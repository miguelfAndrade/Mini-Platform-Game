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
	Point m_pos;
	Point m_normalizedPoint;
	float m_width;
	float m_height;
	unsigned int m_size_count;
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;

	glm::mat4 m_transform;
	glm::vec3 m_rotation;
	float m_angleRotation;

	float m_halfWidth;
	float m_halfHeight;

	Color m_color;
	std::string m_uniform;

	ShapeType m_type;
	VertexArray m_va;
	VertexBufferLayout m_layout;
	IndexBuffer m_ib;
	// Shader m_shader;

	void calculateShapeRender();
	void calculatePositionVerticesSquare(Point& p1, Point& p2, Point& p3, Point& p4);
	void calculatePositionVerticesTriangle(float& vX, float& vY);
public:
	Shape(float width, float height, ShapeType type);
	~Shape();
	void Draw(Renderer& renderer, Shader& shader);
	void Rotate(float angle, glm::vec3 rotation);
	void setColor(Color color, Shader& shader);
	void setPos(float x, float y);
	void setSize(float width, float height);

	Point getPosition() { return m_pos; }
	float getWidth() { return m_width; }
	float getHeight() { return m_height; }

};
