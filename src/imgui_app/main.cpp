#include <array>
#include <chrono>
#include <cstdio>
#include <sstream>
#include <thread>

// clang-format off
#include "glad/gl.h" // must include before glfw
// clang-format on

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "stb_image.h"

auto window_width = 850;
auto window_height = 580;
constexpr auto navigator_width = 200;

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    window_width = width;
    window_height = height;
}

void custom_style() {
    auto& style = ImGui::GetStyle();

    style.WindowPadding = ImVec2{10, 10};

    style.WindowRounding = 0.0F;
    style.FrameRounding = 5.0F;
    style.PopupRounding = 5.0F;
    style.ScrollbarRounding = 5.0F;
    style.GrabRounding = 5.0F;

    style.WindowBorderSize = 1.0F;
    style.FrameBorderSize = 1.0F;
}

static void HelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0F);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

int main(int, char**) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

        // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                   GL_TRUE);  // 3.0+ only
                              // glfwWindowHint(GLFW_DECORATED, GL_FALSE);
#endif

    // Create window with graphics context
    GLFWwindow* window =
        glfwCreateWindow(window_width, window_height, "VideoHub", nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    //  set window icon
    {
        GLFWimage icon;
        icon.pixels = stbi_load("video_hub.png", &icon.width, &icon.height, nullptr, 4);
        glfwSetWindowIcon(window, 1, &icon);
        stbi_image_free(icon.pixels);
    }

    // resize callback
    glfwSetWindowSizeCallback(window, window_size_callback);

    // minimal size
    glfwSetWindowSizeLimits(window, window_width, window_height, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    // Initialize OpenGL loader
    // glad2 recommend using the windowing library loader
    // instead of the (optionally) bundled one.
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();
    custom_style();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple
    // fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the
    // font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in
    // your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture
    // when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below
    // will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 16.0F);
    io.Fonts->AddFontFromFileTTF("fonts/Cousine-Regular.ttf", 15.0F);
    io.Fonts->AddFontFromFileTTF("fonts/DroidSans.ttf", 16.0f);
    io.Fonts->AddFontFromFileTTF("fonts/ProggyTiny.ttf", 16.0f);
    // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Arial.ttf", 18.0f, NULL,
    // io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != NULL);

    // Our state
    ImVec4 clear_color = ImVec4(1.0F, 1.0F, 1.0F, 1.00F);

    // window flags
    ImGuiWindowFlags flags = 0;
    flags |= ImGuiWindowFlags_NoTitleBar;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoScrollbar;
    flags |= ImGuiWindowFlags_NoCollapse;
    flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui
        // wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main
        // application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main
        // application. Generally you may always pass all inputs to dear imgui, and hide them from
        // your application based on those two flags.
        glfwPollEvents();

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // navigator window
        {
            ImGui::SetNextWindowPos({0.0, 0.0});
            ImGui::SetNextWindowSize({navigator_width, static_cast<float>(window_height)});
            ImGui::Begin("Navigator", nullptr, flags);
            if (ImGui::ShowStyleSelector("Theme##Selector")) {
                custom_style();
            }

            ImGui::Spacing();
            ImGui::Separator();

            {
                ImGui::Spacing();
                if (ImGui::Button("New download")) {
                    ImGui::OpenPopup("download");
                };
                // Always center this window when appearing
                ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5F,
                              ImGui::GetIO().DisplaySize.y * 0.5F);
                ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5F, 0.5F));
                ImGui::SetNextWindowSize({window_width * 0.8F, window_height * 0.8F});

                if (ImGui::BeginPopup("download", ImGuiWindowFlags_NoMove)) {
                    std::array<char, 1024> url{};
                    ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth() * 0.9F);
                    ImGui::InputTextWithHint("Url", "download link", url.data(), url.size());

                    if (ImGui::Button("OK")) {
                        // std::stringstream cmd("youtube-dl ");
                        // cmd << url.data();
                        // system(cmd.str().c_str());
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();
                }
            }

            ImGui::End();
        }

        // content window
        {
            ImGui::SetNextWindowPos({navigator_width - 1, 0.0});
            ImGui::SetNextWindowSize({static_cast<float>(window_width - navigator_width + 1),
                                      static_cast<float>(window_height)});
            ImGui::Begin("Content", nullptr, flags);

            ImGui::End();
        }

        ImGui::ShowDemoWindow();

        // Rendering
        ImGui::Render();
        int display_w = 0;
        int display_h = 0;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        if (!glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
