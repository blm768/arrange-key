#include "unicode.h"

#include <memory>

std::vector<std::string> code_point_names(std::string text) {
    std::vector<std::string> names;
    // Make an approximate reservation to start.
    names.reserve(text.size());

    // Set up the UText object.
    UText utext = UTEXT_INITIALIZER;
    UErrorCode error = U_ZERO_ERROR;
    utext_openUTF8(&utext, text.data(), text.size(), &error);
    if(error != U_ZERO_ERROR) {
        // TODO: handle this more usefully.
        return names;
    }

    // Iterate over code points.
    while(true) {
        auto c = utext_next32(&utext);
        // Have we reached the end?
        if(c == U_SENTINEL) break;

        // TODO: use the alias name if the character has one.
        // Find the length of the character name.
        size_t name_len = u_charName(c, U_UNICODE_CHAR_NAME, nullptr, 0, &error);
        // TODO: check error code. (Either U_BUFFER_OVERFLOW_ERROR or U_STRING_NOT_TERMINATED_WARNING would be expected.)

        if(name_len == 0) {
            names.push_back("(unknown)");
        } else {
            // TODO: use alloca() instead?
            char* name = new char[name_len + 1];
            error = U_ZERO_ERROR;
            u_charName(c, U_UNICODE_CHAR_NAME, name, name_len + 1, &error);
            // TODO: check error code just in case?
            names.push_back(std::string(name));
            delete[] name;
        }
    }

    utext_close(&utext);
    return names;
}
