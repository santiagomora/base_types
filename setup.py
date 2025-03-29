from setuptools import find_packages, setup, Extension
from setuptools.command.build_ext import build_ext
from setuptools.command.install_lib import install_lib
from distutils.command.install_data import install_data
from distutils.command.install_headers import install_headers
import struct
import sys
import pathlib
import os
import shutil
from typing import Optional
from glob import glob
import subprocess as sp


BITS = struct.calcsize("P") * 8
PACKAGE_NAME = "core_types"
PACKAGE_CPP_NAME = "core_types_cpp"
PYTHON_VERSION = "3.12"


class CMakeExtension(Extension):
    def __init__(
        self, *, name: str, cmake_lists_path: list[str], so_destination_path: str,
        is_package: bool, include_files_path: Optional[tuple[str, str]]
    ):
        super().__init__(name=name, sources=[])
        self.cmake_lists_path = cmake_lists_path
        self.so_destination_path = so_destination_path
        self.include_files_path = include_files_path
        self.is_package = is_package


cmake_extensions = [
    CMakeExtension(
        name='libcore_types',
        cmake_lists_path=os.path.join(PACKAGE_CPP_NAME, 'lib'),
        so_destination_path=os.path.join('lib',  f'python{PYTHON_VERSION}', 'sgs'),
        include_files_path=(os.path.join(PACKAGE_CPP_NAME, 'lib', 'include'), os.path.join('include', f'python{PYTHON_VERSION}')),
        is_package=False
    ),
    CMakeExtension(
        name='wrapper',
        cmake_lists_path=os.path.join(PACKAGE_CPP_NAME, 'module'),
        so_destination_path=os.path.join(PACKAGE_NAME, 'cpp'),
        include_files_path=None,
        is_package=True
    )
]


class BuildCMakeExt(build_ext):
    def run(self):
        self.distribution.data_files = []
        self.tmp_data_files_lib_dir: str = os.path.join(os.path.join(os.getcwd(), 'build', 'tmp', 'data'), 'lib')
        os.makedirs(self.tmp_data_files_lib_dir, exist_ok=True)
        os.environ['BUILD_TMP_DATA_LIB_DIR'] = self.tmp_data_files_lib_dir
        for extension in self.extensions:
            print(f"[BUILD] \"{extension.name}\": Building", file=sys.stdout)
            self.build_cmake(extension)
            self.distribution.extension = extension
            self.run_command('install_headers')
            self.run_command('install_lib')

    def build_cmake(self, extension: Extension):
        print(f"[BUILD] \"{extension.name}\": Preparing the build environment", file=sys.stdout)
        build_dir = pathlib.Path(self.build_temp)
        extension_path = pathlib.Path(self.get_ext_fullpath(extension.name))
        os.makedirs(build_dir, exist_ok=True)
        os.makedirs(extension_path.parent.absolute(), exist_ok=True)
        print(f"[BUILD] \"{extension.name}\": Configuring cmake project", file=sys.stdout)
        self.spawn(['cmake', f'-H{extension.cmake_lists_path}', f'-B{extension_path}'])
        print(f"[BUILD] \"{extension.name}\": Building libraries", file=sys.stdout)
        self.spawn(["cmake", "--build", extension_path])
        libs = [
            so for so in
            os.listdir(extension_path) if
            os.path.isfile(os.path.join(extension_path, so)) and
            so.split('.')[-1] == "so"
        ]
        for lib in libs:
            p = os.path.join(build_dir, lib)
            dst = os.path.join(extension_path, lib)
            if os.path.exists(p):
                os.remove(p)
            shutil.move(dst, p)
            print(f"[BUILD] \"{extension.name}\": Moved \"{dst}\" -> \"{build_dir}\"", file=sys.stdout)
        print(f"[BUILD] \"{extension.name}\": Removing \"{extension_path}\"", file=sys.stdout)
        shutil.rmtree(extension_path)


class InstallCMakeLibs(install_lib):
    def run(self):
        extension = self.distribution.extension
        print(f"[INSTALL_LIBS] \"{extension.name}\": Installing libraries", file=sys.stdout)
        self.skip_build = True
        build_dir = pathlib.Path(self.get_finalized_command('build').build_temp)
        lib_dir = self.get_finalized_command('build').build_lib
        print(f"[INSTALL_LIBS] \"{extension.name}\": Getting libraries from \"{build_dir}\"", file=sys.stdout)
        libraries = []
        for lib in os.listdir(build_dir):
            if lib.startswith(extension.name):
                libraries.append(lib)
        for libname in libraries:
            install_path = ''
            src_path = ''
            if extension.is_package:
                # its a compiled c++ wrapper
                install_path = os.path.join(lib_dir, extension.so_destination_path)
                os.makedirs(install_path, exist_ok=True)
                install_path = os.path.join(install_path, libname)
                src_path = os.path.join(build_dir, libname)
                shutil.move(src_path, install_path)
            else:
                # its a so library
                install_path = extension.so_destination_path
                tmp_install_path: str = os.path.join(os.path.join(os.environ['BUILD_TMP_DATA_LIB_DIR'], libname))
                if os.path.exists(tmp_install_path):
                    os.remove(tmp_install_path)
                shutil.move(os.path.join(build_dir, libname), tmp_install_path)
                self.distribution.data_files.append((install_path, [tmp_install_path]))
        super().run()


class InstallCMakeHeaders(install_headers):
    def run(self):
        paths: Optional[tuple[str, str]] = self.distribution.extension.include_files_path
        if paths is None:
            super().run()
            return
        print(f"[INSTALL_HEADERS] \"{self.distribution.extension.name}\": Installing headers", file=sys.stdout)
        src, dest = paths
        data_files = []
        base: Optional[str] = None
        for root, _, _ in os.walk(src):
            base = root if base is None else base
            files_and_directories = glob(os.path.join(root, "*"))
            if files_and_directories:
                files = [f for f in files_and_directories if os.path.isfile(f)]
                if len(files) > 0:
                    data_files.append((root.replace(base, dest), files))
        self.distribution.data_files += data_files
        super().run()


class InstallCMakeData(install_data):
    def run(self):
        print(f"[INSTALL_DATA] Setting library rpaths", file=sys.stdout)
        package_exts: list[CMakeExtension] = [p for p in cmake_extensions if p.is_package]
        library_exts: list[CMakeExtension] = [p for p in cmake_extensions if not p.is_package]
        lib_dir = self.get_finalized_command('build').build_lib
        binaries: list[str] = []
        for install_path, data_file_paths in self.distribution.data_files:
            for lib_ext in library_exts:
                if install_path == lib_ext.so_destination_path:
                    binaries += data_file_paths
        for pkg_ext in package_exts:
            install_path: str = os.path.join(lib_dir, pkg_ext.so_destination_path)
            for w in os.listdir(install_path):
                if w.startswith(pkg_ext.name):
                    binaries.append(os.path.join(install_path, w))
        for binary in binaries:
            print(f'[INSTALL_DATA] Binary "{binary}" setting rpath', file=sys.stdout)
            get_rpath_proc: sp.CompletedProcess = sp.run(['patchelf', '--print-rpath', binary], capture_output=True)
            bin_rpath: str = str(get_rpath_proc.stdout).rstrip()
            venv_lib_path: str = os.path.join(sys.prefix, 'lib', f'python{PYTHON_VERSION}', 'sgs')
            if bin_rpath == '':
                bin_rpath = venv_lib_path
            else:
                bin_rpath = f'{venv_lib_path}:{venv_lib_path}'
            sp.run(['patchelf', '--set-rpath', bin_rpath, binary], check=True)
            print(f'[INSTALL_DATA] Binary "{binary}" rpath set to "{bin_rpath}"', file=sys.stdout)
        super().run()


setup(
    packages=find_packages(),
    ext_modules=cmake_extensions,
    cmdclass={
        'build_ext': BuildCMakeExt,
        'install_lib': InstallCMakeLibs,
        'install_headers': InstallCMakeHeaders,
        'install_data': InstallCMakeData
    },
    include_package_data=True
)
