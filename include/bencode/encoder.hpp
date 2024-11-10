#pragma once

#include <sstream>

#include "common.hpp"
#include "object.hpp"

namespace bencode {

class encoder {
public:
  encoder& put(const object&);
  encoder& put(const bencode::object::type::integer);
  encoder& put(const bencode::object::type::bytestring&);
  encoder& put(const bencode::object::type::dictionary&);
  encoder& put(const bencode::object::type::list&);
  encoder& clear();
  std::string str();
  
private:
  std::stringstream m_buffer;
};

namespace details::encoder {

void encode_to_buffer(std::stringstream&, const object&);

} // namespace bencode::details::encoder

} // namespace bencode
