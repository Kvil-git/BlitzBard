#pragma once
#include "Vectors.h"
class Vertex2 {
public:
	Vector2 Position;
	Vector2 Normal;
	Vertex2() {
	}
	Vertex2(float X, float Y) {
		Position.X = X; Position.Y = Y;
	}

};


class Vertex3 {
public:
	Vector3 Position;
	Vector3 Normal;
};


class Triangle2 {
public:
	Vertex2 vertex1, vertex2, vertex3;
	Triangle2() {

	}
	Triangle2(Vertex2 vertex1, Vertex2 vertex2, Vertex2 vertex3) {
		this->vertex1 = vertex1;
		this->vertex2 = vertex2;
		this->vertex3 = vertex3;
	}
};

class Triangle3 {
public:
	Vertex3 vertex1, vertex2, vertex3;
	Vector3 faceNormal;
	Triangle3() {

	}
	Triangle3(const Vertex3& vertex1, const Vertex3& vertex2, const Vertex3& vertex3) {
		this->vertex1 = vertex1;
		this->vertex2 = vertex2;
		this->vertex3 = vertex3;
	}

	Triangle3(const Vector3& position1, const Vector3& position2, const Vector3& position3) {
		this->vertex1.Position = position1;
		this->vertex2.Position = position2;
		this->vertex3.Position = position3;
	}

	Triangle3(const Vertex3& vertex1, const Vertex3& vertex2, const Vertex3& vertex3, const Vector3& faceNormal) {
		this->vertex1 = vertex1;
		this->vertex2 = vertex2;
		this->vertex3 = vertex3;
		this->faceNormal = faceNormal;
	}

	Triangle3(const Vector3& position1, const Vector3& position2, const Vector3& position3, const Vector3& faceNormal) {
		this->vertex1.Position = position1;
		this->vertex2.Position = position2;
		this->vertex3.Position = position3;
		this->faceNormal = faceNormal;
	}
};

Vector3 getTriangleNormal(Vector3 point1, Vector3 point2, Vector3 point3) {
	Vector3 side1 = point2 - point1;
	Vector3 side2 = point3 - point1;
	Vector3 normal = crossProduct(side1, side2);
	return normal;
}

bool isInTriangle(Vector3 point, Vector3 trianglePoint1, Vector3 trianglePoint2, Vector3 trianglePoint3) {
	// Test to see if it is within an infinite prism that the triangle outlines.
	bool within_tri_prism = SameSide(point, trianglePoint1, trianglePoint2, trianglePoint3) && SameSide(point, trianglePoint2, trianglePoint1, trianglePoint3)
		&& SameSide(point, trianglePoint3, trianglePoint1, trianglePoint2);

	// If it isn't it will never be on the triangle
	if (!within_tri_prism) return false;

	// Calulate Triangle's Normal
	Vector3 n = getTriangleNormal(trianglePoint1, trianglePoint2, trianglePoint3);

	// Project the point onto this normal
	Vector3 proj = projectOnVector(point, n);

	// If the distance from the triangle to the point is 0
	//	it lies on the triangle
	if (proj.magnitude() == 0)
		return true;
	else
		return false;
}

void sortTrianglesByZ(std::vector<Triangle3>& polygonsToDraw) {
	std::sort(polygonsToDraw.begin(), polygonsToDraw.end(), [](const Triangle3& tri1, const Triangle3& tri2) {
		float average1 = (tri1.vertex1.Position.Z + tri1.vertex2.Position.Z + tri1.vertex3.Position.Z) / 3;
		float average2 = (tri2.vertex1.Position.Z + tri2.vertex2.Position.Z + tri2.vertex3.Position.Z) / 3;
		return average1 < average2;
	});
}