#include "RegexLexer.hpp"
#include "../Common/ParsingException.hpp"

namespace cru {
namespace parsing {
std::vector<RegexToken> RegexLexer::Parse(std::string_view regex) {
  std::vector<RegexToken> tokens;

  auto iterator = regex.cbegin();
  bool escape = false;

  while (iterator != regex.cend()) {
    char current = *iterator;

    if (escape) {
      switch (current) {
      case '\\':
      case '*':
      case '(':
      case ')':
      case '|': {
        tokens.push_back(RegexToken::Alphabet({current}));
      } break;
      default:
        throw ParsingException("Invalid escape character after \\.",
                               iterator - regex.cbegin() + 1);
      }
      escape = false;
    } else {
      switch (current) {
      case '\\': {
        escape = true;
      } break;
      case '(': {
        tokens.push_back(RegexToken::LeftParenthesis());
      } break;
      case ')': {
        tokens.push_back(RegexToken::RightParenthesis());
      } break;
      case '*': {
        tokens.push_back(RegexToken::Asterisk());
      } break;
      case '|': {
        tokens.push_back(RegexToken::Or());
      } break;
      default: {
        tokens.push_back(RegexToken::Alphabet({current}));
      } break;
      }
    }
    ++iterator;
  }

  if (escape) {
    throw ParsingException("Invalid ending \\.", regex.size());
  }

  return tokens;
}
} // namespace parsing
} // namespace cru
