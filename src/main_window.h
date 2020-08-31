#pragma once

// clang-format off
#include <string>
#include <tuple>
#include "glad/gl.h" // must include before glfw
// clang-format on
#include "GLFW/glfw3.h"

class MainWindow final {
   public:
    [[nodiscard]] static MainWindow& GetInstance() {
        static MainWindow instance;
        return instance;
    }

    static auto GetSize() {
        return std::make_tuple(window_width_, window_height_);
    }

    static auto Width() {
        return window_width_;
    }

    static auto Height() {
        return window_height_;
    }

    static auto SetWindowSize(const int w, const int h) {
        window_width_ = w;
        window_height_ = h;
    }

    auto GetWindow() const {
        return window_;
    }

    auto GetGLSLVersion() const {
        return glsl_version_;
    }

    void Run();

    MainWindow(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;

    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

   private:
    MainWindow();

   private:
    GLFWwindow* window_ = nullptr;
    std::string glsl_version_;
    static int window_width_;
    static int window_height_;
};