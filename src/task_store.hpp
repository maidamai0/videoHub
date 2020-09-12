#pragma once

#include <list>
#include <mutex>
#include <type_traits>

#include "task_queue.hpp"

class TaskStore final {
   public:
    using task_ptr = Task::task_ptr;
    static TaskStore& GetInstance() {
        static TaskStore instance;
        return instance;
    }

    ~TaskStore() {
        std::cout << __FUNCTION__ << std::endl;
    }

    void AddDownloadingTask(const task_ptr& task) {
        std::lock_guard<std::mutex> lock(downloading_mutex_);
        downloading_list_.push_back(task);
    }

    void RemoveDownloadingTask(const task_ptr& task) {
        std::lock_guard<std::mutex> lock(downloading_mutex_);
        downloading_list_.remove_if(
            [&task](const task_ptr& v) { return v->GetUrl() == task->GetUrl(); });
    }

    [[nodiscard]] auto GetDownloadingList() const {
        std::lock_guard<std::mutex> lock(downloading_mutex_);
        auto list = downloading_list_;
        return list;
    }

    void AddDownloadedTask(const task_ptr& task) {
        std::lock_guard<std::mutex> lock(downloaded_mutex_);
        downloaded_list_.push_back(task);
    }

    [[nodiscard]] auto GetDownloadedList() const {
        std::lock_guard<std::mutex> lock(downloaded_mutex_);
        auto list = downloaded_list_;
        return list;
    }

    void AddPendingList(std::string&& url) {
        pending_list_.Push(std::move(url));
    }

    TaskQueue& GetPendingList() {
        return pending_list_;
    }

   private:
    TaskStore() = default;
    void save_tasks() const {}

    std::list<task_ptr> downloading_list_;
    mutable std::mutex downloading_mutex_;
    std::list<task_ptr> downloaded_list_;
    mutable std::mutex downloaded_mutex_;

    TaskQueue pending_list_;  // thread safe queue.
};