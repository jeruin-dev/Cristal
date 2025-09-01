from conan import ConanFile
from conan.tools.cmake import cmake_layout

class Cristal(ConanFile):
    name = "Cristal"
    version = "0.1"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("fmt/11.2.0")

    def layout(self):
        cmake_layout(self)
