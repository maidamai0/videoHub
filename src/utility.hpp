#pragma once

#include <array>
#include <chrono>
#include <iostream>
#include <ratio>
#include <string>
#include <type_traits>
#include <vector>

#define likely(expr) (__builtin_expect(!!(expr), 1))
#define unlikely(expr) (__builtin_expect(!!(expr), 0))

constexpr auto hour_in_seconds = 3600;
constexpr auto minute_in_seconds = 60;

inline std::vector<std::string> split_string(const std::string& str, std::string&& delimiter) {
    size_t start = 0;
    size_t next = 0;
    std::vector<std::string> ret;
    while ((next = str.find(delimiter, start)) != std::string::npos) {
        auto substr = str.substr(start, next - start);
        if (!substr.empty()) {
            ret.push_back(std::move(substr));
        }
        start = next + 1;
    }
    auto last = str.substr(start);
    if (!last.empty()) {
        ret.push_back(std::move(last));
    }

    return ret;
}

inline auto interpolate(const std::array<float, 4>& start, const std::array<float, 4>& middle,
                        const std::array<float, 4>& end, const float v) {
    std::array<float, 4> ret;
    if (v < 0.5) {
        for (size_t i = 0; i < 4; ++i) {
            ret[i] = start[i] + v * (middle[i] - start[i]) / 0.5;
        }
    } else {
        for (size_t i = 0; i < 4; ++i) {
            ret[i] = middle[i] + (v - 0.5) * (end[i] - middle[i]) / 0.5;
        }
    }

    return ret;
}

inline auto duration_to_stirng(std::chrono::system_clock::duration&& dur) {
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
    std::cout << std::to_string(seconds) << " seconds is: ";
    std::string str;

    const auto hours = seconds / hour_in_seconds;
    if (hours != 0) {
        seconds %= hour_in_seconds;
        str = std::to_string(hours) + "h";
    }

    const auto minutes = seconds / minute_in_seconds;
    if (minutes != 0) {
        seconds %= minute_in_seconds;
        if (!str.empty()) {
            str.push_back(' ');
        }
        str += std::to_string(minutes) + "m";
    }

    if (!str.empty()) {
        str.push_back(' ');
    }

    str += std::to_string(seconds) + "s";

    return str;
}

inline auto get_name_from_quotes(const std::string& str) {
    const auto start = str.find('"') + 1;
    const auto end = str.rfind('"');

    return str.substr(start, end-start);
}

#ifdef _WIN32
#include "utility_win.hpp"
#endif