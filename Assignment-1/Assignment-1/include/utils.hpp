/**
 * ! Don't change anything in this file.
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <string>
#include <vector>

/**
 * @brief Remove trailing zeros from a number
 */
std::string removeTrailingZeros(long double);

/**
 * @brief Breaks string into list of strings using whitespaces as separators
 */
std::vector<std::string> str_split(std::string);

#endif  // UTILS_HPP
