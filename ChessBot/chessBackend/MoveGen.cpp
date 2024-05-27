#pragma once
#include "MoveGen.h"
namespace chessBackend{
    inline uint64_t MoveGenerator::genSliderMoves(const uint64_t& blockers, const uint8_t& square, const slider& piece) {
        uint8_t shift = getMagicShift(blockers, square);
        int index = 0;
        switch (piece) {
            case rook:   index = getIndexToShift(blockers, rookMagics[square]);   return precompRookMoves[square][index];   break; //rook
            case bishop: index = getIndexToShift(blockers, bishopMagics[square]); return precompBishopMoves[square][index]; break; //bishop
            case queen:  return (genSliderMoves(blockers, square, rook) | genSliderMoves(blockers, square, bishop)); //queen is just bishop + rook
        }
    }

    void MoveGenerator::genCaptures() {

    }

    void MoveGenerator::genChecks() {

    }

    void MoveGenerator::genMoves() {

    }

    Move MoveGenerator::getBestMove(const uint8_t& searchDepth) {
        return bestMove;
    }

    MoveGenerator::MoveGenerator() {
        for (uint8_t i = 0; i < 64; i++) {
            precompKnightMoves[i] = 0;
            precompKingMoves[i] = 0;
            precompWhitePawnMoves[i] = 0;
            precompBlackPawnMoves[i] = 0;
            emptyRookMoves[i] = 0;
            emptyBishopMoves[i] = 0;
            precompPowOfTwo[i] = powOfTwo<uint64_t>(i);
        }

        for (uint8_t i = 0; i < 64; i++) {
            for (int8_t j = i - 7; ((((j / 8) < 7) && ((j & 7) <= 7)) && (((j / 8) >= 0) && ((j & 7) > 0))); j -= 7) emptyBishopMoves[i] |= precompPowOfTwo[j];
            for (int8_t j = i + 7; ((((j / 8) <= 7) && ((j & 7) < 7)) && (((j / 8) > 0) && ((j & 7) >= 0))); j += 7) emptyBishopMoves[i] |= precompPowOfTwo[j];
            for (int8_t j = i - 9; ((((j / 8) < 7) && ((j & 7) < 7)) && (((j / 8) >= 0) && ((j & 7) >= 0))); j -= 9) emptyBishopMoves[i] |= precompPowOfTwo[j];
            for (int8_t j = i + 9; ((((j / 8) <= 7) && ((j & 7) <= 7)) && (((j / 8) > 0) && ((j & 7) > 0))); j += 9) emptyBishopMoves[i] |= precompPowOfTwo[j];

            uint8_t row = i >> 3;   //x / 8 == x >> 3
            uint8_t column = i & 7; //x % 8 == x & 7

            if (row > 0) {
                for (int8_t j = row - 1; j >= 0; j--) emptyRookMoves[i] |= precompPowOfTwo[(j << 3) + column];

                precompWhitePawnMoves[i] |= precompPowOfTwo[i - 8];
                if (row == 6) precompWhitePawnMoves[i] |= precompPowOfTwo[i - 16];

                precompKingMoves[i] |= precompPowOfTwo[i - 8];
                if (column > 0) {
                    precompKingMoves[i] |= precompPowOfTwo[i - 9];
                }
                if (column < 7) {
                    precompKingMoves[i] |= precompPowOfTwo[i - 7];
                }
            }

            if (row < 7) {
                for (int8_t j = row + 1; j <= 7; j++) emptyRookMoves[i] |= precompPowOfTwo[(j << 3) + column];

                precompBlackPawnMoves[i] |= precompPowOfTwo[i + 8];
                if (row == 1) precompBlackPawnMoves[i] |= precompPowOfTwo[i + 16];

                precompKingMoves[i] |= precompPowOfTwo[i + 8];
                if (column > 0) precompKingMoves[i] |= precompPowOfTwo[i + 7];
                if (column < 7) precompKingMoves[i] |= precompPowOfTwo[i + 9];
            }

            if (column > 0) {
                for (int8_t j = column - 1; j >= 0; j--) emptyRookMoves[i] |= precompPowOfTwo[j + (row << 3)];
                precompKingMoves[i] |= precompPowOfTwo[i - 1];

                if (column > 1) {
                    if (row < 7) precompKnightMoves[i] |= precompPowOfTwo[i + 6];
                    if (row > 0) precompKnightMoves[i] |= precompPowOfTwo[i - 10];
                }
                if (row > 1) precompKnightMoves[i] |= precompPowOfTwo[i - 17];
                if (row < 6) precompKnightMoves[i] |= precompPowOfTwo[i + 15];
            }

            if (column < 7) {
                for (int8_t j = column + 1; j <= 7; j++) emptyRookMoves[i] |= precompPowOfTwo[j + (row << 3)];
                precompKingMoves[i] |= precompPowOfTwo[i + 1];

                if (column < 6) {
                    if (row < 7) precompKnightMoves[i] |= precompPowOfTwo[i + 10];
                    if (row > 0) precompKnightMoves[i] |= precompPowOfTwo[i - 6];
                }
                if (i / 8 > 1) precompKnightMoves[i] |= precompPowOfTwo[i - 15];
                if (i / 8 < 6) precompKnightMoves[i] |= precompPowOfTwo[i + 17];
            }
        }
    }

    MoveGenerator::MoveGenerator(const Position& position, bool movingPlayer) : MoveGenerator() {

    }

    MoveGenerator::MoveGenerator(const Position& position, bool movingPlayer, bool isKingChecked) : MoveGenerator() {

    }

    MoveGenerator::~MoveGenerator() {

    }
}