#include <charconv>
#include <iostream>

#include "obj.hpp"
#include "vec3.hpp"


bool OBJ::ValidateData(int& data, const int& count)
{
    if (data == 0)
    {
        return false;
    }

    if (data < 0)
    {
        data = count + data;
    }
    else
    {
        data -= 1;
    }

    if (data < 0 || data >= count)
    {
        return false;
    }

    return true;
}

bool OBJ::ParseVerts(std::istream &stream)
{
    Vec3 vec;

    // if extraction is successful
    if (stream >> vec.x >> vec.y >> vec.z)
    {
        verts.push_back(vec);
        return true;
    }

    return false;
}

bool OBJ::ParseNormals(std::istream &stream)
{
    Vec3 vec;

    if (stream >> vec.x >> vec.y >> vec.z)
    {
        normals.push_back(vec);
        return true;
    }

    return false;
}

bool OBJ::ParseTexPos(std::istream &stream)
{
    Vec2 vec;

    if (stream >> vec.x >> vec.y)
    {
        texPos.push_back(vec);
        return true;
    }

    return false;
}

bool OBJ::ParseFaces(std::istringstream &stream)
{
    int vertexCount = static_cast<int>(verts.size());
    int normalCount = static_cast<int>(normals.size());
    int textureCount = static_cast<int>(texPos.size());

    Face face;

    std::string corner;

    std::size_t frstSlash;
    std::size_t scndSlash;

    std::from_chars_result result;

    while (stream >> corner)
    {
        FaceVertex fv{};
        frstSlash = corner.find('/');

        // If there are no slashes, it means it's only vertex data ("f 1 2 3")
        if (frstSlash == std::string::npos)
        {
            result = std::from_chars(corner.data(), corner.data() + corner.size(), fv.posIdx);
            if (result.ec != std::errc{} || result.ptr != corner.data() + corner.size())
            {
                std::cerr << "Invaild Position Index\n";
                return false;
            }

            if (!ValidateData(fv.posIdx, vertexCount))
            {
                return false;
            }
        }
        else
        {
            result = std::from_chars(corner.data(), corner.data() + frstSlash, fv.posIdx);
            if (result.ec != std::errc{} || result.ptr != corner.data() + frstSlash)
            {
                std::cerr << "Invaild Position Index\n";
                return false;
            }

            if (!ValidateData(fv.posIdx, vertexCount))
            {
                return false;
            }

            scndSlash = corner.find('/', frstSlash + 1);

            // If second slash doesn't exist (Format: Pos/Tex)
            if (scndSlash == std::string::npos)
            {
                result = std::from_chars(corner.data() + frstSlash + 1, corner.data() + corner.size(), fv.texCoordIdx);
                if (result.ec != std::errc{} || result.ptr != corner.data() + corner.size())
                {
                    std::cerr << "Invaild Texture Coordinate\n";
                    return false;
                }

                if (!ValidateData(fv.texCoordIdx, textureCount))
                {
                    return false;
                }
            }
            else
            {
                // Format: Pos/Tex/Normal or Pos//Normal

                if (scndSlash > frstSlash + 1)
                {
                    result = std::from_chars(corner.data() + frstSlash + 1, corner.data() + scndSlash, fv.texCoordIdx);
                    if (result.ec != std::errc{} || result.ptr != corner.data() + scndSlash)
                    {
                        std::cerr << "Invaild Texture Coordinate\n";
                        return false;
                    }

                    if (!ValidateData(fv.texCoordIdx, textureCount))
                    {
                        return false;
                    }
                }

                result = std::from_chars(corner.data() + scndSlash + 1, corner.data() + corner.size(), fv.normalIdx);
                if (result.ec != std::errc{} || result.ptr != corner.data() + corner.size())
                {
                    std::cerr << "Invaild Normal Coordinate\n";
                    return false;
                }

                if (!ValidateData(fv.normalIdx, normalCount))
                {
                    return false;
                }
            }
        }

        face.indices.push_back(fv);
    }

    if (face.indices.size() >= 3)
    {
        faces.push_back(face);
        return true;
    }

    return false;
}

bool OBJ::LoadOBJ()
{
    std::string line;
    std::string type;

    while (std::getline(m_filePath, line))
    {
        m_Stream.clear();
        m_Stream.str(line);

        type.clear();
        m_Stream >> type;

        if (type == "v")
        {
            if (!ParseVerts(m_Stream))
            {
                std::cerr << "Failed to Parse Vertices\n";
                return false;
            }
        }
        else if (type == "vt")
        {
            if (!ParseTexPos(m_Stream))
            {
                std::cerr << "Failed to Parse Texture Coordinates\n";
                return false;
            }
        }
        else if (type == "vn")
        {
            if (!ParseNormals(m_Stream))
            {
                std::cerr << "Failed to Parse Normals\n";
                return false;
            }
        }
        else if (type == "f")
        {
            if (!ParseFaces(m_Stream))
            {
                std::cerr << "Failed to Parse Faces\n";
                return false;
            }
        }
        else if (type == "#")
        {
            continue;
        }
    }

    return true;
}
