#pragma once

/**
 * @file downloader.hpp
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   start several threads pop task queue and run task.
 * @version 0.1
 * @date 2020-08-30
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <atomic>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#include "task_queue.hpp"

class Downloader final {
   public:
    explicit Downloader(TaskQueue& queue) : task_queue_(queue) {
        const auto size = std::thread::hardware_concurrency();
        for (std::remove_const<decltype(size)>::type i = 0; i < size; ++i) {
            workers_.push_back(std::make_unique<std::thread>(&Downloader::worker, this));
            thread_names_[workers_.back()->get_id()] = "worker #" + std::to_string(i);
        }
    }

    ~Downloader() {
        run_ = false;
        for (auto& worker : workers_) {
            task_queue_.Push(std::string(empty_task));
            auto id = worker->get_id();
            worker->join();
            std::cout << "thread " << thread_names_[id] << std::endl << " exit";
        }
    }

   private:
    void worker() {
        while (run_) {
            auto url = task_queue_.Pop();
            if (url.empty()) {
                using namespace std::chrono_literals;
            } else {
                download(std::move(url));
            }
        }
    }

    void download(std::string&& task) {
        if (task == empty_task) {
            return;
        }
        std::stringstream cmd;
        cmd << "youtube-dl " << task.data();
        std::cout << thread_names_[std::this_thread::get_id()] << " " << cmd.str() << std::endl;
        system(cmd.str().c_str());
    }

   private:
    TaskQueue& task_queue_;
    std::vector<std::unique_ptr<std::thread>> workers_;
    std::atomic_bool run_{true};
    std::map<std::thread::id, std::string> thread_names_;
    const std::string empty_task{" "};  // used for exit
};