#pragma once

#include <list>
#include <mutex>

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

   private:
    TaskStore() = default;

    std::list<task_ptr> downloading_list_;
    mutable std::mutex downloading_mutex_;
    std::list<task_ptr> downloaded_list_;
    std::mutex downloaded_mutex_;
};