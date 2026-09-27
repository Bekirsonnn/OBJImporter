#pragma once

struct vec3
{
	double x = 0;
	double y = 0;
	double z = 0;
	double padding = 0;
};

struct vec2
{
	double x = 0;
	double y = 0;
};

struct vertex_indices
{
	int v = 0; // Vertex Index
	int vt = 0; // Texture Coordinate
	int vn = 0; // Normal Index
};

struct face
{
	vertex_indices indices[3]; // A face is a triangle which has 3 corners
};

struct OBJ
{
	std::string obj_name;
	std::string grp_name;

	// vertex data
	std::vector<vec3> verts;

	// texture coordinates
	std::vector<vec2> vt;

	// vertex normals
	std::vector<vec3> normals;

	// parameter space vertices
	std::vector<vec3> s_verts;

	// faces
	std::vector<face> faces;

	// lines or edges
	std::vector<int> edges;
};