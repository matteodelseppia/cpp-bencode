#include "encoder.hpp"

namespace bencode {

encoder& encoder::put(const object& object_) {
  details::encoder::encode_to_buffer(m_buffer, object_);
  return *this;
}

encoder& encoder::put(const bencode::object::type::integer integer_value) {
  details::encoder::encode_to_buffer(m_buffer, {integer_value});
  return *this;
}

encoder& encoder::put(const bencode::object::type::bytestring& bytestring_value) {
  details::encoder::encode_to_buffer(m_buffer, {bytestring_value});
  return *this;
}

encoder& encoder::put(const bencode::object::type::dictionary& dictionary_value) {
  details::encoder::encode_to_buffer(m_buffer, {dictionary_value});
  return *this;
}

encoder& encoder::put(const bencode::object::type::list& list_value) {
  details::encoder::encode_to_buffer(m_buffer, {list_value});
  return *this;
}

encoder& encoder::clear() {
  m_buffer.clear();
  return *this;
}

std::string encoder::str() {
  return m_buffer.str();
}

namespace details::encoder {

void encode_to_buffer(std::stringstream& buffer, const object& object_) {
    
  if (object_.is_integer()) {

    buffer << bencode::details::constants::int_delimiter;
    buffer << object_.value<bencode::object::type::integer>();
    buffer << bencode::details::constants::end_delimiter;

  } else if (object_.is_bytestring()) {

    buffer << object_.value<bencode::object::type::bytestring>().length();
    buffer << bencode::details::constants::colon_symbol;
    buffer << object_.value<bencode::object::type::bytestring>();

  } else if (object_.is_list()) {

    buffer << bencode::details::constants::list_delimiter;
    for (const auto& entry: object_.value<bencode::object::type::list>()) {
      encode_to_buffer(buffer, entry);
    }
    buffer << bencode::details::constants::end_delimiter;

  } else {
    
    buffer << bencode::details::constants::dictionary_delimiter;
    for (const auto& entry: object_.value<bencode::object::type::dictionary>()) {
      encode_to_buffer(buffer, object{entry.first});
      encode_to_buffer(buffer, entry.second);
    }
    buffer << bencode::details::constants::end_delimiter;

  }
  
}

} // namespace bencode::details::encoder

} // namespace bencode::encoder

