#pragma once

#include <string>

#include "object.hpp"

namespace bencode {

class bad_bencode_exception : public std::exception {
public:
  bad_bencode_exception(std::string_view message) : m_message(message) {}

  const char* what() const noexcept override {
    return m_message.data();
  }

private:
    std::string_view m_message;
};

class decoder {
public:
  decoder(std::string_view);
  decoder(const std::string&);
  object next();
  bool has_next() const;

private:
  size_t m_index = 0; 
  std::string m_string;
};

namespace details::decoder {

bool has_next(std::string_view, const size_t);
object next(std::string_view, size_t&);
object next_integer(std::string_view, size_t&);
object next_bytestring(std::string_view, size_t&);
object next_list(std::string_view, size_t&);
object next_dictionary(std::string_view, size_t&);

} // namespace bencode::details::decoder


} // namespace bencode