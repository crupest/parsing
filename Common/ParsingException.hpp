#pragma once

#include <exception>
#include <string>

namespace cru {
namespace parsing {
class ParsingException : public std::exception {
public:
  ParsingException(std::string message, int error_position)
      : message_(std::move(message)), error_position_(error_position) {}

  ParsingException(const ParsingException &) = default;
  ParsingException(ParsingException &&) = default;
  ParsingException &operator=(const ParsingException &) = default;
  ParsingException &operator=(ParsingException &&) = default;

  ~ParsingException() override = default;

public:
  const char *what() const override { return message_.c_str(); }

  int GetErrorPosition() const { return error_position_; }

private:
  std::string message_;
  int error_position_;
};
} // namespace parsing
} // namespace cru