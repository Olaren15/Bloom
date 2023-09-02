#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-bounds-pointer-arithmetic"
#include "modelImporter.hpp"

#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include <optional>
#include <vector>

namespace bloom::openGL::model {
    static constexpr size_t VerticesPerFace = 3;

#pragma region forward_declarations
    Model generateModel(const aiNode* node, const aiScene* scene, const std::filesystem::path& basePath);
    void accumulateMeshesRecursive(
        const aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, const std::filesystem::path& basePath
    );
    std::optional<Mesh> generateMesh(const aiMesh* mesh, const aiScene* scene, const std::filesystem::path& basePath);
    std::vector<Vertex> extractVertices(const aiMesh* mesh);
    std::vector<Index> extractIndices(const aiMesh* mesh);
    Texture extractTexture(const aiMesh* mesh, const aiScene* scene, const std::filesystem::path& basePath);
#pragma endregion

    Model importModelFromFile(const std::filesystem::path& path) {
        Assimp::Importer importer;

        const aiScene* scene =
            importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_SortByPType);
        if ((scene == nullptr) || ((scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != 0) || (scene->mRootNode == nullptr)) {
            throw std::runtime_error("Failed to load model");
        }

        const std::filesystem::path pathRelativeToModel = path.parent_path();
        return generateModel(scene->mRootNode, scene, pathRelativeToModel);
    }

    Model generateModel(const aiNode* node, const aiScene* scene, const std::filesystem::path& basePath) {
        std::vector<Mesh> meshes;
        accumulateMeshesRecursive(node, scene, meshes, basePath);

        return Model{std::move(meshes)};
    }

    void accumulateMeshesRecursive( // NOLINT(*-no-recursion)
        const aiNode* node,
        const aiScene* scene,
        std::vector<Mesh>& meshes,
        const std::filesystem::path& basePath
    ) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            const unsigned int meshIndex = node->mMeshes[i];
            const aiMesh* mesh = scene->mMeshes[meshIndex];
            std::optional<Mesh> generatedMesh = generateMesh(mesh, scene, basePath);
            if (generatedMesh.has_value()) {
                meshes.push_back(std::move(generatedMesh.value()));
            }
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            accumulateMeshesRecursive(node->mChildren[i], scene, meshes, basePath);
        }
    }

    std::optional<Mesh> generateMesh(const aiMesh* mesh, const aiScene* scene, const std::filesystem::path& basePath) {
        if ((mesh->mPrimitiveTypes & aiPrimitiveType_TRIANGLE) == 0) {
            std::cout << "Skipped mesh because it is not made of triangles\n";
            return std::nullopt;
        }

        return {Mesh{extractVertices(mesh), extractIndices(mesh), extractTexture(mesh, scene, basePath)}};
    }

    std::vector<Vertex> extractVertices(const aiMesh* mesh) {
        std::vector<Vertex> vertices(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            const aiVector3D position = mesh->mVertices[i];
            const aiVector3D normal = mesh->mNormals[i];
            const aiVector3D* uvCoordinates = mesh->mTextureCoords[0];

            const Vertex vertex{
                glm::vec3{position.x, position.y, position.z},
                glm::vec3{normal.x, normal.y, normal.z},
                uvCoordinates == nullptr ? glm::vec2{0.0F, 0.0F} : glm::vec2{uvCoordinates[i].x, uvCoordinates[i].y}};

            vertices.insert(vertices.begin() + i, vertex);
        }

        return vertices;
    }

    std::vector<Index> extractIndices(const aiMesh* mesh) {
        std::vector<Index> indices(VerticesPerFace * mesh->mNumFaces);
        std::for_each(mesh->mFaces, mesh->mFaces + mesh->mNumFaces, [&indices](const aiFace& face) {
            indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
        });

        return indices;
    }

    Texture extractTexture(const aiMesh* mesh, const aiScene* scene, const std::filesystem::path& basePath) {
        const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // TODO: handle more than one texture
        aiString texturePath;

        material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);

        const std::filesystem::path fullPath{basePath.string() + "/" + texturePath.C_Str()};
        return Texture{fullPath};
    }
} // namespace bloom::openGL::model

#pragma clang diagnostic pop