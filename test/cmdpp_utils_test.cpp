#include "gtest/gtest.h"

#include "cmdpp/utils.hpp"

TEST(cmdpp_utils_test, split_string_without_empty_tokens) {
    std::vector<std::string> expected{
        "This",
        "is",
        "a",
        "test",
        "message"
    };
    size_t expected_len = 5;
    std::string s("This is a test message");

    std::vector<std::string> actual = libcmd::split(s, ' ');

    size_t actual_len = actual.size();
    ASSERT_EQ(actual_len, expected_len);
    for (size_t i = 0; i < actual_len; i++) {
        ASSERT_EQ(actual[i], expected[i]);
    }
}

TEST(cmdpp_utils_test, split_string_with_empty_tokens) {
    std::vector<std::string> expected{
        "command",
        "arg1",
        "arg2",
        "arg3"
    };
    size_t expected_len = 4;
    std::string s("command  arg1    arg2 arg3");

    std::vector<std::string> actual = libcmd::split(s, ' ');

    size_t actual_len = actual.size();
    ASSERT_EQ(actual_len, expected_len);
    for (size_t i = 0; i < actual_len; i++) {
        ASSERT_EQ(actual[i], expected[i]);
    }
}
