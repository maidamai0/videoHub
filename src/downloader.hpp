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
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#include "task_queue.hpp"
#include "tiny_process/process.hpp"

class Downloader final {
   public:
    explicit Downloader(TaskQueue& queue) : task_queue_(queue) {
        const auto size = std::thread::hardware_concurrency();
        for (std::remove_const<decltype(size)>::type i = 0; i < size; ++i) {
            workers_.push_back(std::make_unique<std::thread>(&Downloader::worker, this));
            thread_names_[workers_.back()->get_id()] = "worker #" + std::to_string(i);
            std::cout << "worker #" + std::to_string(i) << " started" << std::endl;
        }
    }

    ~Downloader() {
        run_ = false;
        for (auto& worker : workers_) {
            auto id = worker->get_id();
            worker->join();
            std::cout << thread_names_[id] << " exit" << std::endl;
        }
    }

   private:
    void worker() {
        while (run_) {
            auto url = task_queue_.Pop();
            if (url.empty()) {
                std::this_thread::yield();
            } else {
                download(std::move(url));
            }
        }
    }

    void download(std::string&& task) {
        assert(!task.empty());
        std::vector<std::string> cmd{"youtube-dl", task};
        auto cout = [](const char* bytes, size_t n) {
            std::cout << std::string(bytes, n);
            if (bytes[n - 1] != '\n') {
                std::cout << "\n";
            }
            std::flush(std::cout);
        };
        auto cerr = [](const char* bytes, size_t n) {
            std::cout << std::string(bytes, n);
            if (bytes[n - 1] != '\n') {
                std::cout << "\n";
            }
            std::flush(std::cout);
        };

        TinyProcessLib::Process ps{cmd, "", cout, cerr};
        const auto exit_status = ps.get_exit_status();
    }

   private:
    TaskQueue& task_queue_;
    std::vector<std::unique_ptr<std::thread>> workers_;
    std::atomic_bool run_{true};
    std::map<std::thread::id, std::string> thread_names_;
};