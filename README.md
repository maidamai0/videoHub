# Video Hub

## :books: How to use

Download from [release](https://github.com/maidamai0/videoHub/releases) and make sure [youtube-dl](https://github.com/ytdl-org/youtube-dl) is in you `PATH`

## :rocket: Download engine

* [youtube-dl](https://github.com/ytdl-org/youtube-dl)
* [aria2](https://github.com/aria2/aria2)

## :package: Dependencies

* [nlohmann_json](https://github.com/nlohmann/json)
* [spdlog](https://github.com/gabime/spdlog)
* [glfw](https://github.com/glfw/glfw)
* [glad2](https://github.com/Dav1dde/glad/tree/glad2)
* [doctest](https://github.com/onqtam/doctest)
* [fmtlib](https://github.com/fmtlib/fmt)
* [imgui](https://github.com/ocornut/imgui)

## :hammer: Build

* Clone code

    ```git
    git clone https://github.com/maidamai0/videoHub.git --recursive
    ```

* Install dependencies (vcpkg for example)

    ```powershell
    vcpkg install nlohmann_json spdlog glfw3 doctest fmt
    ```

    :bulb: If you want to use [tracy](https://github.com/wolfpld/tracy) profiler you need install its dependencies too.

    ```powershell
    vcpkg install capstone freetype libjpeg-turbo gl3w
    ```

* Build, use ninja for example

    ```powershell
    cd ${video_hub_git_root_path}
    mkdir build
    cd build
    cmake ..
    ninja
    ```

    :bulb: you may need to some options to cmake.

## :camera: Screen shots

![Light theme](screen_shots/light_theme.png)
![Light theme](screen_shots/classical_theme.png)
![Light theme](screen_shots/dark_theme.png)

![Downloading red](screen_shots/downloading_red.png)
![Downloading yellow](screen_shots/downloading_yellow.png)
![Downloading green](screen_shots/downloading_green.png)