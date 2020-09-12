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
#include <utility>
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

    explicit Downloader() {
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
        std::cout << __FUNCTION__ << std::endl;
    }

   private:
    void worker() {
        while (run_) {
            auto task = TaskStore::GetInstance().GetPendingList().Pop();
            if (!task) {
                std::this_thread::yield();
            } else {
                download(std::move(task));
            }
        }
    }

    void download(task_ptr task) {
        assert(task);
        std::cout << thread_names_[std::this_thread::get_id()] << " start to work" << std::endl;

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
        ps.get_exit_status();
        TaskStore::GetInstance().RemoveDownloadingTask(task);
        TaskStore::GetInstance().AddDownloadedTask(task);
    }

    static void update_download_progress(const string_type& str, const task_ptr& task) {
        static constexpr auto kIndexProgress = 1;
        static constexpr auto kIndexTotalSize = kIndexProgress + 2;
        static constexpr auto kIndexSpeed = kIndexTotalSize + 2;
        static constexpr auto kIndexEta = kIndexSpeed + 2;
        auto res = split_string(str, " ");

        // complete message
        if (res.size() < kIndexEta + 1) {
            return;
        }

        task->Update(std::move(res[kIndexProgress]),
                     std::move(res[kIndexTotalSize]),
                     std::move(res[kIndexSpeed]),
                     std::move(res[kIndexEta]));
    }

    static void update_file_name(const string_type& str, const task_ptr& task) {
        constexpr std::string_view kKey = "Destination:";
        auto pos = str.find(kKey);
        if (pos != string_type::npos) {
            task->SetFullPath(str.substr(pos + kKey.size()));
        }
    }

    std::vector<std::unique_ptr<std::thread>> workers_;
    std::atomic_bool run_{true};
    std::map<std::thread::id, string_type> thread_names_;
};