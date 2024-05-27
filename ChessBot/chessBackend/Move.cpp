#pragma once
#include "Move.h"
namespace chessBackend {
    Move::Move() {

    }

    Move::Move(Position& position, const uint8_t& startSqr, const uint8_t& endSqr, const uint8_t& piece) {
        this->startSqr = startSqr; this->endSqr = endSqr; this->piece = piece;
        if (position.isOccupied(endSqr)) this->isCapture = true;
    }

    Move::Move(Position& position, const uint8_t& startSqr, const uint8_t& endSqr, const uint8_t& piece, bool isCapture) {
        this->startSqr = startSqr; this->endSqr = endSqr; this->piece = piece;
        this->isCapture = isCapture;
    }

    Move::~Move() {

    }

    void Move::applyCaptureTo(Position& position) {
        uint64_t squareBitboard = toSquareLong(endSqr);
        position.pieceBitboards[position.squareOccupier(endSqr)] -= squareBitboard;
    }

    void Move::applyTo(Position& position) {
        if (isCapture) applyCaptureTo(position);
        uint64_t squareBitboard = toSquareLong(endSqr);
        position.pieceBitboards[position.squareOccupier(startSqr)] -= squareBitboard;
        position.pieceBitboards[position.squareOccupier(startSqr)] -= squareBitboard;
    }

    bool Move::isKingSafe(const Position& position) {
        return 1;
    }

    bool Move::isLegal(const Position& position) {
        return isKingSafe(position);
        return 0;
    }
}