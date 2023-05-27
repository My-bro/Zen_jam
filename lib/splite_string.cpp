/*
** EPITECH PROJECT, 2023
** Zen_jam
** File description:
** splite_string
*/

#include <vector>
#include <string>

std::vector<std::string> splitString(const std::string &str, const std::string &separator)
{
    std::vector<std::string> result;
    size_t start = 0, end;
    while ((end = str.find(separator, start)) != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + separator.length();
    }
    result.push_back(str.substr(start));
    return result;
}
