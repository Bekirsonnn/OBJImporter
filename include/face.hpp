#pragma once

#include <vector>

struct FaceVertex
{
	int posIdx{ -1 };
	int texCoordIdx{ -1 };
	int normalIdx{ -1 };
};

struct Face
{
	std::vector<FaceVertex> indices;
};