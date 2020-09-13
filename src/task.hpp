#pragma once

#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>

#include "tiny_process/process.hpp"
#include "utility.hpp"

class Task final {
   public:
    using task_ptr = std::shared_ptr<Task>;
    using string_type = TinyProcessLib::Process::string_type;
    using clock_type = std::chrono::system_clock;

    explicit Task(string_type&& url) : url_(url) {}
    Task() = default;
    Task(const Task& rhs) {
        std::lock_guard<std::mutex> lock(rhs.progress_mutex_);
        url_ = rhs.url_;
        full_path_ = rhs.full_path_;
        progress_ = rhs.progress_;
    }

    Task(Task&& rhs) noexcept {
        std::lock_guard<std::mutex> lock(rhs.progress_mutex_);
        url_ = std::move(rhs.url_);
        full_path_ = std::move(rhs.full_path_);
        progress_ = rhs.progress_;
    }

    bool operator==(const Task& rhs) const {
        return url_ == rhs.url_;
    }

    auto IsEmpty() {
        return url_.empty();
    }

    auto GetUrl() {
        return url_;
    }

    void SetURL(string_type&& url) {
        url_ = url;
    }

    void SetFullPath(string_type&& path) {
        full_path_ = path;
    }

    [[nodiscard]] auto GetFullPath() const {
        return full_path_;
    }

    [[nodiscard]] auto GetProgress() const {
        std::lock_guard<std::mutex> lock(progress_mutex_);
        return progress_;
    }

    auto Update(string_type&& v, const string_type&& total_size, string_type&& speed,
                string_type&& eta) {
        std::lock_guard<std::mutex> lock(progress_mutex_);
        progress_ = v;
        total_size_ = total_size;
        speed_ = speed;
        eta_ = eta;
    }

    auto GetSpeed() const {
        std::lock_guard<std::mutex> lock(progress_mutex_);
        return speed_ + " | " + eta_;
    }

    auto GetProgressAndSize() const {
        std::lock_guard<std::mutex> lock(progress_mutex_);
        return progress_ + "/" + total_size_;
    }

    auto SetEndTime(clock_type::time_point tp) {
        end_ = tp;
    }

    auto GetElapsedTime() const {
        return duration_to_stirng(end_ - start_);
    }

   private:
    string_type url_;
    string_type full_path_;
    string_type total_size_;
    string_type speed_;
    string_type eta_;
    string_type progress_ = {};
    mutable std::mutex progress_mutex_;

    std::chrono::time_point<clock_type> start_ = clock_type::now();
    std::chrono::time_point<clock_type> end_;
};