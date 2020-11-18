from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
from distutils.version import LooseVersion

import os

version = '2.3.0'

# Read README for PyPI, fallback to short description if it fails.
desc = 'Physiology Sim - v1'
# try:
#     readme_file = os.path.join(os.path.dirname(os.path.abspath(__file__)),
#                                'README.rst')
#     with open(readme_file) as f:
#         readme = f.read()
# except ImportError:
#     readme = desc

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)

class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)', out.decode()).group(1))
            if cmake_version < '3.1.0':
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        # required for auto-detection of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), extdir)]
            if sys.maxsize > 2**32:
                cmake_args += ['-A', 'x64']
            build_args += ['--', '/m']
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j2']

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(env.get('CXXFLAGS', ''),
                                                              self.distribution.get_version())
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env)
        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)



setup(
    name="biogears",
    version=version,
    # packages=['biogears'],
    description=desc,
    # long_description=readme,
    long_description_content_type='text/x-rst',
    keywords=('biology simulation'),
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: BSD License",
        "Topic :: Scientific/Engineering :: Biology",
        "Programming Language :: C++",
        "Programming Language :: Cython",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
    ],
    zip_safe=False,
    maintainer='Hipo',
    maintainer_email='vybhav@hipo.ai',
    # See documentation credits for current and former lead developers
    author='Vybhav Ramachandran',
    author_email='vybhav@hipo.ai',
    url='https://github.com/vybhavramachandran',
    download_url='https://github.com/vybhavramachandran',
    project_urls={
        'Homepage': 'https://github.com/vybhavramachandran',
        'Documentation': 'https://github.com/vybhavramachandran',
        'Source Code': 'https://github.com/vybhavramachandran',
        'Issue Tracker': 'https://github.com/vybhavramachandran',
    },
    python_requires='>=3.6',
    ext_modules=[CMakeExtension('biogears')],
    cmdclass=dict(build_ext=CMakeBuild),

    )
