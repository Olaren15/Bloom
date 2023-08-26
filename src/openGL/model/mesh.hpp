#pragma once

#include "../texture.hpp"
#include "vertex.hpp"

#include <glad/glad.h>
#include <vector>

namespace bloom::openGL::model {
    using Index = unsigned int;

    struct Mesh {
        Mesh(std::vector<Vertex>&& vertices, std::vector<Index>&& indices, Texture&& texture);
        Mesh(const Mesh&) = delete;
        Mesh(Mesh&& other) noexcept;
        ~Mesh();

        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&& other) noexcept;

        std::vector<Vertex> vertices;
        std::vector<Index> indices;
        Texture texture;

        GLuint vertexBuffer = 0;
        GLuint indexBuffer = 0;
        GLuint vertexArray = 0;
    };
} // namespace bloom::openGL::model