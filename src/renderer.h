#pragma once

#include <memory>
#include <string>

#include "downloader.hpp"
#include "task_queue.hpp"

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

    enum class ContentType { kDownloading, kDownloaded };

    std::shared_ptr<TaskQueue> queue_;
    std::unique_ptr<Downloader> downloader_;
    ContentType content_type_{ContentType::kDownloading};
};