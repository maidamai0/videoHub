#pragma once

#include <memory>
#include <string>

#include "downloader.hpp"

class Renderer final {
   public:
    explicit Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer& rhs) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&& rhs) = delete;

    void Render();
    void Destroy();

   private:
    void draw_navigation_window();
    void draw_new_download_window();
    static void draw_downloading_window();
    static void draw_downloaded_window();
    static void style_selector();
    static void font_selector();
    static void custom_style();

    enum class ContentType { kDownloading, kDownloaded };

    std::unique_ptr<Downloader> downloader_;
    ContentType content_type_{ContentType::kDownloading};
};