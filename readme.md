# Simple OBJ Importer

A lightweight Wavefront OBJ importer written in C++ for loading 3D models into your projects.

## Features

- Loads vertex positions (`v`).
- Loads texture coordinates (`vt`).
- Loads vertex normals (`vn`).
- Loads faces (`f`), including faces with separate position, texture coordinate, and normal indices.
- Converts OBJ's 1-based indices to C++-friendly 0-based indices.
- Supports negative OBJ indices, which reference elements relative to the end of their respective lists.
- Provides direct access to the loaded vertices, normals, texture coordinates, and faces.

## Getting Started

### Requirements

- A C++ compiler with C++17 support.
- The importer source files and required header files.

### Installation

Add the importer files to your C++ project:

- `obj.hpp`
- `obj.cpp`
- `face.hpp`
- `vec2.hpp`
- `vec3.hpp`
- `timer.hpp` (if required by your current implementation)

Make sure the files are included in your project's build and that the header files are accessible to the compiler.

### Usage

Include the importer header:

```cpp
#include "obj.hpp"
```

Create an importer object by providing the path to your OBJ file:

```cpp
OBJ model("model.obj");
```

After loading, you can access the model's data through its public members:

```cpp
// Number of loaded vertices
std::cout << model.verts.size() << '\n';

// Number of loaded normals
std::cout << model.normals.size() << '\n';

// Number of loaded texture coordinates
std::cout << model.texPos.size() << '\n';

// Number of loaded faces
std::cout << model.faces.size() << '\n';
```

The importer stores vertex positions, normals, texture coordinates, and face data in vectors, making the data available for further processing by your application or renderer.

## Index Handling

OBJ files use 1-based indices, while C++ vectors use 0-based indices. This importer converts valid OBJ indices to 0-based indices for convenient access.

For example, an OBJ face referencing vertex `1` will use index `0` in the importer.

Negative OBJ indices are also converted relative to the number of corresponding elements defined so far.

## Current Limitations

- Material libraries (`.mtl`) and material assignments are not implemented yet.
- The importer currently focuses on geometry data and does not provide a complete implementation of every Wavefront OBJ feature.
- Make sure your OBJ files use supported vertex, texture coordinate, normal, and face formats.

## Contributions

Suggestions, bug reports, and contributions are welcome!
