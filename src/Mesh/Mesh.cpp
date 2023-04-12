#include "Mesh.h"

////////////////////////////////////////////////////////////
Mesh::Mesh(sf::Vector2f position, sf::Vector2i meshSize, unsigned cellSize)
	: m_positions{ position }, m_size{ meshSize }, m_cellSize{ cellSize }, m_quads{ sf::Quads }, m_lines{ sf::Lines }
{
	// Reserve memory for all elements
	m_squareVec.resize(meshSize.x * meshSize.y);
	m_quads.resize(meshSize.x * meshSize.y * 4);
	m_lines.resize((meshSize.x + 1) * (meshSize.y + 1) * 2);

	// Set up quads
	for (int i = 0; i < meshSize.y; ++i) 
	{
		for (int j = 0; j < meshSize.x; ++j) 
		{
			int index = i * meshSize.x + j;
			float x = position.x + j * m_cellSize;
			float y = position.y + i * m_cellSize;
			sf::Vector2f cellPosition(x, y);
			m_quads[index * 4].position = cellPosition;
			m_quads[index * 4 + 1].position = sf::Vector2f(x + m_cellSize, y);
			m_quads[index * 4 + 2].position = sf::Vector2f(x + m_cellSize, y + m_cellSize);
			m_quads[index * 4 + 3].position = sf::Vector2f(x, y + m_cellSize);

			// Set quad colors
			for (int k = 0; k < 4; ++k) {
				m_quads[index * 4 + k].color = sf::Color::White;
			}
		}
	}

	// Vertical lines
	for (int i = 0; i < meshSize.x + 1; ++i)
	{
		m_lines[i * 2].position = sf::Vector2f(position.x + i * m_cellSize, position.y);
		m_lines[i * 2 + 1].position = sf::Vector2f(position.x + i * m_cellSize, position.y + meshSize.y * m_cellSize);
		// Set line colors
		m_lines[i * 2].color = sf::Color::Black;
		m_lines[i * 2 + 1].color = sf::Color::Black;
	}

	// Horizontal lines
	for (int i = 0; i < meshSize.y + 1; ++i)
	{
		int index = meshSize.x + 1 + i;
		m_lines[index * 2].position = sf::Vector2f(position.x, position.y + i * m_cellSize);
		m_lines[index * 2 + 1].position = sf::Vector2f(position.x + meshSize.x * m_cellSize, position.y + i * m_cellSize);
		// Set line colors
		m_lines[index * 2].color = sf::Color::Black;
		m_lines[index * 2 + 1].color = sf::Color::Black;
	}
}

////////////////////////////////////////////////////////////
void Mesh::draw(sf::RenderTarget& target, bool drawSquares, bool drawLines)
{
	if (drawSquares)
	{
		target.draw(m_quads);
	}
	if (drawLines)
	{
		target.draw(m_lines);
	}
}

////////////////////////////////////////////////////////////
bool Mesh::isVisible(sf::FloatRect& windowBound)
{
	sf::Vector2f botRight = m_positions + sf::Vector2f(static_cast<float>(m_size.x * m_cellSize), static_cast<float>(m_size.y * m_cellSize));

	return windowBound.intersects(sf::FloatRect(m_positions, botRight - m_positions));
}

////////////////////////////////////////////////////////////
bool Mesh::isInRange(sf::Vector2f mousePos)
{
	sf::Vector2f botRight{ m_positions.x + m_size.x * m_cellSize,m_positions.y + m_size.y * m_cellSize };

	return (mousePos.x >= m_positions.x) &&
		(mousePos.x <= botRight.x) &&
		(mousePos.y >= m_positions.y) &&
		(mousePos.y <= botRight.y);
}

////////////////////////////////////////////////////////////
void Mesh::activateCell(sf::Vector2f mousePos)
{
	// Get cell index
	int col = static_cast<int>(mousePos.x - m_positions.x) / m_cellSize;
	int row = static_cast<int>(mousePos.y - m_positions.y) / m_cellSize;
	int index = row * m_size.x + col;

	// Modify cell if index is in range
	if (index >= 0 && index < m_squareVec.size())
	{
		SquareType& sqType = m_squareVec[index];
		sqType = sqType == SquareType::EMPTY ? SquareType::FULL : SquareType::EMPTY;
		setCellColor(sqType, index);
	}
}

////////////////////////////////////////////////////////////
void Mesh::setCellColor(SquareType sqType, int index)
{
	// Get new color
	sf::Color color;
	switch (sqType)
	{
		case SquareType::EMPTY:
			color = sf::Color::White;
			break;
		case SquareType::FULL:
			color = sf::Color::Green;
			break;
		default:
			color = sf::Color::White;
			break;
	}
	// Change vertex color
	int vertexIndex = index * 4;
	m_quads[vertexIndex].color = color;
	m_quads[vertexIndex + 1].color = color;
	m_quads[vertexIndex + 2].color = color;
	m_quads[vertexIndex + 3].color = color;
}