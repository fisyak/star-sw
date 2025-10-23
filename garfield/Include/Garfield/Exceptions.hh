#ifndef G_EXCEPTIONS
#define G_EXCEPTIONS

#include <stdexcept>
#include <string>
#if __cplusplus >= 202002L || _MSVC_LANG >= 202002L
#include <source_location>
#else
#include <cstdint>
#if !defined(__has_builtin)
#define __has_builtin(builtin) OL
#endif
namespace Garfield {

class source_location {
 public:
#if __has_builtin(__builtin_COLUMN) || (defined(_MSC_VER) && _MSC_VER > 1925)
  inline static source_location current(
      const std::uint_least32_t line = __builtin_LINE(),
      const std::uint_least32_t column = __builtin_COLUMN(),
      const char* file_name = __builtin_FILE(),
      const char* function_name = __builtin_FUNCTION()) noexcept
#elif defined(__GNUC__) and \
    (__GNUC__ > 4 or (__GNUC__ == 4 and __GNUC_MINOR__ >= 8))
  inline static source_location current(
      const std::uint_least32_t line = __builtin_LINE(),
      const std::uint_least32_t column = 0,
      const char* file_name = __builtin_FILE(),
      const char* function_name = __builtin_FUNCTION()) noexcept
#else
  inline static source_location current(
      const std::uint_least32_t line = 0, const std::uint_least32_t column = 0,
      const char* file_name = "unsupported !",
      const char* function_name = "unsupported !") noexcept
#endif
  {
    return source_location(line, column, file_name, function_name);
  }
  explicit source_location(const std::uint_least32_t line = 0,
                           const std::uint_least32_t column = 0,
                           const char* file_name = "unsupported !",
                           const char* function_name = "unsupported !") noexcept
      : m_line(line),
        m_column(column),
        m_file_name(file_name),
        m_function_name(function_name) {}
  explicit source_location() = default;
  constexpr std::uint_least32_t line() const noexcept { return m_line; }
  constexpr std::uint_least32_t column() const noexcept { return m_column; }
  constexpr const char* file_name() const noexcept { return m_file_name; }
  constexpr const char* function_name() const noexcept {
    return m_function_name;
  }

 private:
  const std::uint_least32_t m_line{0};
  const std::uint_least32_t m_column{0};
  const char* m_file_name;
  const char* m_function_name;
};

}  // namespace Garfield
#endif

namespace Garfield {

class Exception : public std::runtime_error {
 public:
#if __cplusplus >= 202002L || _MSVC_LANG >= 202002L
  explicit Exception(
      const char* const message,
      const std::source_location& location = std::source_location::current())
      : std::runtime_error(message), m_source_location(location) {}
#else
  inline explicit Exception(
      const char* const message,
      const source_location& location = source_location::current())
      : std::runtime_error(message), m_source_location(location) {}
#endif
  virtual const char* what() const noexcept {
    try {
      static thread_local std::string full_message;
      full_message.clear();
      full_message = std::runtime_error::what();
      full_message += " in " + std::string(m_source_location.function_name()) +
                      " at " + std::string(m_source_location.file_name()) +
                      ":" + std::to_string(m_source_location.line()) + ":" +
                      std::to_string(m_source_location.column());
      return full_message.c_str();
    } catch (...) {
      return std::runtime_error::what();
    }
  }

 private:
#if __cplusplus >= 202002L || _MSVC_LANG >= 202002L
  std::source_location m_source_location;
#else
  source_location m_source_location;
#endif
};

}  // namespace Garfield

#endif