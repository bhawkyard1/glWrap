#include <iostream>
#include <sstream>
#include "Mesh.hpp"

void Mesh::bind()
{
    m_vao.bind();
}

void Mesh::generateBuffers()
{
    if(!m_vertices.empty())
    {
        m_vao.bind();
        m_verticesBuffer.bind();
        m_verticesBuffer.bufferData(m_vertices);
        
        m_vao.enableVertexAttribArray(0);
        m_vao.vertexAttribPointer(3, GL_FLOAT);
    }
    else
    {
        std::cerr << "Cannot generate buffers for a mesh with no vertices!" << std::endl;
        exit(1);
    }

    if(!m_normals.empty())
    {
        m_normalsBuffer.bind();
        m_normalsBuffer.bufferData(m_normals);

        m_vao.enableVertexAttribArray(1);
        m_vao.vertexAttribPointer(3, GL_FLOAT);
    }

    if(!m_uvs.empty())
    {
        m_uvsBuffer.bind();
        m_uvsBuffer.bufferData(m_uvs);

        m_vao.enableVertexAttribArray(2);
        m_vao.vertexAttribPointer(2, GL_FLOAT);
    }

    m_vao.unbind();
}

void Mesh::loadObj(const std::vector<std::string>& _data)
{
    for(auto &line: _data)
    {
        if(line.substr(0, 2) == "v ")
        {
            std::istringstream p(line.substr(2));
            double x, y, z;
            p >> x; p >> y; p >> z;
            glm::vec3 vert = glm::vec3(x, y, z);
            m_vertices.push_back(vert);
        }
        else if(line.substr(0, 3) == "vt ")
        {
            std::istringstream p(line.substr(2));
            double u, v;
            p >> u; p >> v;;
            glm::vec2 uv = glm::vec2(u, v);
            m_uvs.push_back(uv);
        }
        else if(line.substr(0, 3) == "vn ")
        {
            std::istringstream p(line.substr(2));
            double x, y, z;
            p >> x; p >> y; p >> z;
            glm::vec3 norm = glm::vec3(x, y, z);
            m_normals.push_back(norm);
        }
    }
}

size_t Mesh::size()
{
    return m_vertices.size();
}

void Mesh::unbind()
{
    m_vao.unbind();
}