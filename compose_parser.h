#ifndef _COMPOSE_PARSER_H
#define _COMPOSE_PARSER_H

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

struct ComposeEntry {
    std::vector<std::string> key_codes;
    std::string result;
};

enum class ComposeTokenType {
    invalid,
    separator,
    input_keysym,
    input_modifier,
    result_string,
    result_keysym,
};

struct ComposeToken {
    ComposeToken(ComposeTokenType type) : type(type) {}
    ComposeToken(ComposeTokenType type, std::string&& text) : type(type), text(text) {}

    ComposeTokenType type;
    std::string text;
};

/**
 * @brief Lexes a single line from a compose file
 */
class ComposeLineLexer {
public:
    ComposeLineLexer(std::string& text);

    std::optional<ComposeToken> next_token();
private:
    std::string::iterator _current, _end;
};

/*
 * NOTE: we'll need to scan compose file locations properly:
 * - Check XCOMPOSEFILE or ~/.XCompose
 * - Find file for current locale in /usr/share/X11/locale/compose.dir
 */

/**
 * Parses compose key bindings from an X11 configuration file
 */
std::vector<ComposeEntry> parse_compose_bindings(std::istream& stream);


#endif
