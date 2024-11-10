#include <gtest/gtest.h>
#include "bencode/decoder.hpp"
#include "bencode/common.hpp"

using namespace bencode;

TEST(decoder_test, when_bencoded_integer_then_decode_integer) {
  const std::string bencoded_integer = "i123e";
  decoder dec{bencoded_integer};

  ASSERT_TRUE(dec.has_next());
  object decoded_object = dec.next();
  ASSERT_TRUE(decoded_object.is_integer());
  ASSERT_EQ(decoded_object.value<object::type::integer>(), 123);
}

TEST(decoder_test, when_bencoded_negative_integer_then_decode_integer) {
  const std::string bencoded_integer = "i-456e";
  decoder dec{bencoded_integer};

  ASSERT_TRUE(dec.has_next());
  object decoded_object = dec.next();
  ASSERT_TRUE(decoded_object.is_integer());
  ASSERT_EQ(decoded_object.value<object::type::integer>(), -456);
}

TEST(decoder_test, when_bencoded_bytestring_then_decode_bytestring) {
  const std::string bencoded_bytestring = "11:hello world";
  decoder dec{bencoded_bytestring};

  ASSERT_TRUE(dec.has_next());
  object decoded_object = dec.next();
  ASSERT_TRUE(decoded_object.is_bytestring());
  ASSERT_EQ(decoded_object.value<object::type::bytestring>(), "hello world");
}

TEST(decoder_test, when_bencoded_list_then_decode_list) {
  const std::string bencoded_list = "li123e6:foobar4:teste";
  decoder dec{bencoded_list};
  ASSERT_TRUE(dec.has_next());
  object decoded_object = dec.next();
  ASSERT_TRUE(decoded_object.is_list());

  const auto& list = decoded_object.value<object::type::list>();
  ASSERT_EQ(list.size(), 3);
  ASSERT_TRUE(list[0].is_integer());
  ASSERT_EQ(list[0].value<object::type::integer>(), 123);
  ASSERT_TRUE(list[1].is_bytestring());
  ASSERT_EQ(list[1].value<object::type::bytestring>(), "foobar");
  ASSERT_TRUE(list[2].is_bytestring());
  ASSERT_EQ(list[2].value<object::type::bytestring>(), "test");
}

TEST(decoder_test, when_bencoded_dictionary_then_decode_dictionary) {
  const std::string bencoded_dict = "d3:bar4:spam3:fooi42ee";
  decoder dec{bencoded_dict};

  ASSERT_TRUE(dec.has_next());
  object decoded_object = dec.next();
  ASSERT_TRUE(decoded_object.is_dictionary());

  const auto& dict = decoded_object.value<object::type::dictionary>();
  ASSERT_EQ(dict.size(), 2);
  ASSERT_TRUE(dict.at("bar").is_bytestring());
  ASSERT_EQ(dict.at("bar").value<object::type::bytestring>(), "spam");
  ASSERT_TRUE(dict.at("foo").is_integer());
  ASSERT_EQ(dict.at("foo").value<object::type::integer>(), 42);
}