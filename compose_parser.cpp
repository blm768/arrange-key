#include "compose_parser.h"

ComposeLineLexer::ComposeLineLexer(std::string&& text) : _text(text) {}

std::vector<ComposeEntry> parse_compose_bindings(std::istream& stream) {
    std::vector<ComposeEntry> entries;

    std::string line;
    while(std::getline(stream, line)) {
        // TODO: implement.
    }

    return entries;
}
