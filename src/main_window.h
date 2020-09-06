#pragma once
#include <string>
#include <tuple>

// clang-format off
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

    [[nodiscard]] auto GetWindow() const {
        return window_;
    }

    [[nodiscard]] auto GetGLSLVersion() const {
        return glsl_version_;
    }

    void Run();

    MainWindow(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;

    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

   private:
    MainWindow();

    GLFWwindow* window_ = nullptr;
    std::string glsl_version_;
    static int window_width_;
    static int window_height_;
};