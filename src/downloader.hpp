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

#include <algorithm>
#include <atomic>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <vector>

#include "task.hpp"
#include "task_queue.hpp"
#include "task_store.hpp"
#include "tiny_process/process.hpp"
#include "utility.hpp"

class Downloader final {
   public:
    using string_type = Task::string_type;
    using task_ptr = Task::task_ptr;

    explicit Downloader(TaskQueue& queue) : task_queue_(queue) {
        const auto size = std::thread::hardware_concurrency();
        for (std::remove_const<decltype(size)>::type i = 0; i < size; ++i) {
            workers_.push_back(std::make_unique<std::thread>(&Downloader::worker, this));
            thread_names_[workers_.back()->get_id()] = string_type{"worker #"} + std::to_string(i);
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
            auto task = task_queue_.Pop();
            if (!task) {
                std::this_thread::yield();
            } else {
                download(std::move(task));
            }
        }
    }

    static void download(task_ptr task) {
        assert(task);

        auto cout = [&task](const char* bytes, size_t n) {
            auto log = string_type(bytes, n);

            if (unlikely(task->GetFullPath().empty())) {
                update_file_name(log, task);
            } else {
                update_download_progress(log, task);
            }

            std::cout << log;
            // auto split = split_string(string_type(bytes), " ");
            // fmt::print("{}\n", split);
            if (bytes[n - 1] != '\n') {
                std::cout << "\n";
            }
            std::flush(std::cout);
        };

        auto cerr = [](const char* bytes, size_t n) {
            std::cout << string_type(bytes, n);
            if (bytes[n - 1] != '\n') {
                std::cout << "\n";
            }
            std::flush(std::cout);
        };

        TaskStore::GetInstance().AddDownloadingTask(task);

        std::vector<string_type> cmd{string_type{"youtube-dl"}, task->GetUrl()};
        TinyProcessLib::Process ps{cmd, "", cout, cerr};
        auto status = ps.get_exit_status();
        TaskStore::GetInstance().RemoveDownloadingTask(task);
    }

    static void update_download_progress(const string_type& str, const task_ptr& task) {
        static constexpr auto index_progress = 1;
        static constexpr auto index_total_size = index_progress + 2;
        static constexpr auto index_speed = index_total_size + 2;
        static constexpr auto index_eta = index_speed + 2;
        auto res = split_string(str, " ");

        // complete message
        if (res.size() < index_eta + 1) {
            return;
        }

        task->Update(
            std::stof(res[index_progress].substr(0, res[index_progress].size() - 1)) / 100.0F,
            res[index_total_size],
            res[index_speed],
            res[index_eta]);
    }

    static void update_file_name(const string_type& str, const task_ptr& task) {
        constexpr std::string_view kKey = "Destination:";
        auto pos = str.find(kKey);
        if (pos != string_type::npos) {
            task->SetFullPath(str.substr(pos + kKey.size()));
        }
    }

   private:
    TaskQueue& task_queue_;
    std::vector<std::unique_ptr<std::thread>> workers_;
    std::atomic_bool run_{true};
    std::map<std::thread::id, string_type> thread_names_;
};