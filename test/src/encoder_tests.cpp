#include <gtest/gtest.h>

#include "bencode/encoder.hpp"

TEST(encoder_test, when_encode_positive_integer_then_get_encoded_integer) {
  constexpr bencode::object::type::integer integer{288832};
  const std::string expected_str = 
    bencode::details::constants::int_delimiter + 
    std::to_string(integer) + 
    bencode::details::constants::end_delimiter;

  bencode::encoder encoder;
  encoder.put(integer);
  const std::string encoded_integer = encoder.str();
  ASSERT_EQ(encoded_integer, expected_str);
}

TEST(encoder_test, when_encode_negative_integer_then_get_encoded_integer) {
  constexpr bencode::object::type::integer integer{-283482};
  const std::string expected_str = 
    bencode::details::constants::int_delimiter + 
    std::to_string(integer) + 
    bencode::details::constants::end_delimiter;

  bencode::encoder encoder;
  encoder.put(integer);
  const std::string encoded_integer = encoder.str();
  ASSERT_EQ(encoded_integer, expected_str);
}

TEST(encoder_test, when_encode_bytestring_then_get_encoded_bytestring) {
  const bencode::object::type::bytestring string{"i'm an alien 👽"};
  const std::string expected_str = 
    std::to_string(string.length()) +
    bencode::details::constants::colon_symbol +
    string;

  bencode::encoder encoder;
  encoder.put(string);
  const std::string encoded_string = encoder.str();
  ASSERT_EQ(encoded_string, expected_str);
}

TEST(encoder_test, when_encode_flat_list_then_get_encoded_list) {
  constexpr bencode::object::type::integer pos_integer{383};
  constexpr bencode::object::type::integer neg_integer{-2382};
  const bencode::object::type::bytestring string{"i'm a devil 👹"};
  const bencode::object::type::list list{
    pos_integer,
    neg_integer,
    string
  };

  const std::string expected_str =
      std::string(1, bencode::details::constants::list_delimiter) 
    + bencode::details::constants::int_delimiter
    + std::to_string(pos_integer) 
    + bencode::details::constants::end_delimiter
    + bencode::details::constants::int_delimiter
    + std::to_string(neg_integer) 
    + bencode::details::constants::end_delimiter
    + std::to_string(string.length())
    + bencode::details::constants::colon_symbol
    + string
    + bencode::details::constants::end_delimiter;

  bencode::encoder encoder;
  encoder.put(list);
  const std::string encoded_string = encoder.str();
  ASSERT_EQ(encoded_string, expected_str);
}

TEST(encoder_test, when_encode_flat_dict_then_get_encoded_dict) {
  constexpr bencode::object::type::integer pos_integer{383};
  const bencode::object::type::bytestring string{"i'm a devil 👹"};
  const bencode::object::type::bytestring first_key{"first_key"};
  const bencode::object::type::bytestring second_key{"second_key"};
  const bencode::object::type::dictionary dict{
    {first_key, pos_integer},
    {second_key, string}
  };

  const std::string expected_bytestring =
      std::string(1, bencode::details::constants::list_delimiter) 
    + bencode::details::constants::int_delimiter
    + std::to_string(pos_integer) 
    + bencode::details::constants::end_delimiter
    + std::to_string(string.length())
    + bencode::details::constants::colon_symbol
    + string
    + bencode::details::constants::end_delimiter;

  const std::string expected_first_entry =
      std::to_string(first_key.length())
    + bencode::details::constants::colon_symbol
    + first_key
    + bencode::details::constants::int_delimiter
    + std::to_string(pos_integer) 
    + bencode::details::constants::end_delimiter;

  const std::string expected_second_entry =
      std::to_string(second_key.length())
    + bencode::details::constants::colon_symbol
    + second_key
    + std::to_string(string.length())
    + bencode::details::constants::colon_symbol
    + string;

  bencode::encoder encoder;
  encoder.put(dict);
  const std::string encoded_string = encoder.str();
  ASSERT_EQ(*encoded_string.cbegin(), bencode::details::constants::dictionary_delimiter);
  ASSERT_EQ(*std::prev(encoded_string.cend()), bencode::details::constants::end_delimiter);
  ASSERT_FALSE(encoded_string.find(expected_first_entry) == std::string::npos);
  ASSERT_FALSE(encoded_string.find(expected_second_entry) == std::string::npos);
}