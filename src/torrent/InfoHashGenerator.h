#pragma once

#include <string>

#include "../bencode/BencodeValue.h"

class InfoHashGenerator
{
public:

    static std::string generate(
        const BencodeValue& root
    );

    static std::string generateHex(
        const BencodeValue& root
    );

private:

    static std::string sha1Binary(
        const std::string& data
    );

    static std::string sha1Hex(
        const std::string& data
    );
};