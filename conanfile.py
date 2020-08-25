from conans import ConanFile, Meson


class Project(ConanFile):
    name = "timer"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "pkg_config"
    requires = []
    exports_sources = "src/*"

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()
