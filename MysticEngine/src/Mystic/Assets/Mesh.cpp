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
            { Mystic::ShaderDataType::Float3, "a_Position"}
        };
        vb->SetLayout(layout);
        va->AddVertexBuffer(vb);

        ib.reset(Mystic::IndexBuffer::Create(&indices[0], indices.size()));

        va->SetIndexBuffer(ib);
	}

    void Mesh::Draw(Ref<Shader> shader)
    {
        Renderer::Submit(shader, va, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    }

    void Mesh::loadMesh(const std::string& filepath)
    {
        std::string prefix;

        std::ifstream file(filepath);
        
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
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                //MS_CORE_INFO("{0} {1} {2}", x, y, z);
            }
            if (prefix == "f")
            {
                std::string a, b, c;
                iss >> a;
                iss >> b;
                iss >> c;
                
                int x, y, z;
                int placeholder;
                if (std::sscanf(a.c_str(), "%d/%d/%d", &x, &placeholder, &placeholder) > 0)
                   indices.push_back(x - 1);
                if (std::sscanf(b.c_str(), "%d/%d/%d", &y, &placeholder, &placeholder) > 0)
                    indices.push_back(y - 1);
                if (std::sscanf(c.c_str(), "%d/%d/%d", &z, &placeholder, &placeholder) > 0)
                    indices.push_back(z - 1);
                //MS_CORE_INFO("{0} {1} {2}", x, y, z);
            }
        }
    }

}