#include "compose_parser.h"

#include <algorithm>
#include <locale>
#include <sstream>

ComposeLineLexer::ComposeLineLexer(std::string& text) : _current(text.begin()), _end(text.end()) {}

std::optional<ComposeToken> ComposeLineLexer::next_token() {
    std::optional<ComposeToken> maybe_tok;

    std::locale locale;

    // Skip whitespace.
    while(_current != _end && std::isspace(*_current, locale)) {
        ++_current;
    }

    // Skip comments.
    if(_current != _end && *_current == '#') {
        _current = _end;
    }

    if(_current == _end) return maybe_tok;

    std::string::iterator token_end = std::find_if(
        _current, _end,
        [&locale] (char c) { return std::isspace(c, locale); }
    );
    switch(*_current) {
    // TODO: handle modifiers.
    case '<':
        if(*(token_end - 1) != '>') return ComposeToken(ComposeTokenType::invalid);
        maybe_tok = ComposeToken(ComposeTokenType::input_keysym, std::string(_current + 1, token_end - 1));
        break;
    case ':':
        maybe_tok = ComposeToken(ComposeTokenType::separator);
        break;
    case '"':
        {
            auto close_quote = token_end - 1;
            if(close_quote == _current || *close_quote != '"') return ComposeToken(ComposeTokenType::invalid);
            std::stringbuf buf;
            for(auto it = _current + 1; it != close_quote; ++it) {
                // TODO: handle escape sequences.
                buf.sputc(*it);
            }
            maybe_tok = ComposeToken(ComposeTokenType::result_string, buf.str());
            break;
        }
    default:
        maybe_tok = ComposeToken(ComposeTokenType::result_keysym, std::string(_current, token_end));
    }
    _current = token_end;

    return maybe_tok;
}

std::vector<ComposeEntry> parse_compose_bindings(std::istream& stream) {
    std::vector<ComposeEntry> entries;

    std::string line;
    size_t line_num = 1;
    while(std::getline(stream, line)) {
        ComposeLineLexer lexer(line);

        ComposeEntry entry;

        auto tok = lexer.next_token();
        while(tok && tok->type == ComposeTokenType::input_keysym) {
            // TODO: handle modifiers.
            entry.key_codes.push_back(tok->text);
            tok = lexer.next_token();
        }

        if(!tok || tok->type != ComposeTokenType::separator) {
            // TODO: log errors somewhere? (Right now we just skip lines.)
            continue;
        }
        tok = lexer.next_token();

        if(!tok) continue;
        // TODO: finish parsing.
        if(tok->type == ComposeTokenType::result_string) {
            entry.result = tok->text;
        }

        // TODO: handle entries with no string?

        entries.push_back(entry);
        line_num += 1;
    }

    return entries;
}
