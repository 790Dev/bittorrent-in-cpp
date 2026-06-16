#pragma once

#include <vector>

struct PieceMessage
{
    int pieceIndex;
    int begin;

    std::vector<char> block;
};

class PieceMessageParser
{
public:

    static PieceMessage parse(
        const std::vector<char>& payload
    );
};