#pragma once
#include "Game.h"
namespace chessBackend {
    //Конструктор за замовчуванням
    Game::Game() {
        movingPlayer = currentPosition.movingPlayer;
    }

    //конструктор партії з кастомної позиції
    Game::Game(const std::string& startingFEN, int botElo, int timeControl, bool playerColor) : Game() {
        this->startingFEN = startingFEN;
        this->botElo = botElo;
        this->timeControl = timeControl;
        this->playerColor = playerColor;
        currentPosition.setFromFEN(startingFEN);
    }

    Game::Game(int botElo, int timeControl, bool playerColor) : Game() {
        this->botElo = botElo;
        this->timeControl = timeControl;
        this->playerColor = playerColor;
        currentPosition.setFromFEN(startingFEN);
    }

    //деструктор
    Game::~Game() {

    }

    void Game::eraseGame() {
        moveList.clear(); positionList.clear();
    }

    void Game::makeMove(Move& move) {
        move.applyTo(currentPosition);
        positionList.push_back(currentPosition);
        movingPlayer = !movingPlayer;
    }

    void Game::undoMove() {
        positionList.pop_back();
        currentPosition = positionList.back();
        movingPlayer = !movingPlayer;
    }
}