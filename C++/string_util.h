//
// Created by Daniel Hametner on 10/01/2021.
//

#ifndef KNN_STRING_UTIL_H
#define KNN_STRING_UTIL_H

// system includes
#include <vector>
#include <string>

using namespace std;

/**
 * This method is to split strings into a vector.
 *
 * @param str is the input string to be decomposed by the delimiter
 * @param del is the delimiter that indicates to split the input string
 * @return vector of strings
 */
static std::vector<string> split_str(const string &str, const string &del) {
    std::vector<string> tokens;
    size_t pos = 0;
    size_t prev = pos;

    do {
        pos = str.find(del, prev);

        if (pos == string::npos)
            pos = str.length();

        string token = str.substr(prev, pos - prev);

        if (!token.empty())
            tokens.push_back(token);

        prev = pos + del.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

#endif // KNN_STRING_UTIL_H
