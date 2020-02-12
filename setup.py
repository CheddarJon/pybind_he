from distutils.core import setup, Extension
import os
import sysconfig

setup(name="pbind_he",
        version="0.1",
        description="bgv example",
        package_dir={'': 'lib'},
        ext_modules= [
            Extension("helib_bgv",
                sources = ["pbind_he/helib_bgv.cpp"],
                include_dirs = ['lib/helib_pack/include',],
                library_dirs = ['lib/helib_pack/lib',],
                libraries = ['helib', 'gmp', 'ntl'],
            ),
        ]
)
