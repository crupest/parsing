#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace cru {
namespace parsing {

enum class RegexTokenType {
  Alphabet,        // Any single character.
  Asterisk,        // *
  Or,              // |
  LeftParenthesis, // (
  RightParenthesis // )
};

struct RegexToken {

  static RegexToken Alphabet(std::string character) {
    return RegexToken{RegexTokenType::Alphabet, std::move(character)};
  }

  static RegexToken Asterisk() { return RegexToken{RegexTokenType::Asterisk}; }

  static RegexToken Or() { return RegexToken{RegexTokenType::Or}; }

  static RegexToken LeftParenthesis() {
    return RegexToken{RegexTokenType::LeftParenthesis};
  }

  static RegexToken RightParenthesis() {
    return RegexToken{RegexTokenType::RightParenthesis};
  }

  explicit RegexToken(RegexTokenType type) : type(type) {}

  RegexToken(RegexTokenType type, std::string character)
      : type(type), character(std::move(character)) {}

  RegexTokenType type;
  // Only used if type is alphabet.
  std::string character;
};

class RegexLexer {
public:
  std::vector<RegexToken> Parse(std::string_view regex);
};

} // namespace parsing
} // namespace cru
