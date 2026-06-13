#pragma once

#include <string>

#include "../bencode/BencodeValue.h"

class InfoHashGenerator
{
public:

    static std::string generate(
        const BencodeValue& root
    );

private:

    static std::string sha1(
        const std::string& data
    );
};