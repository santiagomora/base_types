from setuptools import find_packages, setup
from core_cpp_packaging_tools.setup_script import\
    BuildCMakeExt,\
    InstallCMakeLibs,\
    InstallCMakeHeaders,\
    extract_module_from_path


setup_config = extract_module_from_path('_packaging', 'core_types')


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
