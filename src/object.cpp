#include "object.hpp"

namespace bencode {

object::type object::get_type() const {
  return m_type;
}

object::object(const int64_t integer) {
  m_type = type::integer;
  m_data = integer;
}

object::object(std::string_view bytestring_) {
  m_type = type::bytestring;
  m_data = bytestring_;
}

object::object(const std::vector<object>& objects_) {
  m_type = type::list;
  m_data = objects_;
}

object::object(const std::unordered_map<std::string_view, object>& objects_) {
  m_type = type::dictionary;
  m_data = objects_;
}

} // namespace bencode