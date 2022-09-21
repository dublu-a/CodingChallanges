add_rules("mode.debug", "mode.release")
add_requires("raylib")


target("smoketest")
    set_kind("binary")
    add_files("src/0000.smoketest/*.cpp")
    add_packages("raylib")
target_end()

target("starfield")
    set_kind("binary")
    add_files("src/0001.starfield/*.cpp")
    add_packages("raylib")
target_end()