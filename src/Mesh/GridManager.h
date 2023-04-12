#pragma once
#include <vector>
#include "Mesh.h"

/// <summary>
/// The GridManager class manages a collection of Mesh objects and provides methods for drawing and adding meshes,
/// as well as toggling the display of squares and lines and handling mouse clicks.
/// </summary>
class GridManager
{
public:
	/// <summary>
	/// Draws all meshes within the specified window bounds to the specified render target.
	/// </summary>
	/// <param name="target">The render target to draw to.</param>
	/// <param name="windowBound">The current camera view.</param>
	void draw(sf::RenderTarget& target, sf::FloatRect& windowBound);
	/// <summary>
	/// Adds a new Mesh object with the specified position, mesh size, and cell size to the Mesh vector.
	/// </summary>
	/// <param name="position">The position of the Mesh object.</param>
	/// <param name="meshSize">The size of the Mesh object.</param>
	/// <param name="cellSize">The size of each cell in the Mesh object.</param>
	void addMesh(sf::Vector2f position, sf::Vector2i meshSize, unsigned cellSize);
	/// <summary>
	/// Toggles the drawing of squares on and off.
	/// </summary>
	void switchSquares() { drawSquares = !drawSquares; };
	/// <summary>
	/// Toggles the drawing of lines on and off.
	/// </summary>
	void switchLines() { drawLines = !drawLines; };
	/// <summary>
	/// Handles a mouse click at the specified position, highlighting the cell at that position in the Mesh vector.
	/// </summary>
	/// <param name="mousePos">The position of the mouse click.</param>
	void handleMouseClick(sf::Vector2f mousePos);
private:
	std::vector<Mesh> m_meshVec;		//!< The vector of Mesh objects managed by the GridManager.
	bool drawSquares{ true };			//!< A flag indicating whether to draw squares or not.
	bool drawLines{ true };				//!< A flag indicating whether to draw lines or not.
};