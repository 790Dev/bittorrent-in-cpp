#pragma once

#include <string>
#include "BencodeValue.h"

class BencodeParser {

public:

    static std::string parseString(
        const std::string& data,
        size_t& pos
    );

    static long long parseInteger(
        const std::string& data,
        size_t& pos
    );

    static BencodeList parseList(
        const std::string& data,
        size_t& pos
    );

    static BencodeDict parseDictionary(
        const std::string& data,
        size_t& pos
    );

    static BencodeValue parse(
        const std::string& data,
        size_t& pos
    );
};