#ifndef MESH
#define MESH

#include <string>
#include <vector>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"

class Mesh
{
    public:
    	void bind();
    	void generateBuffers();
        void loadObj(const std::vector<std::string>& _data);
        size_t size();
        void unbind();

    private:
        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec2> m_uvs;
        
        VertexArrayObject m_vao;
        VertexBufferObject m_verticesBuffer;
        VertexBufferObject m_normalsBuffer;
        VertexBufferObject m_uvsBuffer;
};

#endif