#include "decoder.hpp"
#include "common.hpp"

namespace bencode {

decoder::decoder(std::string_view string) : m_string(string) {}

decoder::decoder(const std::string& string) : m_string(string) {}

bool decoder::has_next() const {
  return details::decoder::has_next(m_string, m_index);
}

object decoder::next() {
  if (!has_next())
    throw bad_bencode_exception{"Nothing to decode"};
  
  return details::decoder::next(m_string, m_index);
}

namespace details::decoder {

bool has_next(std::string_view string, const size_t index) {
  return index < string.length();
}

static void check_out_of_bounds(std::string_view string, const size_t index) {
  if (!has_next(string, index))
    throw bad_bencode_exception{"Ill-formed bencoding: unexpected end of string"};
}

object next(std::string_view string, size_t& index) {
  check_out_of_bounds(string, index);

  switch (string[index]) {
    case details::constants::int_delimiter:
      return next_integer(string, ++index);

    case details::constants::list_delimiter:
      return next_list(string, ++index);
      
    case details::constants::dictionary_delimiter:
      return next_dictionary(string, ++index);

    default:
      if (std::isdigit(string[index]))
        return next_bytestring(string, index);

      throw bad_bencode_exception{
        "Error: decoding unknown data type: " 
        + std::string(1, string[index]) 
        + "at position " 
        + std::to_string(index)
      };
  }
}

object next_integer(std::string_view string, size_t& index) {
  check_out_of_bounds(string, index);
  const size_t pos = string.find_first_of(details::constants::end_delimiter, index);
  if (pos == std::string::npos) {
    throw bad_bencode_exception{"Error: invalid integer format: delimiter not found"};
  }

  const std::string_view num_str = string.substr(index, pos - index);

  if (num_str.empty()) {
    throw bad_bencode_exception{"Error: invalid integer format: empty string"};
  }

  if (num_str[0] == '-' && num_str == "-0") {
    throw bad_bencode_exception{"Error: invalid integer format: negative zero"};
  } else if (num_str[0] == '0' && num_str.length() > 1) {
    throw bad_bencode_exception{"Error: invalid integer format: leading zero"};
  }
  
  index = pos + 1;

  try {
    int64_t n = std::stoll(std::string(num_str));
    return object{n};
  } catch (...) {
    throw bad_bencode_exception{"Error: invalid integer format"};
  }
}

object next_bytestring(std::string_view string, size_t& index) {
  check_out_of_bounds(string, index);
  const size_t colon_pos = string.find(details::constants::colon_symbol, index);
  if (colon_pos == std::string::npos) {
    throw bad_bencode_exception{"Error: invalid byte string format: colon delimiter not found"};
  }

  const std::string_view length_str = string.substr(index, colon_pos - index);
  size_t length;
  try {
    length = std::stoul(std::string(length_str));
  } catch (...) {
    throw bad_bencode_exception{"Error: invalid byte string format: invalid length format"};
  }

  index = colon_pos + 1;

  if (index + length > string.size()) {
    throw bad_bencode_exception{
      "Error: invalid byte string format: declared string length exceeds data length"};
  }

  const std::string_view str = string.substr(index, length);
  index += length;

  return object{std::string(str)};
}

object next_list(std::string_view string, size_t& index) {
  check_out_of_bounds(string, index);
  std::vector<object> list;

  while (has_next(string, index) && string[index] != details::constants::end_delimiter) {
    object next_ = next(string, index);
    list.push_back(next_);
  }
  
  index++;
  return object{list};  
}

object next_dictionary(std::string_view string, size_t& index) {
  check_out_of_bounds(string, index);
  std::unordered_map<std::string, object> dict;

  while (has_next(string, index) && string[index] != details::constants::end_delimiter) {
    if (!std::isdigit(string[index])) {
      throw bad_bencode_exception{"Error: invalid dictionary format: key must be a byte string"};
    }

    object key_item = next_bytestring(string, index);
    object value = next(string, index);

    dict.emplace(key_item.value<bencode::object::type::bytestring>(), std::move(value)); 
  }

  index++;
  return object{dict};
}

} // namespace bencode::details::decoder

} // namespace bencode