add_library(cru_regex_parser STATIC RegexLexer.cpp RegexParser.cpp)
target_link_libraries(cru_regex_parser PUBLIC cru_parsing_common)
