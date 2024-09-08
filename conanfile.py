from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake, CMakeDeps, CMakeToolchain
from conan.tools.files import copy
from conans.errors import ConanInvalidConfiguration

class galactic_structures(ConanFile):
    name = "galactic_structures"
    package_type = "library"
    version = "1.0.0"
    description = "Useful data structures"
    homepage = "https://gitlab.galacticempire.dev/chris/<please create>"
    url = ""
    license = ""
    author = "Chris Samuelson (chris.sam55@gmail.com)"
    topics = ("data-structures", "utility")

    settings = "os", "compiler", "build_type", "arch"

    exports_sources = (
        "aligned_buffer/*",
        "core/*",
        "future/*",
        "lifetime/*",
        "matrix/*",
        "optional/*",
        "vector/*",
        "cmake/*",
        "CMakeLists.txt",
        "!.devbox/*",
        "!build*/*",
        "!cmake-build-*/*",
        "!.venv/*",
        "!.conan/*",
    )

    requires = [
    ]

    # it appears that the test_package is picking up this dependency
    # is this always happening? how to stop that..
    test_requires = [
        "catch2/3.7.0"
    ]

    tool_requires = [
        "cmake_scripts/1.0.0"
    ]

    options = {
        "shared": [True, False],
        "sanitize" : [True, False],
        "coverage" : [True, False],
        "fuzz" : [True, False],
        "run_tests" : [True, False],
    }

    default_options = {
        "shared": False,
        "sanitize" : False,
        "coverage" : False,
        "fuzz" : False,
        "run_tests": True,
    }

    def configure(self):
        if self.options.fuzz:
            self.options.sanitize = True

    # more presumptuous alternative to validate
    #def config_options(self):
    #    if self.settings.build_type == "Release":
    #        del self.options.fuzz
    #        del self.options.sanitize

    def requirements(self):
    #    self.requires(".../...", override=True)
        self.requires("error_support/1.0.0", transitive_headers=True, transitive_libs=True)

    # running the tests doesn't affect the results
    # if this produces an invalid package, that package would always have been invalid, regardless of if the tests were run
    # the tests just help us catch the invalid ones :)
    #def package_id(self):
    #    del self.info.options.run_tests
    
    def validate(self):
        if self.settings.build_type == "Release":
            if self.options.fuzz:
                raise ConanInvalidConfiguration("Fuzz builds are not for release")
            if self.options.sanitize:
                raise ConanInvalidConfiguration(
                    "Sanitizers can affect performance, so they cannot be activated in release mode")

    def generate(self):
        tool_chain = CMakeToolchain(self)

        # should be cache variables?
        tool_chain.cache_variables["WITH_FUZZING"] = self.options.fuzz
        tool_chain.cache_variables["WITH_SANITIZERS"] = self.options.sanitize
        tool_chain.cache_variables["WITH_COVERAGE"] = self.options.coverage
        tool_chain.cache_variables["CONAN_VERSION"] = self.version  # should this be set by git?
        #tool_chain.variables["CI_BUILD_ID"] = self.options.ci_build_id if self.options.ci_build_id else "local"

        tool_chain.generate()

        deps = CMakeDeps(self)
        deps.build_context_activated = [ "cmake_scripts" ]
        deps.build_context_build_modules = [ "cmake_scripts" ]
        deps.generate()

    def build(self):
        cmake = CMake(self)

        cmake.configure()
        cmake.build()

        if self.options.run_tests:
            cmake.test()

    def layout(self):
        cmake_layout(self)

    def package(self):
        cmake = CMake(self)
        cmake.install()

    # use components
    def package_info(self):
        # no built binaries yet
        #self.cpp_info.libs = ["galactic_structures"]
        self.cpp_info.includedirs = ["include"]

    def deploy(self):
        copy(self, "*", src=self.package_folder, dst=self.deploy_folder)

