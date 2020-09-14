#include "../utility.hpp"

#include <chrono>
#include <iostream>
#include <string>

#include "doctest/doctest.h"

TEST_CASE("utility_split_string") {
    SUBCASE("full path") {
        auto res = split_string(
            "[download] Destination: Was Biden's trip to Kenosha too late Trump thinks "
            "so-u9aQlB05gPQ.mp4",
            " ");
        CHECK(res[0] == std::string("[download]"));
        CHECK(res[1] == std::string("Destination:"));
        CHECK(res.back() == std::string("so-u9aQlB05gPQ.mp4"));
    }

    SUBCASE("progress") {
        auto res = split_string(R"([download]   0.0% of 45.17MiB at 70.71KiB/s ETA 10:54)", " ");
        CHECK(res[0] == std::string("[download]"));
        CHECK(res[1] == std::string(R"(0.0%)"));
        CHECK(res[3] == std::string(R"(45.17MiB)"));
        CHECK(res[5] == std::string(R"(70.71KiB/s)"));
        CHECK(res[7] == std::string(R"(10:54)"));
    }
}

TEST_CASE("utility_duration_to_stirng") {
    SUBCASE("1 sec") {
        auto str = duration_to_stirng(std::chrono::seconds(1));
        CHECK(str == "1s");
        std::cout << str << std::endl;
    }

    SUBCASE("80 sec") {
        auto str = duration_to_stirng(std::chrono::seconds(80));
        CHECK(str == "1m 20s");
        std::cout << str << std::endl;
    }

    SUBCASE("3700 sec") {
        auto str = duration_to_stirng(std::chrono::seconds(3700));
        CHECK(str == "1h 1m 40s");
        std::cout << str << std::endl;
    }
}

TEST_CASE("utility_get_name_from_quotes") {
    auto test = std::string(R"(file is "12345asddfmmm"\nfsfj)");
    CHECK(get_name_from_quotes(R"(file is "12345asddfmmm"\nfsfj)") == R"(12345asddfmmm)");
}