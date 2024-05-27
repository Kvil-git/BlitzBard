#pragma once
#include "Position.cpp"
namespace chessBackend {
    class Move {
        private:
            enum Piece {
                whitePawn,
                blackPawn,
                whiteKnight,
                blackKnight,
                whiteBishop,
                blackBishop,
                whiteRook,
                blackRook,
                whiteQueen,
                blackQueen,
                whiteKing,
                blackKing
            };

            bool legality = 0;
            bool isCapture = 0;
            uint8_t startSqr, endSqr;
            uint8_t piece;
            bool movingPlayer;

            bool isKingSafe(const Position& position);
            void applyCaptureTo(Position& position);
        public:
            bool isLegal(const Position& position);

            void applyTo(Position& position);

            Move();
            Move(Position& position, const uint8_t& startSqr, const uint8_t& endSqr, const uint8_t& piece);
            Move(Position& position, const uint8_t& startSqr, const uint8_t& endSqr, const uint8_t& piece, bool isCapture);

            ~Move();
    };
}