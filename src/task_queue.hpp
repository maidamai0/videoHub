#pragma once

/**
 * @file task_queue.hpp
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief thread save multiple producer multiple consumer queue.
 * @version 0.1
 * @date 2020-08-30
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <chrono>
#include <memory>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <string>
#include <type_traits>

#include "task.hpp"

/**
 * @brief Every task is a resource link can be used to download.
 *
 */
class TaskQueue {
   public:
    using value_type = Task::task_ptr;

    void Push(std::string&& url) {
        std::unique_lock<mutex_type> lock(mtx_);
        tasks_.push(std::make_shared<Task>(std::move(url)));
        con_var_.notify_one();
    };

    auto Pop() {
        using namespace std::chrono_literals;
        std::unique_lock<mutex_type> lock(mtx_);
        if (con_var_.wait_for(lock, 200ms, [this]() { return !tasks_.empty(); })) {
            auto task = tasks_.front();
            tasks_.pop();
            return task;
        }

        // time out
        return value_type{};
    }

   private:
    using mutex_type = std::mutex;
    mutex_type mtx_;
    std::queue<value_type> tasks_;
    std::condition_variable con_var_;
};