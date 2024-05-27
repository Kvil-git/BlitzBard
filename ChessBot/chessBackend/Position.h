#pragma once
#include "../resources/functions.cpp"
namespace chessBackend {
    class Position {
        friend class Move;
        friend class MoveGenerator;
    private:
        enum PieceBitboardIndices {
            whitePawns,
            blackPawns,
            whiteKnights,
            blackKnights,
            whiteBishops,
            blackBishops,
            whiteRooks,
            blackRooks,
            whiteQueens,
            blackQueens,
            whiteKings,
            blackKings
        };

        enum PieceColor {
            white,
            black
        };

        enum CastlingRights {
            whiteShortCastling = 'K',
            whiteLongCastling = 'Q',
            blackShortCastling = 'k',
            blackLongCastling = 'q'
        };

        uint64_t pieceBitboards[12];
        uint64_t allPieces[2];
        uint64_t squaresAttackedBy[2];
        uint64_t occupiedSquares = 18446462598732906495;

        uint8_t _50MoveRule = 0, halfMoveCount = 0;
        uint8_t enPassantSquare = 0;
        uint8_t castlingRights = 0b00001111;

        bool isWhiteChecked = 0;
        bool isBlackChecked = 0;


        void clearPosition();

    public:
        bool movingPlayer = 1;
        //void selector();
        void Position::operator=(const Position& other);
        void setFromFEN(const std::string& FEN);
        std::string toFEN();
        uint8_t squareOccupier(const uint8_t &square);
        bool isOccupied(uint8_t square);
        bool isInCheck(bool movingPlayer);
        
        uint8_t getCastlingRights();
        uint8_t getEnPassantSquare();
        bool getMovingPlayer();
        uint64_t getWhitePawns();
        Position();
    };
}