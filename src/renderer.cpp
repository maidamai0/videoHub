#include "renderer.h"

#include <array>
#include <memory>
#include <queue>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "main_window.h"
#include "resource_list.h"
#include "roboto_medium.hpp"
#include "task.hpp"
#include "task_queue.hpp"
#include "task_store.hpp"

// window flags
constexpr auto kFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus;

constexpr auto kNavigatorWidth = 200;

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

void HelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0F);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

Renderer::Renderer()
    : queue_{std::make_shared<TaskQueue>()}, downloader_{std::make_unique<Downloader>(queue_)} {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(MainWindow::GetInstance().GetWindow(), true);
    ImGui_ImplOpenGL3_Init(MainWindow::GetInstance().GetGLSLVersion().c_str());

    // Load Fonts
    io.Fonts->AddFontFromMemoryCompressedTTF(
        roboto_medium_compressed_data, roboto_medium_compressed_size, 16.0F);

    custom_style();
}

void Renderer::Render() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos({0.0, 0.0});
    ImGui::SetNextWindowSize(
        {static_cast<float>(MainWindow::Width()), static_cast<float>(MainWindow::Height())});
    ImGui::Begin("background", nullptr, kFlags);
    ImGui::Columns(2, "MainColumn");

    // There is a bug on the column width, see details at
    // https://github.com/ocornut/imgui/issues/1655
    static bool init = true;
    if (init) {
        ImGui::SetColumnWidth(-1, kNavigatorWidth);
        init = false;
    }
    ImGui::BeginChild("Navigator");
    draw_navigation_window();
    ImGui::EndChild();
    ImGui::SameLine();

    ImGui::NextColumn();
    ImGui::PushItemWidth(-1);
    ImGui::BeginChild("Content");
    draw_content_window();
    ImGui::EndChild();
    ImGui::PopItemWidth();

    ImGui::End();

#ifndef NDEBUG
    ImGui::ShowDemoWindow();
#endif

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::draw_navigation_window() {
    {
        ImGui::Spacing();
        if (ImGui::Button("New download", ImVec2(-FLT_MIN, 0.0F))) {
            ImGui::OpenPopup("download");
        };
        // Always center this window when appearing
        ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5F, ImGui::GetIO().DisplaySize.y * 0.5F);
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5F, 0.5F));
        ImGui::SetNextWindowSize({MainWindow::Width() * 0.8F, MainWindow::Height() * 0.8F});

        if (ImGui::BeginPopup("download", ImGuiWindowFlags_NoMove)) {
            static std::array<char, 1024> url{};
            ImGui::PushItemWidth(-FLT_MIN);
            if (ImGui::InputTextWithHint("Url", "download link", url.data(), url.size())) {
                ImGui::SetKeyboardFocusHere();
            }

            if (ImGui::Button("OK", ImVec2(-FLT_MIN, 0.0F))) {
                if (!url.empty()) {
                    queue_->Push(std::string(url.data()));
                    url = {};
                }
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }

    ImGui::SetCursorPos({15.0F, static_cast<float>(MainWindow::Height() - 50)});
    ImGui::Separator();
    ImGui::Spacing();
    if (ImGui::ShowStyleSelector("Theme##Selector")) {
        custom_style();
    }
}

void Renderer::draw_content_window() {
    for (const auto& task : TaskStore::GetInstance().GetDownloadingList()) {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0F);
        ImGui::BeginChild(task->GetUrl().c_str(), ImVec2(0, 80), true, window_flags);

        // progress bar
        if (unlikely(task->GetFullPath().empty())) {
            ImGui::ProgressBar(0.0F, ImVec2(-1.0F, -1.0F), task->GetUrl().c_str());
        } else {
            auto progress = task->GetProgress();
            auto progresss_value =
                progress.empty() ? 0.0F
                                 : std::stof(progress.substr(0, progress.size() - 1)) / 100.0F;
            auto color = interpolate(
                {0.8F, 0.F, 0.0F}, {1.0F, 0.88F, 0.2F}, {0.0F, 0.4F, 0.0F}, progresss_value);

            ImGui::PushStyleColor(ImGuiCol_PlotHistogram,
                                  ImVec4{color[0], color[1], color[2], 1.0F});
            ImGui::ProgressBar(
                progresss_value, ImVec2(-1.0F, 0.0F), task->GetProgressAndSize().c_str());
            ImGui::PopStyleColor();

            // file name
            ImGui::Text("   * %s", task->GetFullPath().c_str());

            // realtime description
            ImGui::Text("   * %s", task->GetSpeed().c_str());
        }

        ImGui::EndChild();
        ImGui::PopStyleVar();

        ImGui::Spacing();
        ImGui::Spacing();
    }
}

void Renderer::Destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}