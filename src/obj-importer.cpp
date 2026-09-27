#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "obj-data.h"

#pragma region DivideByLine
//------------------------------------------
//	Purpose: Dividing Raw Input Line by Line
//------------------------------------------
std::vector<std::string> DivideByLine(std::ifstream& file)
{
	std::vector<std::string> lines;
	for (std::string line; std::getline(file, line);)
	{
		lines.push_back(line);
	}

	return lines;
}
#pragma endregion

#pragma region ParseVerts
//------------------------------------------
//	Purpose: Parsing Vertices
//------------------------------------------
void ParseVerts(OBJ& myOBJ, const std::string& line)
{
	vec3 vector;

	// string stream automatically divides the data at a whitespace
	// and also it extracts sequentially
	// so we can do the thing below
	std::istringstream stream(line);
	stream >> vector.x >> vector.y >> vector.z;

	myOBJ.verts.push_back(vector);
}
#pragma endregion

#pragma region ParseVT
//------------------------------------------
//	Purpose: Parsing Texture Coordinates
//------------------------------------------
void ParseVT(OBJ& myOBJ, const std::string& line)
{
	vec2 vector;

	std::istringstream stream(line);
	stream >> vector.x >> vector.y;

	myOBJ.vt.push_back(vector);
}
#pragma endregion

#pragma region ParseNormals
//------------------------------------------
//	Purpose: Parsing Normals
//------------------------------------------
void ParseNormals(OBJ& myOBJ, const std::string& line)
{
	vec3 vector;

	std::istringstream stream(line);
	stream >> vector.x >> vector.y >> vector.z;

	myOBJ.normals.push_back(vector);
}
#pragma endregion

#pragma region ParseSpaceVerts
//------------------------------------------
//	Purpose: Parsing Parameter Space Vertices
//------------------------------------------
void ParseSpaceVerts(OBJ& myOBJ, const std::string& line)
{
	vec3 vector;

	std::istringstream stream(line);
	stream >> vector.x >> vector.y >> vector.z;

	myOBJ.s_verts.push_back(vector);
}
#pragma endregion

#pragma region ParseFaces
//------------------------------------------
//	Purpose: Parsing Faces
//------------------------------------------
void ParseFaces(OBJ& myOBJ, std::string& line)
{
	face face;

	// double slashes means texture coordinates are missing
	// if there is two seperate slashes it means face data contains all three data
	// if there is a single slash it means vertex normal data is missing
	// if there is no slashes it means face data only has vertices

	// if data doesnt contain any slashes
	// so it only has vertices

	// if there is slashes next to each other
	if (line.find("//") != std::string::npos)
	{
		std::replace(line.begin(), line.end(), '/', ' ');

		std::istringstream stream(line);
		stream >> face.indices[0].v >> face.indices[0].vn >>
				  face.indices[1].v >> face.indices[1].vn >>
				  face.indices[2].v >> face.indices[2].vn;

		myOBJ.faces.push_back(face);
	}
	else if (line.find("/") != std::string::npos)
	{
		std::replace(line.begin(), line.end(), '/', ' ');

		std::istringstream stream(line);
		stream >> face.indices[0].v >> face.indices[0].vt >> face.indices[0].vn >>
				  face.indices[1].v >> face.indices[1].vt >> face.indices[1].vn >>
				  face.indices[2].v >> face.indices[2].vt >> face.indices[2].vn;

		myOBJ.faces.push_back(face);
	}
	else
	{
		std::istringstream stream(line);
		stream >> face.indices[0].v >> face.indices[1].v >> face.indices[2].v;

		myOBJ.faces.push_back(face);
	}
}
#pragma endregion

#pragma region LoadOBJ
//------------------------------------------
//	Purpose: Wrapping Everything Into A Single Function
//------------------------------------------
OBJ LoadOBJ(std::ifstream& file_path)
{
	OBJ myOBJ;
	std::string line;
	while (std::getline(file_path, line))
	{
		std::istringstream stream(line);
		std::string token;
		stream >> token;

		if (token.empty() || token[0] == '#') continue;

		std::string current_data = line.substr(token.length());

		if (token == "v") ParseVerts(myOBJ, current_data);
		if (token == "vt") ParseVT(myOBJ, current_data);
		if (token == "vn") ParseNormals(myOBJ, current_data);
		if (token == "vp") ParseSpaceVerts(myOBJ, current_data);
		if (token == "f") ParseFaces(myOBJ, current_data);
	}

	return myOBJ;
}
#pragma endregion