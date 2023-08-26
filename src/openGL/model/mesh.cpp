#include "mesh.hpp"

#include <utility>

namespace bloom::openGL::model {
    Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<Index>&& indices, Texture&& texture) :
      vertices(std::move(vertices)), indices(std::move(indices)), texture(std::move(texture)) {
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(this->vertices.size() * sizeof(Vertex)),
            this->vertices.data(),
            GL_STATIC_DRAW
        );

        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(this->indices.size() * sizeof(Index)),
            this->indices.data(),
            GL_STATIC_DRAW
        );

        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, position)) // NOLINT(performance-no-int-to-ptr)
        );
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, normal)) // NOLINT(performance-no-int-to-ptr)
        );
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, uv)) // NOLINT(performance-no-int-to-ptr)
        );
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    Mesh::Mesh(Mesh&& other) noexcept :
      vertices(std::move(other.vertices)), indices(std::move(other.indices)), texture(std::move(other.texture)) {
        vertexBuffer = other.vertexBuffer;
        indexBuffer = other.indexBuffer;
        vertexArray = other.vertexArray;

        other.vertexBuffer = 0;
        other.indexBuffer = 0;
        other.vertexArray = 0;
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept {
        glDeleteBuffers(1, &indexBuffer);
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteVertexArrays(1, &vertexArray);

        vertices = std::move(other.vertices);
        indices = std::move(other.indices);
        texture = std::move(other.texture);

        vertexBuffer = other.vertexBuffer;
        indexBuffer = other.indexBuffer;
        vertexArray = other.vertexArray;

        other.vertexBuffer = 0;
        other.indexBuffer = 0;
        other.vertexArray = 0;

        return *this;
    }

    Mesh::~Mesh() {
        glDeleteBuffers(1, &indexBuffer);
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteVertexArrays(1, &vertexArray);
    }
} // namespace bloom::openGL::model