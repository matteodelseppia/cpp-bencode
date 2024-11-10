#include "object.hpp"

namespace bencode {

object::object(const type::integer integer_) {
  m_data = integer_;
}

object::object(const type::bytestring& bytestring_) {
  m_data = bytestring_;
}

object::object(type::bytestring&& bytestring_) {
  m_data = std::move(std::forward<decltype(bytestring_)>(bytestring_));
}

object::object(const type::list& objects_) {
  m_data = objects_;
}

object::object(type::list&& objects_) {
  m_data = std::move(std::forward<decltype(objects_)>(objects_));
}

object::object(const type::dictionary& objects_) {
  m_data = objects_;
}

object::object(type::dictionary&& objects_) {
  m_data = std::move(std::forward<decltype(objects_)>(objects_));
}

bool object::is_integer() const { 
  return std::holds_alternative<type::integer>(m_data); 
}

bool object::is_bytestring() const { 
  return std::holds_alternative<type::bytestring>(m_data); 
}

bool object::is_list() const { 
  return std::holds_alternative<type::list>(m_data); 
}

bool object::is_dictionary() const { 
  return std::holds_alternative<type::dictionary>(m_data); 
}

} // namespace bencode