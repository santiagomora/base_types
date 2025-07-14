from setuptools import find_packages, setup, Extension
from setuptools.command.build_ext import build_ext
from setuptools.command.install_lib import install_lib
from distutils.command.install_headers import install_headers
import sys
import pathlib
import os
import shutil
from typing import Optional
from glob import glob
import ast


def extract_module_from_path(module_name: str, path: str):
    module_path = os.path.join(path, f'{module_name}.py')
    with open(module_path, 'r') as f:
        tree = ast.parse(f.read(), filename=module_path)
    code_object = compile(tree, filename=module_name, mode='exec')
    module = sys.modules.setdefault(module_name, type(sys)(module_name))
    exec(code_object, module.__dict__)
    return module


setup_config = extract_module_from_path('setup_configuration', os.path.join('core_types', '_sgs_config'))


class BuildCMakeExt(build_ext):
    def run(self):
        self.distribution.data_files = []
        self.tmp_data_files_lib_dir: str = os.path.join(os.getcwd(), setup_config.TMP_DATA_FILES_DIR, 'lib')
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
        # extension_path = pathlib.Path(self.get_ext_fullpath(extension.name))
        extension_path = pathlib.Path(os.path.join(extension.cmake_lists_path, 'build'))
        os.makedirs(build_dir, exist_ok=True)
        # os.makedirs(extension_path.parent.absolute(), exist_ok=True)
        print(f"[BUILD] \"{extension.name}\": Configuring cmake project", file=sys.stdout)
        self.spawn(['cmake', f'-H{extension.cmake_lists_path}', f'-B{extension_path}', '-G', 'Ninja'])
        print(f"[BUILD] \"{extension.name}\": Building libraries", file=sys.stdout)
        self.spawn(["ninja", '-C', extension_path, '-d', 'explain'])
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
            shutil.copy(dst, p)
            print(f"[BUILD] \"{extension.name}\": Copied \"{dst}\" -> \"{build_dir}\"", file=sys.stdout)
        # print(f"[BUILD] \"{extension.name}\": Removing \"{extension_path}\"", file=sys.stdout)
        # shutil.rmtree(extension_path)


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
                shutil.copy(src_path, install_path)
            else:
                # its a so library
                install_path = extension.so_destination_path
                tmp_install_path: str = os.path.join(os.path.join(os.environ['BUILD_TMP_DATA_LIB_DIR'], libname))
                if os.path.exists(tmp_install_path):
                    os.remove(tmp_install_path)
                shutil.copy(os.path.join(build_dir, libname), tmp_install_path)
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


setup(
    packages=find_packages(),
    ext_modules=setup_config.cmake_extensions,
    cmdclass={
        'build_ext': BuildCMakeExt,
        'install_lib': InstallCMakeLibs,
        'install_headers': InstallCMakeHeaders
    },
    include_package_data=True
)
