#pragma once

#include <vector>

class PieceManager
{
public:

    PieceManager(int totalPieces);

    bool isComplete() const;

    int getNextMissingPiece();

    void markComplete(int pieceIndex);

private:

    std::vector<bool> completed;
};
