#pragma once

#include <vector>

class PieceStorage
{
public:

    static bool savePiece(
        int pieceIndex,
        const std::vector<char>& data
    );
};