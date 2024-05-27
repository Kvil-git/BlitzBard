#pragma once
#include "Polygons.h"
class Model {
public:
	std::vector<Triangle3> LoadedPolygons;
	std::vector<Vertex3> LoadedVertices;
	std::vector<Vector3> LoadedNormals;



	Triangle3 getPolygonFromObjLine(const std::string& line) {
		unsigned int vertexIndices[3];
		if (line.find('/') < line.length()) {
			unsigned int normalIndices[3];
			std::string newline = line.substr(2, line.length());
			newline = std::regex_replace(newline, std::regex("//"), " ");
			newline = std::regex_replace(newline, std::regex("/"), " ");
			std::istringstream iss(newline);
			unsigned int junk[3];
			if (line.find("//") < line.length())
				iss >> vertexIndices[0] >> normalIndices[0]
				>> vertexIndices[1] >> normalIndices[1]
				>> vertexIndices[2] >> normalIndices[2];
			else
				iss >> vertexIndices[0] >> junk[0] >> normalIndices[0]
				>> vertexIndices[1] >> junk[1] >> normalIndices[1]
				>> vertexIndices[2] >> junk[2] >> normalIndices[2];

			LoadedVertices[vertexIndices[0] - 1].Normal = LoadedNormals[normalIndices[0] - 1];
			LoadedVertices[vertexIndices[1] - 1].Normal = LoadedNormals[normalIndices[1] - 1];
			LoadedVertices[vertexIndices[2] - 1].Normal = LoadedNormals[normalIndices[2] - 1];

			return(Triangle3(LoadedVertices[vertexIndices[0] - 1], LoadedVertices[vertexIndices[1] - 1], LoadedVertices[vertexIndices[2] - 1]));
		}
		else {
			std::istringstream iss(line.substr(2, line.length()));
			iss >> vertexIndices[0] >> vertexIndices[1] >> vertexIndices[2];

			Vector3 A = LoadedVertices[vertexIndices[0] - 1].Position - LoadedVertices[vertexIndices[1] - 1].Position;
			Vector3 B = LoadedVertices[vertexIndices[2] - 1].Position - LoadedVertices[vertexIndices[1] - 1].Position;
			Vector3 normal = crossProduct(A, B);
			for (uint8_t i = 0; i < 3; i++) LoadedVertices[vertexIndices[i] - 1].Normal = normal;

			return(Triangle3(LoadedVertices[vertexIndices[0] - 1], LoadedVertices[vertexIndices[1] - 1], LoadedVertices[vertexIndices[2] - 1]));
		}
	}




	bool loadFromFile(const std::string &path) {
		// If the file is not an .obj file return false
		if (path.substr(path.size() - 4, 4) != ".obj")
			return false;

		std::ifstream file(path);
		if (!file.is_open())
			return false;

		LoadedPolygons.clear();
		LoadedNormals.clear();
		LoadedVertices.clear();

		std::string line;

		while (std::getline(file, line)) {
			std::string type = line.substr(0, 2);
			if (type == "v ") {
				Vertex3 vertex;
				std::istringstream iss(line.substr(2, line.length()));
				if (!(iss >> vertex.Position.X >> vertex.Position.Y >> vertex.Position.Z)) return false; // Parsing error
				LoadedVertices.push_back(vertex);
			}
			if (type == "vn") {
				Vector3 normal;
				std::istringstream iss(line.substr(3, line.length()));
				if (!(iss >> normal.X >> normal.Y >> normal.Z)) return false; // Parsing error
				LoadedNormals.push_back(normal);

			}
			if (type == "f ") LoadedPolygons.push_back(getPolygonFromObjLine(line));
		} file.close();

		LoadedVertices.clear();

		if (LoadedPolygons.empty()) return false;
		return true;
	}
};


class World {
public:
	float xRotAngle = 0.0f;
	float yRotAngle = 0.0f;
	float zRotAngle = 35.0f;
};


class Camera {
public:
	Vector3 position;

	float aspectRatio = 0.66f;
	float Near = 0.1f;
	float Far = 1000.0f;

	float fov = 90.0f;

	bool xRotation = 0;
	bool yRotation = 0;
	bool zRotation = 0;
	bool increment = 0;

	Camera() {
		position.X = 0.0f;
		position.Y = 0.0f;
		position.Z = 0.0f;
	}

};