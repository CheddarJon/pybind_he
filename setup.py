from distutils.core import setup, Extension
import os

__version__ = '0.0.1'
dir_path = os.path.dirname(os.path.realpath(__file__))

ext_modules = [
    Extension(
        'pybind_he',
        ['{0}/pybind_he/pybind_he.cpp'.format(dir_path)],
        include_dirs=[
            '{0}/lib/pybind11'.format(dir_path),
            '{0}/lib/helib_pack/include'.format(dir_path)
        ],
        language='c++'
    ),
]


def run_setup():

    setup(name="pybind_he",
          version=__version__,
          description="bgv example",
          package_dir={'': 'lib'},
          author='Ture Teknolog',
          url='https://github.com/CheddarJon/pybind_he',
          # Modules not written in Python !
          ext_modules=ext_modules
          )


try:
    run_setup()
except Exception as e:
    raise e