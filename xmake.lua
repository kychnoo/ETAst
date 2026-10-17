set_project("ETAst")

add_rules("mode.debug", "mode.release")

add_requires("openssl4")

target("ETAst")
    set_kind("static")
    set_languages("c++20")
    add_files("src/**.cpp|main.cpp")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", {public = true})
    add_packages("openssl4")

    if is_plat("android") then
        set_kind("shared")
    end

target("etast_demo")
    set_kind("binary")
    set_languages("c++20")
    add_files("src/main.cpp")
    add_deps("ETAst")

