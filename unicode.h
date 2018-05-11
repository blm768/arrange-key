#ifndef _UNICODE_H
#define _UNICODE_H

#include <string>
#include <vector>

#include <unicode/ubrk.h>
#include <unicode/utext.h>

/**
 * Finds the Unicode alias names of all code points in the string
 */
std::vector<std::string> code_point_names(std::string text);

#endif
