from setuptools import Extension
import os
from typing import Optional
import sys


PACKAGE_NAME = "core_types"
PACKAGE_CPP_NAME = "core_types_cpp"
PYTHON_VERSION = f'{sys.version_info.major}.{sys.version_info.minor}'
SITE_PACKAGES_PATH = os.path.join(sys.prefix, 'lib', f'python{PYTHON_VERSION}', 'site-packages')
TMP_DATA_FILES_DIR = os.path.join('build', 'tmp', 'data')
VENV_LIB_PATH: str = os.path.join(sys.prefix, 'lib', f'python{PYTHON_VERSION}', 'sgs')


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
