#include <gtest/gtest.h>

#include "bencode/object.hpp"

TEST(object_test, when_object_integer_then_get_integer) {
  constexpr int64_t integer = 5;
  bencode::object object{integer};
  ASSERT_EQ(object.get_type(), bencode::object::type::integer);
  ASSERT_EQ(object.value<int64_t>(), integer);
}

TEST(object_test, when_object_stringview_then_get_stringview) {
  constexpr std::string_view test_str = "test string";
  bencode::object object{test_str};
  ASSERT_EQ(object.get_type(), bencode::object::type::bytestring);
  ASSERT_EQ(object.value<std::string_view>(), test_str);
}


