#pragma once
#include "Matrices.h"
class Vector2 {
public:
	float X;
	float Y;
	Vector2() {
		X = 0.0f;
		Y = 0.0f;
	}
	// Variable Set Constructor
	Vector2(float X_, float Y_) {
		X = X_;
		Y = Y_;
	}
	// Bool Equals Operator Overload
	bool operator==(const Vector2& other) const
	{
		return (this->X == other.X && this->Y == other.Y);
	}
	// Bool Not Equals Operator Overload
	bool operator!=(const Vector2& other) const
	{
		return !(this->X == other.X && this->Y == other.Y);
	}
	// Addition Operator Overload
	Vector2 operator+(const Vector2& right) const
	{
		return Vector2(this->X + right.X, this->Y + right.Y);
	}
	// Subtraction Operator Overload
	Vector2 operator-(const Vector2& right) const
	{
		return Vector2(this->X - right.X, this->Y - right.Y);
	}
	// Float Multiplication Operator Overload
	Vector2 operator*(const float& other) const
	{
		return Vector2(this->X * other, this->Y * other);
	}
};

class Vector3 {
public:
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;



	Vector3() {
	}

	Vector3(float X_, float Y_, float Z_) {
		X = X_;
		Y = Y_;
		Z = Z_;
	}

	float magnitude() {
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	void normalize() {
		float l = this->magnitude();
		this->X /= l;
		this->Y /= l;
		this->Z /= l;
	}



	// Bool Equals Operator Overload
	bool operator==(const Vector3& other) const
	{
		return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
	}
	// Bool Not Equals Operator Overload
	bool operator!=(const Vector3& other) const
	{
		return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
	}
	// Addition Operator Overload
	Vector3 operator+(const Vector3& right) const
	{
		return Vector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
	}
	// Subtraction Operator Overload
	Vector3 operator-(const Vector3& right) const
	{
		return Vector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
	}
	// Float Multiplication Operator Overload
	Vector3 operator*(const float& other) const
	{
		return Vector3(this->X * other, this->Y * other, this->Z * other);
	}
	Vector3 operator*(const Matrix3x3& matrix) const {
		Vector3 output;
		output.X = (matrix.elements[0][0] * this->X + matrix.elements[0][1] * this->Y + matrix.elements[0][2] * this->Z);
		output.Y = (matrix.elements[1][0] * this->X + matrix.elements[1][1] * this->Y + matrix.elements[1][2] * this->Z);
		output.Z = (matrix.elements[2][0] * this->X + matrix.elements[2][1] * this->Y + matrix.elements[2][2] * this->Z);
		return output;
	}

	void operator*=(const Matrix3x3& matrix) {
		this->X = (matrix.elements[0][0] * this->X + matrix.elements[0][1] * this->Y + matrix.elements[0][2] * this->Z);
		this->Y = (matrix.elements[1][0] * this->X + matrix.elements[1][1] * this->Y + matrix.elements[1][2] * this->Z);
		this->Z = (matrix.elements[2][0] * this->X + matrix.elements[2][1] * this->Y + matrix.elements[2][2] * this->Z);
	}


	// Float Division Operator Overload
	Vector3 operator/(const float& other) const
	{
		return Vector3(this->X / other, this->Y / other, this->Z / other);
	}

	void operator/=(const float& other)
	{
		this->X /= other; this->Y /= other; this->Z /= other;
	}

};


class Vector4 {
public:
	float elements[4];
	Vector4() {
	}

	Vector4(float x, float y, float z, float w) {
		elements[0] = x;
		elements[1] = y;
		elements[2] = z;
		elements[3] = w;
	}

	~Vector4() {

	}

	void operator*=(const Matrix4x4& matrix) {
		Vector4 result;
		for (uint8_t i = 0; i < 4; i++) {
			for (uint8_t j = 0; j < 4; j++) {
				result.elements[i] += this->elements[j] * matrix.elements[i][j];
			}
		}
		for (uint8_t i = 0; i < 4; i++) this->elements[i] = result.elements[i];
	}

	Vector4 operator*(const Matrix4x4& matrix) const {
		Vector4 result;
		for (uint8_t i = 0; i < 4; i++) {
			for (uint8_t j = 0; j < 4; j++) {
				result.elements[i] += this->elements[i] * matrix.elements[i][j];
			}
		} return result;
	}

};


Vector3 crossProduct(const Vector3& a, const Vector3& b) {
	return Vector3(a.Y * b.Z - a.Z * b.Y,
		a.Z * b.X - a.X * b.Z,
		a.X * b.Y - a.Y * b.X);
}

// Vector3 DotProduct
float dotProduct(const Vector3& a, const Vector3& b) {
	return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
}

// Angle between 2 Vector3 Objects
float angleBetweenVectors(Vector3& a, Vector3& b) {
	float angle = dotProduct(a, b);
	angle /= a.magnitude() * b.magnitude();
	return angle = acosf(angle);
}

// Projection Calculation of a onto b
Vector3 projectOnVector(Vector3 a, Vector3 b) {
	;
	b.normalize();
	return b * dotProduct(a, b);
}

bool SameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b) {
	Vector3 cp1 = crossProduct(b - a, p1 - a);
	Vector3 cp2 = crossProduct(b - a, p2 - a);
	if (dotProduct(cp1, cp2) >= 0) return true;
	else return false;
}