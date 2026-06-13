#pragma once

#include <string>
#include "BencodeValue.h"

class BencodeEncoder {
public:
    static std::string encode(const BencodeValue& value);
};
