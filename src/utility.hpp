#pragma once

#include <array>
#include <string>
#include <type_traits>
#include <vector>

#define likely(expr) (__builtin_expect(!!(expr), 1))
#define unlikely(expr) (__builtin_expect(!!(expr), 0))

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