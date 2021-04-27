#include "gtest/gtest.h"

#include "cmdpp/utils.hpp"

TEST(cmdpp_utils_test, split_string_into_vector) {
    std::vector<std::string> expected{
        "This",
        "is",
        "a",
        "test",
        "message"
    };
    std::string s("This is a test message");

    std::vector<std::string> actual = libcmd::split(s, ' ');

    size_t actual_len = actual.size();
    size_t expected_len = expected.size();
    ASSERT_EQ(actual_len, expected_len);
    for (size_t i = 0; i < actual_len; i++) {
        ASSERT_EQ(actual[i], expected[i]);
    }
}
