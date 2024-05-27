#pragma once
#include "MoveGen.cpp"
namespace chessBackend{
    class Game {
        private:
            std::string startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            std::string currentFEN;
            int botElo = 1000;
            int timeControl = 1;
            bool playerColor = 1;
            bool movingPlayer = 1;
            std::list<Position> positionList; //Позиція як клас щоб круто використати список позицій як список ходів впродовж партії
            std::list<Move> moveList;
        public:
            Position currentPosition;
            void eraseGame();
            Game();
            Game(const std::string &startingFEN, int botElo, int timeControl, bool playerColor);
            Game(int botElo, int timeControl, bool playerColor);
            void makeMove(Move &move);
            void undoMove();
            ~Game();
    };
}