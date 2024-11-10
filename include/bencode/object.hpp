#pragma once

#include <variant>
#include <unordered_map>
#include <vector>
#include <string>
#include <type_traits>

namespace bencode {

class object {
public:
  struct type {
    using integer = int64_t;
    using bytestring = std::string;
    using list = std::vector<object>;
    using dictionary = std::unordered_map<std::string, object>;
  };

  object(const type::integer);
  object(const type::bytestring&);
  object(type::bytestring&&);
  object(const type::list&);
  object(type::list&&);
  object(const type::dictionary&);
  object(type::dictionary&&);

  bool is_integer() const;
  bool is_bytestring() const;
  bool is_list() const;
  bool is_dictionary() const;

  template <typename T>
  std::enable_if_t<
    std::is_same_v<T, type::integer> ||
    std::is_same_v<T, type::bytestring> ||
    std::is_same_v<T, type::list> ||
    std::is_same_v<T, type::dictionary>,
    const T&
  >
  value() const {
    return std::get<T>(m_data);
  }

  
private:

  std::variant<
    type::integer,
    type::bytestring,
    type::list,
    type::dictionary
  > m_data;
};

} // namespace bencode