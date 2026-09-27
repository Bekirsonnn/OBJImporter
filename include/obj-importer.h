#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "obj-data.h"

//------------------------------------------
//	Purpose: Dividing Raw Input Line by Line
//------------------------------------------
std::vector<std::string> DivideByLine(std::ifstream& file);

//------------------------------------------
//	Purpose: Parsing Vertices
//------------------------------------------
void ParseVerts(OBJ& myOBJ, const std::string& line);

//------------------------------------------
//	Purpose: Parsing Texture Coordinates
//------------------------------------------
void ParseVT(OBJ& myOBJ, const std::string& line);

//------------------------------------------
//	Purpose: Parsing Normals
//------------------------------------------
void ParseNormals(OBJ& myOBJ, const std::string& line);

//------------------------------------------
//	Purpose: Parsing Parameter Space Vertices
//------------------------------------------
void ParseSpaceVerts(OBJ& myOBJ, const std::string& line);

//------------------------------------------
//	Purpose: Parsing Faces
//------------------------------------------
void ParseFaces(OBJ& myOBJ, std::string& line);

//------------------------------------------
//	Purpose: Wrapping Everything Into A Single Function
//------------------------------------------
OBJ LoadOBJ(std::ifstream& file_path);
