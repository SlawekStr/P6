#pragma once
#include "MazeGenerator.h"
#include <random>

class RecursiveDivisionGenerator : public MazeGenerator
{
public:
	RecursiveDivisionGenerator(Mesh* mesh);
	/// <summary>
	/// Update next step of generator
	/// </summary>
	void updateGenerator() override;
	/// <summary>
	/// Is maze generation finished
	/// </summary>
	/// <returns></returns>
	bool isFinished() override;
private:
	void divideMaze(int x, int y, int sectionWidth, int sectionHeight, int orientation);

	int getOrientation(int width, int height);

	int getRandomInt(int min, int max);
private:
	// Random generation
	std::mt19937 m_generator;								//!< Random number generator
	// Other
	bool m_isFinished{ false };								//!< Is generation finished 
	int divisionCounter{};
};
