#include "GridManager.h"
#include <iostream>
#include "src/Solvers/DFSSolver.h"
#include "src/Solvers/BFSSolver.h"
#include "src/Solvers/DjikstraSolver.h"
#include "src/Solvers/AStarSolver.h"

////////////////////////////////////////////////////////////
GridManager::GridManager()
{
	if (!m_font.loadFromFile("Resources/arial.ttf"))
	{
		// handle font loading error
		throw std::runtime_error("Failed to load font file: arial.ttf");
	}
}

////////////////////////////////////////////////////////////
void GridManager::draw(sf::RenderTarget& target, sf::FloatRect& windowBound)
{
	int index{};
	for (auto it = m_meshVec.begin(); it != m_meshVec.end(); ++it)
	{
		if (it->isVisible(windowBound))
		{
			it->draw(target, m_font, drawSquares, drawLines, drawWeights);
		}
		if (it != std::prev(m_meshVec.end()))
		{
			std::string solverName = m_solvers[index]->getSolverName();
			int processedCells = m_solvers[index]->getProcessedSquares();
			int pathLength = m_solvers[index]->getPathLength();
			int pathWeight = m_solvers[index]->getPathWeight();
			it->drawData(target, m_font, solverName, processedCells, pathLength, pathWeight);
		}
		index++;
	}
}

////////////////////////////////////////////////////////////
void GridManager::addMesh(sf::Vector2f position, sf::Vector2i meshSize, unsigned cellSize, SolverType solverType)
{
	m_meshVec.emplace_back(position, meshSize, cellSize);
	switch (solverType)
	{
	case SolverType::DFS:
		m_solvers.emplace_back(std::make_unique<DFSSolver>(&m_meshVec.back()));
		break;
	case SolverType::BFS:
		m_solvers.emplace_back(std::make_unique<BFSSolver>(&m_meshVec.back()));
		break;
	case SolverType::DJIKSTRA:
		m_solvers.emplace_back(std::make_unique<DjikstraSolver>(&m_meshVec.back()));
		break;
	case SolverType::ASTAR:
		m_solvers.emplace_back(std::make_unique<AStarSolver>(&m_meshVec.back()));
		break;
	}
}

////////////////////////////////////////////////////////////
void GridManager::addMesh(sf::Vector2f position, sf::Vector2i meshSize, unsigned cellSize)
{
	m_meshVec.emplace_back(position, meshSize, cellSize);
}

////////////////////////////////////////////////////////////
void GridManager::setSquareType(sf::Vector2f mousePos, SquareType squareType)
{
	int index{};

	for (auto it = m_meshVec.begin(); it != m_meshVec.end(); ++it)
	{
		if (it->isInRange(mousePos))
		{
			it->setCellType(mousePos, squareType);
			if (it != std::prev(m_meshVec.end()))
			{
				clearMesh(index);
			}
			return;
		}
		index++;
	}
}

////////////////////////////////////////////////////////////
void GridManager::changeSquareWeight(sf::Vector2f mousePos, bool isPositive)
{
	int index{};
	for (auto it = m_meshVec.begin(); it != m_meshVec.end(); ++it)
	{
		if (it->isInRange(mousePos))
		{
			if (isPositive)
			{
				it->addCellWeight(mousePos);
			}
			else
			{
				it->subCellWeight(mousePos);
			}
			if (it != std::prev(m_meshVec.end()))
			{
				clearMesh(index);
			}
			return;
		}
		index++;
	}
}

////////////////////////////////////////////////////////////
void GridManager::copyTemplateMesh()
{
	Mesh& mesh = m_meshVec.back();
	int index{};
	for (auto it = m_meshVec.begin(); it != std::prev(m_meshVec.end()); ++it)
	{
		it->copyMesh(mesh);
		clearMesh(index);
		index++;
	}
}

////////////////////////////////////////////////////////////
void GridManager::update()
{
	for (auto& solver : m_solvers)
	{
		solver->update();
	}
}

////////////////////////////////////////////////////////////
void GridManager::generateMaze()
{

}

////////////////////////////////////////////////////////////
void GridManager::clearMesh(int index)
{
	if (!m_solvers[index]->isClear())
	{
		m_solvers[index]->reset();

		auto it = m_meshVec.begin();
		std::advance(it, index);
		it->resetMesh();
	}
}
