#pragma once

#include <variant>
#include <unordered_map>
#include <vector>
#include <string>
#include <type_traits>

namespace bencode {

class object {
public:

  enum class type {
    integer,
    bytestring,
    list,
    dictionary
  };

  type get_type() const;

  object(const int64_t);
  object(std::string_view);
  object(const std::vector<object>&);
  object(const std::unordered_map<std::string_view, object>&);

  template <typename T>
  std::enable_if_t<
    std::is_same_v<std::decay_t<T>, int64_t> ||
    std::is_same_v<std::decay_t<T>, std::string_view> ||
    std::is_same_v<std::decay_t<T>, std::vector<object>> ||
    std::is_same_v<std::decay_t<T>, std::unordered_map<std::string_view, object>>,
    T
  >
  value() const {
    return std::get<T>(m_data);
  }
  
private:

  type m_type;
  std::variant<
    int64_t,
    std::string_view,
    std::vector<object>,
    std::unordered_map<std::string_view, object>
  > m_data;
};

} // namespace bencode