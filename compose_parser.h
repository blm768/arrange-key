#ifndef _COMPOSE_PARSER_H
#define _COMPOSE_PARSER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct ComposeEntry {
    std::vector<std::string> key_codes;
    std::vector<std::string> result;
};

enum class ComposeTokenType {
    keysym,
    result_string,
    result_keysym,
};

class ComposeLineLexer {
public:
    ComposeLineLexer(std::string&& text);

private:
    void skip_whitespace();
    void skip_comments();
    std::string _text;
};

/**
 * Parses compose key bindings from an X11 configuration file
 */
std::vector<ComposeEntry> parse_compose_bindings(std::istream& stream);


#endif
