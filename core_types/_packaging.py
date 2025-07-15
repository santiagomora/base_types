import os
import sys
from core_cpp_packaging_tools import CMakeExtension


PACKAGE_NAME = "core_types"
PACKAGE_CPP_NAME = "core_types_cpp"
PYTHON_VERSION = f'{sys.version_info.major}.{sys.version_info.minor}'
SITE_PACKAGES_PATH = os.path.join(sys.prefix, 'lib', f'python{PYTHON_VERSION}', 'site-packages')
TMP_DATA_FILES_DIR = os.path.join('build', 'tmp', 'data')
VENV_LIB_PATH: str = os.path.join(sys.prefix, 'lib', f'python{PYTHON_VERSION}', 'sgs')
SRC_PATH: str = os.path.abspath('.')


cmake_extensions = [
    CMakeExtension(
        name='libcore_types', src_path=SRC_PATH,
        cmake_lists_path=os.path.join(PACKAGE_CPP_NAME, 'lib'),
        so_destination_path=os.path.join('lib',  f'python{PYTHON_VERSION}', 'sgs'),
        include_files_path=(os.path.join(PACKAGE_CPP_NAME, 'lib', 'include'), os.path.join('include', f'python{PYTHON_VERSION}')),
        is_package=False
    ),
    CMakeExtension(
        name='wrapper', src_path=SRC_PATH,
        cmake_lists_path=os.path.join(PACKAGE_CPP_NAME, 'module'),
        so_destination_path=os.path.join(PACKAGE_NAME, 'cpp'),
        include_files_path=None,
        is_package=True
    )
]
