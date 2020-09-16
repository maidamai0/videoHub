#include "main_window.h"

#include "renderer.h"
#include "resource_list.h"
#include "stb_image.h"

int MainWindow::window_width_ = 850;
int MainWindow::window_height_ = 580;

void glfw_error_callback(int error, const char* description) {
    LOG_E("GLFW error {}:{}", error, description)
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    MainWindow::SetWindowSize(width, height);
}

MainWindow::MainWindow() {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        throw std::exception{"initialize GLFW failed"};
    }
    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    glsl_version_ = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    glsl_version_ = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_DECORATED, GL_FALSE);
#endif

    // Create window with graphics context
    window_ = glfwCreateWindow(window_width_, window_height_, "VideoHub", nullptr, nullptr);
    if (window_ == nullptr) {
        throw std::exception{"GLFW create window failed"};
    }
    //  set window icon
    {
        GLFWimage icon;
        resman::ResourceHandle win_icon{window_icon};
        // icon.pixels = stbi_load("video_hub.png", &icon.width, &icon.height, nullptr, 4);
        icon.pixels = stbi_load_from_memory(
            win_icon.data(), win_icon.size(), &icon.width, &icon.height, nullptr, 4);
        glfwSetWindowIcon(window_, 1, &icon);
        stbi_image_free(icon.pixels);
    }

    // resize callback
    glfwSetWindowSizeCallback(window_, window_size_callback);

    // minimal size
    glfwSetWindowSizeLimits(window_, window_width_, window_height_, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);  // Enable vsync

    // Initialize OpenGL loader
    // glad2 recommend using the windowing library loader
    // instead of the (optionally) bundled one.
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        throw std::exception{"glad2 load OpenGL failed"};
    }
}

void MainWindow::Run() {
    Renderer renderer;
    // Main loop
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();

        if (glfwGetWindowAttrib(window_, GLFW_ICONIFIED)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            continue;
        }

        // Rendering
        renderer.Render();

        glfwSwapBuffers(window_);
        int display_w = 0;
        int display_h = 0;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(1.0F, 1.0F, 1.0F, 1.00F);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!glfwGetWindowAttrib(window_, GLFW_FOCUSED)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    renderer.Destroy();

    glfwDestroyWindow(window_);
    glfwTerminate();
}