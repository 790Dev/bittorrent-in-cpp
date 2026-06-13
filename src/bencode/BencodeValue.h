#pragma once

#include <string>
#include <vector>
#include <map>
#include <variant>

struct BencodeValue;

using BencodeList = std::vector<BencodeValue>;
using BencodeDict = std::map<std::string, BencodeValue>;

struct BencodeValue {

    std::variant<
        std::string,
        long long,
        BencodeList,
        BencodeDict
    > value;

    BencodeValue() = default;

    BencodeValue(const std::string& s)
        : value(s) {}

    BencodeValue(const char* s)
        : value(std::string(s)) {}

    BencodeValue(long long i)
        : value(i) {}

    BencodeValue(const BencodeList& l)
        : value(l) {}

    BencodeValue(const BencodeDict& d)
        : value(d) {}
};