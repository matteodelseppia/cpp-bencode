#include <gtest/gtest.h>

#include "bencode/object.hpp"

TEST(object_test, when_object_integer_then_get_integer) {
  constexpr bencode::object::type::integer expectedInteger = 5;
  bencode::object object{expectedInteger};

  ASSERT_TRUE(object.is_integer());
  ASSERT_EQ(object.value<bencode::object::type::integer>(), expectedInteger);
}

TEST(object_test, when_object_bytestring_then_get_bytestring) {
  const bencode::object::type::bytestring expectedByteString = "👽";

  bencode::object object{expectedByteString};
  
  ASSERT_TRUE(object.is_bytestring());
  ASSERT_EQ(object.value<bencode::object::type::bytestring>(), expectedByteString);
}

TEST(object_test, when_object_list_then_get_list) {
  const bencode::object::type::list list{bencode::object{5}, bencode::object{"hello 😼"}};

  bencode::object object{list};
  
  ASSERT_TRUE(object.is_list());
  const bencode::object::type::list& ref_list = object.value<bencode::object::type::list>();
  ASSERT_EQ(ref_list.size(), list.size());
  ASSERT_EQ(ref_list.at(0).value<bencode::object::type::integer>(), 5);
  ASSERT_EQ(ref_list.at(1).value<bencode::object::type::bytestring>(), "hello 😼");
}

TEST(object_test, when_object_dict_then_get_dict) {
  const bencode::object::type::dictionary dict {
    {"first", bencode::object{5}}, 
    {"second", bencode::object{"hello 😼"}}
  };

  bencode::object object{dict};
  
  ASSERT_TRUE(object.is_dictionary());
  const bencode::object::type::dictionary& ref_map = object.value<bencode::object::type::dictionary>();
  ASSERT_EQ(ref_map.size(), dict.size());
  ASSERT_EQ(ref_map.at("first").value<bencode::object::type::integer>(), 5);
  ASSERT_EQ(ref_map.at("second").value<bencode::object::type::bytestring>(), "hello 😼");
}


