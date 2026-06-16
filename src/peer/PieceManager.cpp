#include "PieceManager.h"

PieceManager::PieceManager(int totalPieces)
    : completed(totalPieces, false)
{
}

bool PieceManager::isComplete() const
{
    for(bool val : completed)
    {
        if(!val)
        {
            return false;
        }
    }
    return true;
}

int PieceManager::getNextMissingPiece()
{
    for(size_t i = 0; i < completed.size(); i++)
    {
        if(!completed[i])
        {
            return (int)i;
        }
    }
    return -1;
}

void PieceManager::markComplete(int pieceIndex)
{
    if(pieceIndex >= 0 && pieceIndex < (int)completed.size())
    {
        completed[pieceIndex] = true;
    }
}
