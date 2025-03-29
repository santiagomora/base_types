import os
import sys
from .setup_configuration import\
    cmake_extensions,\
    CMakeExtension,\
    SITE_PACKAGES_PATH,\
    VENV_LIB_PATH
import subprocess as sp


if __name__ == '__main__':
    print("[CONFIGURE_RPATH] Setting library rpaths for package core_types.", file=sys.stdout)
    package_exts: list[CMakeExtension] = [p for p in cmake_extensions if p.is_package]
    library_exts: list[CMakeExtension] = [p for p in cmake_extensions if not p.is_package]
    binaries: list[str] = []
    for lib_ext in library_exts:
        install_path: str = os.path.join(sys.prefix, lib_ext.so_destination_path, f'{lib_ext.name}.so')
        assert os.path.exists(install_path)
        binaries.append(install_path)
    for pkg_ext in package_exts:
        install_path: str = os.path.join(SITE_PACKAGES_PATH, pkg_ext.so_destination_path)
        for w in os.listdir(install_path):
            if w.startswith(pkg_ext.name):
                binaries.append(os.path.join(install_path, w))
    for binary in binaries:
        print(f'[CONFIGURE_RPATH] Binary "{binary}" setting rpath', file=sys.stdout)
        get_rpath_proc: sp.CompletedProcess = sp.run(['patchelf', '--print-rpath', binary], capture_output=True)
        bin_rpath: str = get_rpath_proc.stdout.decode("utf-8").rstrip()
        if VENV_LIB_PATH in bin_rpath:
            print(f'[CONFIGURE_RPATH] Binary "{VENV_LIB_PATH}" already in "{binary}" rpath', file=sys.stdout)
            continue
        if bin_rpath == '':
            bin_rpath = VENV_LIB_PATH
        else:
            bin_rpath = f'{VENV_LIB_PATH}:{bin_rpath}'
        sp.run(['patchelf', '--set-rpath', bin_rpath, binary], check=True)
        print(f'[CONFIGURE_RPATH] Binary "{binary}" rpath set to "{bin_rpath}"', file=sys.stdout)
