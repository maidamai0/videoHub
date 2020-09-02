# Video Hub

## Download engine

* [youtube-dl](https://github.com/ytdl-org/youtube-dl)
* [aria2](https://github.com/aria2/aria2)

## Dependencices

* spdlog
* glfw
* glad
* doctest
* fmtlib
* imgui

:bulb: Install all dependencies with [vcpkg](https://github.com/microsoft/vcpkg)

```cmd
vcpkg install spdlog glfw3 doctest fmt
```

:bulb: `glad` and `imgui` are already in [third_party](third_party/CMakeLists.txt)