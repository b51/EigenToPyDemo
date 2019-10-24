from distutils.core import setup, Extension
import numpy

module1 = Extension('EigenToPy',
                    sources=['eigen_extensions.cc'],
                    extra_compile_args=["-std=c++11"],
                    include_dirs=[numpy.get_include(), '/usr/include/eigen3'],
                    # extra_compile_args=["-O0", "-g"],
                    )

setup(name='Eigen-Extensions',
      version='1.0',
      description='This is a package with python extensions for the rotation matrix to numpy',
      ext_modules=[module1])
