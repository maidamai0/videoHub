#pragma once

#include <array>
#include <string>
#include <type_traits>
#include <vector>

// #include "doctest/doctest.h"

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

// TEST_CASE("utility_split_string") {
//     SUBCASE("full path") {
//         auto res = split_string(
//             "[download] Destination: Was Biden's trip to Kenosha too late Trump thinks "
//             "so-u9aQlB05gPQ.mp4",
//             " ");
//         CHECK(res[0] == std::string("[download]"));
//         CHECK(res[1] == std::string("Destination:"));
//         CHECK(res.back() == std::string("so-u9aQlB05gPQ.mp4"));
//     }

//     SUBCASE("progress") {
//         auto res = split_string(R"([download]   0.0% of 45.17MiB at 70.71KiB/s ETA 10:54)", " ");
//         CHECK(res[0] == std::string("[download]"));
//         CHECK(res[1] == std::string(R"(0.0%)"));
//         CHECK(res[3] == std::string(R"(45.17MiB)"));
//         CHECK(res[5] == std::string(R"(70.71KiB/s)"));
//         CHECK(res[7] == std::string(R"(10:54)"));
//     }
// }

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