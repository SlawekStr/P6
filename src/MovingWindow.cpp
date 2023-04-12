#include "MovingWindow.h"
#include "src/Utility/Timer.h"
#include <iostream>

////////////////////////////////////////////////////////////
MovingWindow::MovingWindow(unsigned windowWidth, unsigned windowHeight, std::string windowTitle, unsigned framerate) 
	: Window{windowWidth,windowHeight,windowTitle,framerate}, m_camera{ m_window }
{
	// Create grids
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			m_gridManager.addMesh(sf::Vector2f(20.0f * i, 20.0f * j), sf::Vector2i(10, 10), 1);
		}
	}
}

////////////////////////////////////////////////////////////
void MovingWindow::run()
{
	Timer t;
	while (m_window.isOpen())
	{
		t.start();
		pollEvent();
		update();
		m_window.clear(sf::Color(128, 128, 128));
		draw();
		m_window.display();
		t.stop();
		std::cout << "Frame time: " << t.measure() << std::endl;
	}
}

////////////////////////////////////////////////////////////
void MovingWindow::pollEvent()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		if (m_camera.handleEvent(e))
		{
			break;
		}
		switch (e.type)
		{
			case sf::Event::Closed:
			{
				m_window.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (e.key.code == sf::Keyboard::Escape)
				{
					m_window.close();
				}
				else if (e.key.code == sf::Keyboard::Z)
				{
					m_gridManager.switchSquares();
				}
				else if (e.key.code == sf::Keyboard::X)
				{
					m_gridManager.switchLines();
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (e.key.code == sf::Mouse::Button::Left)
				{
					m_gridManager.addMesh(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)), sf::Vector2i(5, 10), 5);
				}
				else if (e.key.code == sf::Mouse::Button::Right)
				{
					m_gridManager.handleMouseClick(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
				}
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////
void MovingWindow::update()
{
}

////////////////////////////////////////////////////////////
void MovingWindow::draw()
{
	sf::FloatRect viewBound = m_camera.getGlobalViewBounds();
	m_gridManager.draw(m_window, viewBound);
}
