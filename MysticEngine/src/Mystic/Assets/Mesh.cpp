#include "mspch.h"

#include <regex>

#include "Mesh.h"

#include "Mystic/Renderer/Buffer.h"
#include "Mystic/Renderer/VertexArray.h"

#include "Mystic/Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Mystic {

	Mesh::Mesh(const std::string& filepath)
	{
        loadMesh(filepath);

        va.reset(Mystic::VertexArray::Create());
        vb.reset(Mystic::VertexBuffer::Create(&vertices[0], vertices.size() * sizeof(float)));

        Mystic::BufferLayout layout = {
            { Mystic::ShaderDataType::Float3, "a_Position"},
            { Mystic::ShaderDataType::Float3, "a_Normal"},
            { Mystic::ShaderDataType::Float2, "a_TexCoord"}
        };
        vb->SetLayout(layout);
        va->AddVertexBuffer(vb);

        ib.reset(Mystic::IndexBuffer::Create(&indices[0], indices.size()));

        va->SetIndexBuffer(ib);
	}

    void Mesh::Draw(Ref<Shader> shader, glm::mat4 modelMatrix)
    {
        Renderer::Submit(shader, va, modelMatrix);
    }

    void Mesh::loadMesh(const std::string& filepath)
    {
        std::string prefix;

        std::ifstream file(filepath);

        int index = 0;
        
        for (std::string line; getline(file, line);)
        {
            std::istringstream iss(line);
            iss >> prefix;
            if (prefix == "o")
            {
                std::string name;
                iss >> name;
                //MS_CORE_INFO(name);
            }
            if (prefix == "v")
            {
                float x, y, z;
                iss >> x;
                iss >> y;
                iss >> z;
                positions.push_back(glm::vec3(x, y, z));
                //MS_CORE_INFO("{0} {1} {2}", x, y, z);
            }
            if (prefix == "vt")
            {
                float x, y;
                iss >> x;
                iss >> y;
                texCoords.push_back(glm::vec2(x, y));
            }
            if (prefix == "vn")
            {
                float x, y, z;
                iss >> x;
                iss >> y;
                iss >> z;
                normals.push_back(glm::vec3(x, y, z));
            }
            if (prefix == "f")
            {
                std::string a, b, c;
                iss >> a;
                iss >> b;
                iss >> c;
                
                int i1, i2, i3;
                int t1, t2, t3;
                int n1, n2, n3;

                if (std::sscanf(a.c_str(), "%d/%d/%d", &i1, &t1, &n1) <= 0)
                    MS_CORE_ASSERT("Failed to load faces: {0} {1} {2}", a, b, c);
                if (std::sscanf(b.c_str(), "%d/%d/%d", &i2, &t2, &n2) <= 0)
                    MS_CORE_ASSERT("Failed to load faces: {0} {1} {2}", a, b, c);
                if (std::sscanf(c.c_str(), "%d/%d/%d", &i3, &t3, &n3) <= 0)
                    MS_CORE_ASSERT("Failed to load faces: {0} {1} {2}", a, b, c);

                push_vertex_data(i1, n1, t1);
                push_vertex_data(i2, n2, t2);
                push_vertex_data(i3, n3, t3);

                indices.push_back(index);
                indices.push_back(index + 1);
                indices.push_back(index + 2);
                index += 3;
                
                //MS_CORE_INFO("{0} {1} {2}", i1, i2, i3);
            }
        }
    }

    void Mesh::push_vertex_data(int i, int n, int t)
    {
        i -= 1;
        n -= 1;
        t -= 1;

        vertices.push_back(positions[i].x);
        vertices.push_back(positions[i].y);
        vertices.push_back(positions[i].z);

        vertices.push_back(normals[n].x);
        vertices.push_back(normals[n].y);
        vertices.push_back(normals[n].z);

        vertices.push_back(texCoords[t].x);
        vertices.push_back(texCoords[t].y);
    }

}