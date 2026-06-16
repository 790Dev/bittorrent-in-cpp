#pragma once

#include <vector>
#include <string>

class PieceHashVerifier
{
public:

    static bool verify(
        const std::vector<char>& pieceData,
        const std::string& expectedHash
    );

    static std::string calculateHash(
        const std::vector<char>& pieceData
    );
};