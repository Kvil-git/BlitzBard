#pragma once
#include <math.h>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <fstream>
class Matrix3x3 {
public:
	float elements[3][3];

	Matrix3x3() {
	}

	Matrix3x3(const float elements[3][3]) {
		for (uint8_t i = 0; i < 3; i++)
			for (uint8_t j = 0; j < 3; j++)
				this->elements[i][j] = elements[i][j];
	}

	~Matrix3x3() {
	}



	bool operator==(const Matrix3x3& other) const {
		bool output = 1;
		for (uint8_t i = 0; i < 3; i++)
			for (uint8_t j = 0; j < 3; j++)
				output = (output && this->elements[i][j] == other.elements[i][j]);
		return output;
	}

	bool operator!=(const Matrix3x3& other) const {
		bool output = 1;
		for (uint8_t i = 0; i < 3; i++)
			for (uint8_t j = 0; j < 3; j++)
				output = (output && this->elements[i][j] != other.elements[i][j]);
		return output;
	}
};





class Matrix4x4 {
public:
	float elements[4][4] = {
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	};

	Matrix4x4() {
	}

	~Matrix4x4() {
	}


	Matrix4x4(const float elements[4][4]) {
		for (uint8_t i = 0; i < 4; i++) {
			for (uint8_t j = 0; j < 4; j++) {
				this->elements[i][j] = elements[i][j];
			}
		}
	}

	void operator=(const Matrix4x4& other) {
		for (uint8_t i = 0; i < 4; i++) {
			for (uint8_t j = 0; j < 4; j++) {
				this->elements[i][j] = other.elements[i][j];
			}
		}
	}

	bool operator==(const Matrix4x4& other) const {
		bool output = 1;
		for (uint8_t i = 0; i < 4; i++) {
			for (uint8_t j = 0; j < 4; j++) {
				output = (output && this->elements[i][j] == other.elements[i][j]);
			}
		} return output;
	}

	bool operator!=(const Matrix4x4& other) const {
		bool output = 1;
		for (uint8_t i = 0; i < 4; i++) {
			for (uint8_t j = 0; j < 4; j++) {
				output = (output && this->elements[i][j] != other.elements[i][j]);
			}
		} return output;
	}

};