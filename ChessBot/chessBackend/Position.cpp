#pragma once
#include "Position.h"
namespace chessBackend {

    void Position::clearPosition() {
        castlingRights = 0;
        for (uint8_t i = 0; i < 12; i++) pieceBitboards[i] = 0;

        for (uint8_t i = 0; i < 2; i++) {
            squaresAttackedBy[i] = 0;
            allPieces[i] = 0;
        }

        isWhiteChecked = 0;
        isBlackChecked = 0;


        occupiedSquares = 0;
        halfMoveCount = 0;
        castlingRights = 0;
        _50MoveRule = 0;
        enPassantSquare = 0;

        movingPlayer = 1;

    }

    void Position::operator=(const Position& other) {
        for (uint8_t i = 0; i < 12; i++) pieceBitboards[i] = other.pieceBitboards[i];
        for (uint8_t i = 0; i < 2; i++) {
            squaresAttackedBy[i] = other.squaresAttackedBy[i];
            allPieces[i] = other.allPieces[i];
        }

        isWhiteChecked = other.isWhiteChecked;
        isBlackChecked = other.isBlackChecked;

        occupiedSquares = other.occupiedSquares;
        halfMoveCount   = other.halfMoveCount;
        castlingRights  = other.castlingRights;
        _50MoveRule     = other._50MoveRule;
        enPassantSquare = other.enPassantSquare;

        movingPlayer = other.movingPlayer;
    }
    

    Position::Position() {



    }



    bool Position::getMovingPlayer() {
        return movingPlayer;
    }

    uint64_t Position::getWhitePawns() {
        return pieceBitboards[whitePawns];
    }

    uint8_t Position::getCastlingRights() {
        return castlingRights;
    }

    uint8_t Position::getEnPassantSquare() {
        return enPassantSquare;
    }



    void Position::setFromFEN(const std::string& FEN) {
        clearPosition();
        
        uint8_t pos = FEN.find(' ');
        std::string temp = FEN.substr(0, pos);
        std::string processedFEN;
        for (int i = 0; i < temp.length(); i++) if (temp[i] != '/') processedFEN += temp[i];

        const char castlingRightsFEN[4] = {
            'K','Q','k','q'
        };

        const char pieceFENStrings[12] = {
            'P','p','N','n','B','b','R','r','Q','q','K','k'
        };

        

        uint8_t bitCounter = 0;
        for (int i = 0; i < processedFEN.length(); i++) {
            if (bitCounter < '9' && bitCounter > '1')
                for (uint8_t j = 0; j < 12; j++) if (processedFEN[i] == pieceFENStrings[j]) bitSet(pieceBitboards[i], bitCounter);
                else
                  switch (processedFEN[i]) {
                    case '2': bitCounter++;    break;
                    case '3': bitCounter += 2; break;
                    case '4': bitCounter += 3; break;
                    case '5': bitCounter += 4; break;
                    case '6': bitCounter += 5; break;
                    case '7': bitCounter += 6; break;
                    case '8': bitCounter += 7; break;
            } bitCounter++;
        }



        for (uint8_t piece = 0; piece < 12; piece += 2) allPieces[white] |= pieceBitboards[piece];
        for (uint8_t piece = 0; piece < 12; piece += 2) allPieces[black] |= pieceBitboards[piece];

        occupiedSquares = allPieces[white] | allPieces[black];

        uint8_t counter = 0, i = 0;
        while (FEN[i] != ' ') {
            if (FEN[i] == '/') counter++; i++;
        }

        
        //Кінець обробки рядів дошки
        switch (FEN[++i]) {
            case 'w': movingPlayer = 1; break;
            case 'b': movingPlayer = 0; break;
            //default: cout << "Entered FEN notation is wrong"; break;
        }

        i += 2;
        if (FEN[i] != '-') {
            while (FEN[i] != ' ') {
                for (uint8_t j = 0; j < 4; j++) if (FEN[i] == castlingRightsFEN[j]) { castlingRights += 1 << j; break; }
                i++;
            }
        }

        enPassantSquare = 0;
        if (FEN[++i] != '-') {
            switch (FEN[i]) {
                case 'b': enPassantSquare = 1; break;
                case 'c': enPassantSquare = 2; break;
                case 'd': enPassantSquare = 3; break;
                case 'e': enPassantSquare = 4; break;
                case 'f': enPassantSquare = 5; break;
                case 'g': enPassantSquare = 6; break;
                case 'h': enPassantSquare = 7; break;
            } i++;
            enPassantSquare += (stringToInt<uint8_t>(FEN[i]) - 1) << 3;
        } i += 2;

        std::string amount;
        while (FEN[i] != ' ') { amount += FEN[i]; i++; }
        _50MoveRule = stringToInt<uint8_t>(amount); amount.clear(); i++;

        for (; i < FEN.length(); i++) amount += FEN[i];
        uint8_t fullMoveCount = stringToInt<uint8_t>(amount);

        halfMoveCount = fullMoveCount << 1;
        if (movingPlayer == black) fullMoveCount++;

    }



    std::string Position::toFEN() {
        std::string FEN;
        uint8_t counter = 0;
        
        const char castlingRightsFEN[4] = {
            'K','Q','k','q'
        };

        const char pieceFENStrings[12] = {
            'P','p','N','n','B','b','R','r','Q','q','K','k'
        };

        bool sawPiece = 0;
        for (uint8_t i = 0; i < 8; i++) {
            counter = 0; sawPiece = 0;
            for (uint8_t j = 0; j < 8; j++) {
                for (uint8_t i = 0; i < 12; i++)
                    if (CHECK_BIT(pieceBitboards[i], j + (i << 3))) {
                        if (counter) FEN += intToString<uint8_t>(counter, 1); counter = 0; sawPiece = 1; FEN += pieceFENStrings[i];
                    }
                    else { counter++; sawPiece = 0; }
            }  if (counter) FEN += intToString<uint8_t>(counter, 1);  if (i < 7) FEN += "/";
        }

        (movingPlayer) ? FEN += " w " : FEN += " b ";


        if (castlingRights) for (uint8_t i = 0; i < 4; i++) if (CHECK_BIT(castlingRights, i)) FEN += castlingRightsFEN[i];
        else FEN += "- ";

        FEN += toSquare(enPassantSquare); FEN += ' ';
        FEN += intToString<uint8_t>(_50MoveRule, 1); FEN += ' ';
        FEN += intToString<uint8_t>((halfMoveCount >> 1) << 2, 1);

        return FEN;
    }

    bool Position::isInCheck(bool movingPlayer) {
        if (movingPlayer) {
            if (CHECK_ANY_BIT_EQUALITY(this->squaresAttackedBy[black], this->pieceBitboards[whiteKings])) return 1;
            return 0;
        }
        if (CHECK_ANY_BIT_EQUALITY(this->squaresAttackedBy[white], this->pieceBitboards[blackKings])) return 1;
        return 0;
    }

    bool Position::isOccupied(uint8_t square) {
        if (CHECK_BIT(this->occupiedSquares, square)) return 1;
        return 0;
    }

    uint8_t Position::squareOccupier(const uint8_t &square) {
        for (uint8_t i = 0; i < 12; i++)
            if (CHECK_BIT(pieceBitboards[i], square)) return i; return 13;
    }
}