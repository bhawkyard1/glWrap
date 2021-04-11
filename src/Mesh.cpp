#include <iostream>
#include <sstream>
#include "glm/gtx/string_cast.hpp"
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
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<size_t> indices;

    std::cout << "Parsing data from vector length " << _data.size() << "...\n";
    for(auto &line: _data)
    {
        if(line.substr(0, 2) == "v ")
        {
            std::istringstream p(line.substr(2));
            double x, y, z;
            p >> x; p >> y; p >> z;
            glm::vec3 vert = glm::vec3(x, y, z);
            vertices.push_back(vert);
        }
        else if(line.substr(0, 3) == "vt ")
        {
            std::istringstream p(line.substr(2));
            double u, v;
            p >> u; p >> v;;
            glm::vec2 uv = glm::vec2(u, v);
            uvs.push_back(uv);
        }
        else if(line.substr(0, 3) == "vn ")
        {
            std::istringstream p(line.substr(2));
            double x, y, z;
            p >> x; p >> y; p >> z;
            glm::vec3 norm = glm::vec3(x, y, z);
            normals.push_back(norm);
        }
        else if(line.substr(0, 2) == "f ")
        {
            std::istringstream p(line.substr(2));
            size_t i1, i2, i3;
            p >> i1; p >> i2; p >> i3;
            // obj indexes start from 1
            indices.push_back(i1-1);
            indices.push_back(i2-1);
            indices.push_back(i3-1);
        }
    }
    std::cout << "Found " << vertices.size() << " vertices, " << normals.size() << " normals and " << uvs.size() << " uvs.\n";

    if(!indices.empty())
    {
        std::cout << "Indexing data...\n";
        for(auto &index : indices)
        {
            if(!vertices.empty())
            {
                m_vertices.push_back(vertices.at(index));
            }

            if(!normals.empty())
            {
                m_normals.push_back(normals.at(index));
            }

            if(!uvs.empty())
            {
                m_uvs.push_back(uvs.at(index));
            }
        }
    }
    else
    {
        m_vertices = vertices;
        m_normals = normals;
        m_uvs = uvs;
    }

    // Generate normals
    if(normals.empty())
    {
        std::cout << "Generating normals...\n";
        if(m_vertices.size() % 3 != 0)
        {
            std::cerr << "Error vertices array length not divisible by 3!\n";
            exit(1);
        }

        size_t len = m_vertices.size() / 3;
        for(size_t i = 0; i < len; ++i)
        {
            size_t m = i * 3;
            glm::vec3 a = m_vertices.at(m);
            glm::vec3 b = m_vertices.at(m+1);
            glm::vec3 c = m_vertices.at(m+2);

            glm::vec3 ab = b - a;
            glm::vec3 bc = c - b;
            glm::vec3 n = glm::normalize(glm::cross(ab, bc));
            m_normals.push_back(n);
            m_normals.push_back(n);
            m_normals.push_back(n);
            std::cout << "computed normal vector " << glm::to_string(n) << "\n";
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