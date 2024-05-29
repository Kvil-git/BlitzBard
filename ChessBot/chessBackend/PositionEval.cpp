#pragma once
#include "PositionEval.h"
namespace chessBackend {
	int PositionEval::Material(const Position& position) {
		const int middlegamePieceValue[6] = {
			82, 337, 365, 477, 1025, 0
		};

		const int engamePieceValue[6] = {
			94, 281, 297, 512,  936, 0
		};

		int material[2] = { 0,0 };

		for (uint8_t color = white; color <= black; color++) {
			for (uint8_t pieceIndex = whitePawns + color; pieceIndex <= blackKings; pieceIndex += 2) {
				(color) ? material[color] += countSetBits(position.pieceBitboards[pieceIndex]) : material[color] -= countSetBits(position.pieceBitboards[pieceIndex]);
			}
		}
		return material[black] + material[white];
	}
}
