#include "Shape.h"

// Public
Shape::Shape(float width, float height, ShapeType type) : m_type(type) {

	m_size_count = (unsigned int) type;
	m_uniform = "u_Color";
	m_transform = glm::mat4(1.0f);
	m_rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	m_angleRotation = 0.0f;

	setSize(width, height);
	setPos(0.0f, 0.0f); 
	m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	calculateShapeRender();

	VertexBuffer vb(&m_vertices[0], sizeof(float) * m_vertices.size() * 2); // Needs to be the size in bytes, so type size times the number of elements of the array
	m_layout.Push(GL_FLOAT, 2);
	m_va.AddBuffer(vb, m_layout);
	m_ib.setNewIndexBuffer(&m_indices[0], m_indices.size()); // (indices.size() * sizeof(unsigned int)) / sizeof(unsigned int)

	m_va.Unbind();
	// m_shader.Unbind();
	vb.Unbind();
	m_ib.Unbind();
	vb.~VertexBuffer();

}

Shape::~Shape() {
	m_va.~VertexArray();
	m_ib.~IndexBuffer();
}

void Shape::Draw(Renderer& renderer, Shader& shader) {
	
	shader.SetUniform4f("u_Color", m_color.red, m_color.blue, m_color.green, m_color.alpha);
	m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, glm::vec3(m_normalizedPoint.x, m_normalizedPoint.y, m_normalizedPoint.z));
	m_transform = glm::rotate(m_transform, m_angleRotation, m_rotation);
	shader.SetTransformMatrix("u_Pos", m_transform);
	renderer.Draw(m_va, m_ib, shader);
}

void Shape::Rotate(float angle, glm::vec3 rotation) {
	m_angleRotation = angle;
	m_rotation = rotation;
}

void Shape::setColor(Color color, Shader& shader) {
	m_color = color;
}

void Shape::setPos(float x, float y) {
	m_pos = {x, y, 0.0f};
	m_normalizedPoint = { m_pos.x / WINDOW_SIZE_QUADRANT_X, m_pos.y / WINDOW_SIZE_QUADRANT_Y, 0.0f};
}

void Shape::setSize(float width, float height) {
	m_width = width;
	m_height = height;
	m_halfWidth = m_width / 2;
	m_halfHeight = m_height / 2;
}


// Private
void Shape::calculateShapeRender() {
	
	switch (m_type)
	{
		case SQUARE: // Array for the squares vertices
			Point pointSquare1, pointSquare2, pointSquare3, pointSquare4;
			calculatePositionVerticesSquare(pointSquare1, pointSquare2, pointSquare3, pointSquare4);
			m_vertices.insert(m_vertices.begin(), {
					pointSquare1.x, pointSquare1.y,
					pointSquare2.x, pointSquare2.y,
					pointSquare3.x, pointSquare3.y,
					pointSquare4.x, pointSquare4.y
				});

			// Draw order for the vertices of the square
			m_indices.insert(m_indices.cend(), {
					0, 1, 2,
					2, 3, 0
				});
			break;

		case TRIANGLE:
			Point pointTriangle1, pointTriangle2, pointTriangle3;
			calculatePositionVerticesTriangle(pointTriangle1, pointTriangle2, pointTriangle3);
			m_vertices.insert(m_vertices.begin(), {
					pointTriangle1.x, pointTriangle1.y,
					pointTriangle2.x, pointTriangle2.y,
					pointTriangle3.x, pointTriangle3.y
				});

			m_indices.insert(m_indices.cend(), {
					0, 1, 2
				});
			break;
		default:
			break;
	}
}

void Shape::calculatePositionVerticesSquare(Point& p1, Point& p2, Point& p3, Point& p4) {
	// 1st quadrant
	p1.x = (m_pos.x + m_halfWidth) / WINDOW_SIZE_QUADRANT_X;
	p1.y = (m_pos.y + m_halfHeight) / WINDOW_SIZE_QUADRANT_Y;
	// 2nd quadrant
	p2.x = (m_pos.x + m_halfWidth) / WINDOW_SIZE_QUADRANT_X;
	p2.y = (m_pos.y - m_halfHeight) / WINDOW_SIZE_QUADRANT_Y;
	// 3th quadrant
	p3.x = (m_pos.x - m_halfWidth) / WINDOW_SIZE_QUADRANT_X;
	p3.y = (m_pos.y - m_halfHeight) / WINDOW_SIZE_QUADRANT_Y;
	// 4th quadrant
	p4.x = (m_pos.x - m_halfWidth) / WINDOW_SIZE_QUADRANT_X;
	p4.y = (m_pos.y + m_halfHeight) / WINDOW_SIZE_QUADRANT_Y;

}

void Shape::calculatePositionVerticesTriangle(Point& p1, Point& p2, Point& p3) {
	// Point in the Y axis
	p1.x = m_pos.x / WINDOW_SIZE_QUADRANT_X;
	p1.y = (m_pos.y + m_halfHeight) / WINDOW_SIZE_QUADRANT_Y;
	// 2nd quadrant
	p2.x = (m_pos.x + m_halfWidth) / WINDOW_SIZE_QUADRANT_X;
	p2.y = (m_pos.y - m_halfHeight) / WINDOW_SIZE_QUADRANT_Y;
	// 3th quadrant
	p3.x = (m_pos.x - m_halfWidth) / WINDOW_SIZE_QUADRANT_X;
	p3.y = (m_pos.y - m_halfHeight) / WINDOW_SIZE_QUADRANT_Y;
}

