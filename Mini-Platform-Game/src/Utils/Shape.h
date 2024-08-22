#pragma once

#include <memory>
#include <vector>

#include "Utilities.h"

#include "../Rendering/Renderer.h"
#include "../Rendering/VertexBuffer.h"
#include "../Rendering/VertexBufferLayout.h"
#include "../Rendering/IndexBuffer.h"
#include "../Rendering/VertexArray.h"
#include "../Rendering/Shader.h"


class Shape
{

private:
	float posX;
	float posY;
	float m_width;
	float m_height;
	unsigned int m_size_count;
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;

	float m_color[4];
	std::string m_uniform;

	ShapeType m_type;
	VertexArray m_va;
	VertexBufferLayout m_layout;
	IndexBuffer m_ib;
	Shader m_shader;

public:
	Shape(float width, float height, ShapeType type);
	~Shape();
	void Draw(Renderer& renderer, Shader& shader);
	void calculateShapeRender();
	void setColor(float red, float green, float blue, float alpha);
	void setPos(float x, float y);
	void setSize(float width, float height);

	float getX() { return posX; }
	float getY() { return posY; }
	float getWidth() { return m_width; }
	float getHeight() { return m_height; }

};
