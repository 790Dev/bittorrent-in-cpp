#include "PieceMessage.h"

PieceMessage PieceMessageParser::parse(
    const std::vector<char>& payload
)
{
    PieceMessage piece;

    piece.pieceIndex =
        ((unsigned char)payload[0] << 24) |
        ((unsigned char)payload[1] << 16) |
        ((unsigned char)payload[2] << 8)  |
        ((unsigned char)payload[3]);

    piece.begin =
        ((unsigned char)payload[4] << 24) |
        ((unsigned char)payload[5] << 16) |
        ((unsigned char)payload[6] << 8)  |
        ((unsigned char)payload[7]);

    piece.block.assign(
        payload.begin() + 8,
        payload.end()
    );

    return piece;
}