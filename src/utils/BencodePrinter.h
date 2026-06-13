#pragma once

#include "../bencode/BencodeValue.h"

class BencodePrinter {
public:
    static void print(
        const BencodeValue& value,
        int indent = 0
    );
};