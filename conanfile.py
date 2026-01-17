from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake, CMakeDeps, CMakeToolchain
from conan.tools.files import copy
from conan.tools.scm import Git, Version
from conan.tools.env import Environment
from conan.errors import ConanInvalidConfiguration


#! @TODO
#! - non-trivial version number (i.e. X.Y.Z-rcN)
#! - test options
#!   - sanitize
#!   - coverage
#!   - fuzz_test
#!   - mutation_test
#!   - ci_build_id
#! - the test package is inheriting the error_support package
#!   - verify this only happens when appropriate
#!   - with shared object
#!   - not with static
#! - Make sure the build can still be run 'manually' with cmake after conan
#!   generates the necesasry dependency files
#! - Make sure the project loads nicely in CLion

#! I'm still determining some of the semantics I want:
#!   - when not running tests, should sanitize (etc) be false or not exist?
class galactic_structures(ConanFile):
    name = 'galactic_structures'
    package_type = 'library'
    version = '1.0.0'
    description = 'Useful data structures'
    homepage = 'https://gitlab.galacticempire.dev/chris/<please create>'
    url = ''
    license = 'GPL-3.0-or-later'
    author = 'Chris Samuelson (chris.sam55@gmail.com)'
    topics = ('utility', 'testing', 'reference')

    settings = 'os', 'compiler', 'build_type', 'arch'

    # it appears that the test_package is picking up this dependency
    # is this always happening? how to stop that..
    test_requires = [
        'boost/[^1.90.0]',
        'rapidcheck/cci.20231215',
        'bitflags/1.5.0',
        'lyra/1.7.0',
        'nlohmann_json/3.12.0',
    ]

    tool_requires = [
        'cmake_scripts/[^1.2.0]',
    ]

    options = {
        'shared': [True, False],
        'fPIC': [True, False],
        'coverage': [True, False],
        'ci_build_id': ['ANY'],
        'docs': [True, False],
        'build_examples': [True, False],
        'sanitize': [True, False],
        'ASan': [True, False],
        'TSan': [True, False],
        'MSan': [True, False],
        'LSan': [True, False],
        'UBSan': [True, False],
        'run_tests': [True, False, None],
        'unit_test': [True, False],
        'fuzz_test': [True, False],
        'mutation_test': [True, False],
    }

    default_options = {
        'shared': False,
        'fPIC': False,
        'coverage': False,
        'ci_build_id': 'local',
        # https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/
        'docs': False,
        # Every sub-project should include some simple example code to work with to demonstrat how to use it, and maybe why it's useful.
        # Bonus: such examples may be useful for developing the project as well
        'build_examples': False,
        'sanitize': False,
        'ASan': True,
        'TSan': False,
        'MSan': False,
        'LSan': True,
        'UBSan': True,
        'run_tests': None,
        'unit_test': True,
        'fuzz_test': False,
        'mutation_test': True,

        'boost/*:without_atomic': True,
        'boost/*:without_charconv': True,
        'boost/*:without_chrono': True,
        'boost/*:without_cobalt': True,
        'boost/*:without_container': True,
        'boost/*:without_context': True,
        'boost/*:without_contract': True,
        'boost/*:without_coroutine': True,
        'boost/*:without_date_time': True,
        'boost/*:without_fiber': True,
        'boost/*:without_filesystem': True,
        'boost/*:without_graph': True,
        'boost/*:without_graph_parallel': True,
        'boost/*:without_iostreams': True,
        'boost/*:without_json': True,
        'boost/*:without_locale': True,
        'boost/*:without_log': True,
        'boost/*:without_math': True,
        'boost/*:without_mpi': True,
        'boost/*:without_nowide': True,
        'boost/*:without_process': True,
        'boost/*:without_program_options': True,
        'boost/*:without_python': True,
        'boost/*:without_random': True,
        'boost/*:without_regex': True,
        'boost/*:without_serialization': True,
        'boost/*:without_stacktrace': True,
        'boost/*:without_system': True,
        'boost/*:without_test': True,
        'boost/*:without_thread': True,
        'boost/*:without_timer': True,
        'boost/*:without_type_erasure': True,
        'boost/*:without_url': True,
        'boost/*:without_wave': True,

        'boost/*:without_exception': False,

        'boost/*:bzip2': False,
        'boost/*:zlib': False,
        'boost/*:numa': False,
        'boost/*:lzma': False,
        'boost/*:zstd': False,

        'boost/*:pch': False,
        'boost/*:header_only': False,
        'boost/*:filesystem_use_std_fs': True,
        'boost/*:asio_no_deprecated': True,
        'boost/*:filesystem_no_deprecated': True,

        'cmake_scripts/*:antlr': True,
    }

    def export_sources(self):
        git = Git(self)
        files = git.included_files()
        for file in files:
            copy(self, file, self.recipe_folder, self.export_sources_folder)

    # I believe this should be used to modify/remove options based on settings
    def config_options(self):
        if self.settings.build_type == 'Release':
            # Sanitizers can affect performance, so they cannot be activated in release mode
            self.options.rm_safe('sanitize')
            self.options.rm_safe('coverage')
            # Fuzzing builds are not for release
            self.options.rm_safe('fuzz_test')

        if self.settings.os == 'Windows':
            self.options.rm_safe('fPIC')

    def configure(self):
        if self.options.get_safe('fuzz_test', default=False):
            self.options.sanitize = True

        # The locally set test_running will supersede the global 'skip_test'
        # If it's not set, then defer to global setting
        if self.options.get_safe('run_tests') == None:
            self.output.debug(f'defaulting run_tests')
            # if it's None, it was not user set; use the skip_test configuration
            self.options.run_tests = not self.conf.get('tools.build:skip_test', default=False)

        if not self.options.run_tests:
            self.options.rm_safe('fuzz_test')
            self.options.rm_safe('mutation_test')
            self.options.rm_safe('unit_test')

        if not self.options.get_safe('sanitize', default=False):
            self.options.rm_safe('ASan')
            self.options.rm_safe('TSan')
            self.options.rm_safe('MSan')
            self.options.rm_safe('LSan')
            self.options.rm_safe('UBSan')

        if self.options.shared:
            self.options.rm_safe('fPIC')

    def requirements(self):
        # libs
        #self.requires('error_support/[^1.0.0]', transitive_headers=True, transitive_libs=True)
        # applications?
        self.requires('error_support/[^1.0.0]')

        if self.unit_test:
            self.test_requires('catch2/[^3.7.0]')

    # running the tests doesn't affect build results
    # if the build produces an invalid package that package would always have
    # been invalid, regardless of if the tests were run
    # the tests just help us catch when that happens
    def package_id(self):
        # theoretical
        # self.config.rm_safe('tools.build:skip_test')
        self.info.options.rm_safe('run_tests')
        self.info.options.rm_safe('unit_test')
        self.info.options.rm_safe('fuzz_test')
        self.info.options.rm_safe('mutation_test')

    def validate(self):
        if (self.options.get_safe('ASan', default=False) and (self.options.get_safe('MSan', default=False) or self.options.get_safe('TSan', default=False))) or (self.options.get_safe('MSan', default=False) and (self.options.get_safe('ASan', default=False) or self.options.get_safe('TSan', default=False))):
            raise ConanInvalidConfiguration('ASan, MSan and TSan are incompatible with each other')

    @property
    def coverage(self) -> bool:
        return self.options.get_safe('coverage', default=False)

    @property
    def ci_build_id(self) -> str:
        return self.options.get_safe('ci_build_id', default='local')

    @property
    def sanitize(self) -> bool:
        return self.options.get_safe('sanitize', default=False)

    @property
    def ASan(self) -> bool:
        return self.sanitize and self.options.get_safe('ASan', default=False)

    @property
    def MSan(self) -> bool:
        return self.sanitize and self.options.get_safe('MSan', default=False)

    @property
    def LSan(self) -> bool:
        return self.sanitize and self.options.get_safe('LSan', default=False)

    @property
    def TSan(self) -> bool:
        return self.sanitize and self.options.get_safe('TSan', default=False)

    @property
    def UBSan(self) -> bool:
        return self.sanitize and self.options.get_safe('UBSan', default=False)

    @property
    def run_tests(self) -> bool:
        return self.options.get_safe('run_tests', default=False)

    @property
    def unit_test(self) -> bool:
        return self.options.get_safe('unit_test', default=False)

    @property
    def fuzz_test(self) -> bool:
        return self.options.get_safe('fuzz_test', default=False)

    @property
    def mutation_test(self) -> bool:
        return self.options.get_safe('mutation_test', default=False)

    def generate(self):
        tool_chain = CMakeToolchain(self)

        version = Version(self.version)
        tool_chain.cache_variables['CONAN_VERSION'] = f'{version.major}.{version.minor}.{version.patch}'
        tool_chain.cache_variables['CONAN_FULL_VERSION'] = self.version
        tool_chain.cache_variables['CONAN_NAME'] = self.name

        tool_chain.cache_variables['WITH_COVERAGE'] = self.coverage
        tool_chain.cache_variables['CI_BUILD_ID'] = self.ci_build_id
        tool_chain.cache_variables['WITH_SANITIZERS'] = self.sanitize
        tool_chain.cache_variables['SANITIZE_ADDRESS'] = self.ASan
        tool_chain.cache_variables['SANITIZE_MEMORY'] = self.MSan
        tool_chain.cache_variables['SANITIZE_LEAK'] = self.LSan
        tool_chain.cache_variables['SANITIZE_THREAD'] = self.TSan
        tool_chain.cache_variables['SANITIZE_UNDEFINED'] = self.UBSan

        tool_chain.cache_variables['RUN_TESTS'] = self.run_tests
        tool_chain.cache_variables['WITH_UNIT_TESTS'] = self.unit_test
        tool_chain.cache_variables['WITH_FUZZING'] = self.fuzz_test
        tool_chain.cache_variables['WITH_MUTATION_TEST'] = self.mutation_test

        tool_chain.generate()

        deps = CMakeDeps(self)
        deps.build_context_activated = ['cmake_scripts']
        deps.build_context_build_modules = ['cmake_scripts']
        deps.generate()

    def _configure_cmake(self):
        cmake = CMake(self)
        return cmake

    def build(self):
        cmake = self._configure_cmake()

        cmake.configure()

        cmake.build()

        if self.unit_test:
            env = Environment()
            env.define('CTEST_OUTPUT_ON_FAILURE', '1')
            vars = env.vars(self)
            with vars.apply():
                cmake.test()

    def layout(self):
        cmake_layout(self)

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    # use components here
    def package_info(self):
        self.cpp_info.libs = ['greeter']
        self.cpp_info.bins = ['Marksman']
        #self.cpp_info.bindirs = ['bin']
        self.cpp_info.includedirs = ['include']
        # self.cpp_info.components['component_name'].set_property('cmake_file_name', 'cmake_target_name')
        # self.cpp_info.components['component_name'].libs = ['...']
        # internal or external target names
        # self.cpp_info.components['component_name'].requires = ['XXX::YYY']
        # self.cpp_info.components['component_name'].defines = ['key=value']

    def deploy(self):
        copy(self, '*', src=self.package_folder, dst=self.deploy_folder)

