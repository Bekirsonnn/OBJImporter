#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "vec3.hpp"
#include "vec2.hpp"
#include "face.hpp"
#include "timer.hpp"

class OBJ
{
private:
    std::ifstream m_filePath;
    std::istringstream m_Stream;

public:
    std::vector<Vec3> verts;

    std::vector<Vec3> normals;

    std::vector<Vec2> texPos;

    std::vector<Face> faces;

    bool ValidateData(int& data, const int& count);

    bool ParseVerts(std::istream &stream);
    bool ParseNormals(std::istream& stream);
    bool ParseTexPos(std::istream &stream);
    bool ParseFaces(std::istringstream &stream);

    bool LoadOBJ();

    OBJ(const std::string &path) : m_filePath(path)
    {
        if (!m_filePath.is_open())
        {
            std::cerr << "Failed To Open OBJ File\n";
            return;
        }
        
        bool loaded = false;
        {
            Timer timer;
            loaded = LoadOBJ();
        }
        if (!loaded)
        {
            std::cerr << "Failed To Load OBJ File\n";
            return;
        }

        std::cout << "OBJ Loaded!\n";

        m_filePath.close();
    }
};