add_requires("imgui", "raylib", "raylib-cpp")

target("node_editor")
    set_kind("binary")
    set_basename("NodeEditor")
    set_languages("c++20")
    add_files("src/**.cpp")

    add_packages("imgui", "raylib", "raylib-cpp")