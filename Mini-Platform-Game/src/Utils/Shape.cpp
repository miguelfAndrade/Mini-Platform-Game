#include "Shape.h"


Shape::Shape(float width, float height, ShapeType type) : m_width(width), m_height(height), m_type(type) {

	m_size_count = (unsigned int) type;

	for (int i = 0; i < (sizeof(m_color)/sizeof(float)); i++)
		m_color[i] = 1.0f;

	m_uniform = "u_Color";


	calculateShapeRender();

	VertexBuffer vb(&m_vertices[0], sizeof(float) * m_vertices.size() * 2); // Needs to be the size in bytes, so type size times the number of elements of the array
	m_layout.Push(GL_FLOAT, 2);
	m_va.AddBuffer(vb, m_layout);
	m_ib.setNewIndexBuffer(&m_indices[0], m_indices.size()); // (indices.size() * sizeof(unsigned int)) / sizeof(unsigned int)

	m_va.Unbind();
	m_shader.Unbind();
	vb.Unbind();
	m_ib.Unbind();

}

Shape::~Shape() {
	m_va.~VertexArray();
	m_ib.~IndexBuffer();
}

void Shape::Draw(Renderer& renderer, Shader& shader) {
	shader.SetUniform4f(m_uniform, m_color[0], m_color[1], m_color[2], m_color[3]);
	renderer.Draw(m_va, m_ib, shader);
}

void Shape::calculateShapeRender() {

	m_vertices.clear();
	m_indices.clear();
	
	switch (m_type)
	{
		case SQUARE: // Array for the squares vertices
			m_vertices.insert(m_vertices.begin(), {
					-0.2f, -0.2f,
					 0.2f, -0.2f,
					 0.2f, 0.2f,
					-0.2f, 0.2f
				});

			// Draw order for the vertices of the square
			m_indices.insert(m_indices.cend(), {
					0, 1, 2,
					2, 3, 0
				});
			break;

		case TRIANGLE:
			m_vertices.insert(m_vertices.begin(), {
					-0.95f, 0.0f, // 0
					-0.55f, 0.75f, // 1
					-0.55f, 0.0f, // 2
				});

			m_indices.insert(m_indices.cend(), {
					0, 1, 2
				});
			break;
		default:
			break;
	}
}

void Shape::setColor(float red, float green, float blue, float alpha) {
	m_color[0] = red;
	m_color[1] = blue;
	m_color[2] = green;
	m_color[3] = alpha;
}

void Shape::setPos(float x, float y) {
	posX = x;
	posY = y;
	calculateShapeRender();
}

void Shape::setSize(float width, float height) {
	m_width = width;
	m_height = height;
	calculateShapeRender();
}
