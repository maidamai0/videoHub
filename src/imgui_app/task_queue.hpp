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
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <string>
#include <type_traits>

/**
 * @brief Every task is a resource link can be used to download.
 *
 */
class TaskQueue {
   public:
    void Push(std::string&& task) {
        std::unique_lock<mutex_type> lock(mtx_);
        tasks_.push(std::move(task));
        con_var_.notify_one();
    };

    std::string Pop() {
        using namespace std::chrono_literals;
        std::unique_lock<mutex_type> lock(mtx_);
        if (con_var_.wait_for(lock, 200ms, [this]() { return !tasks_.empty(); })) {
            auto task = tasks_.front();
            tasks_.pop();
            return task;
        }

        // time out
        return {};
    }

   private:
    using mutex_type = std::mutex;
    mutex_type mtx_;
    std::queue<std::string> tasks_;
    std::condition_variable con_var_;
};