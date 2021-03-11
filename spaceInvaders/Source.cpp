#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include"sprite.h"
#include <math.h>

# define M_PI           3.14159265358979323846

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML");

	sprite* p1 = nullptr, *p2 = nullptr, *p3 = nullptr;
	bool p11 = false, p22 = false, p33 = false;
	sprite l1, l2, l3;
	l1.setTexture("Assets/line.png");
	l2.setTexture("Assets/line.png");
	l3.setTexture("Assets/line.png");
	

	
	//Game Loop
	while (window.isOpen())
	{
		
		window.setKeyRepeatEnabled(true);
		sf::Mouse mouse;

		if (p1 != nullptr)
		{
			p1->draw(window);
		}

		if (p22)
		{
			p2->draw(window);
		}

		if (p33)
		{
			p3->draw(window);
		}

		if (p11 && p22 && p33)
		{
			float dist = sqrt((p1->sp.getPosition().x -  p2->sp.getPosition().x) * (p1->sp.getPosition().x - p2->sp.getPosition().x) + (p1->sp.getPosition().y - p2->sp.getPosition().y)* (p1->sp.getPosition().y - p2->sp.getPosition().y));
			float angle = std::atan((p1->sp.getPosition().y - p2->sp.getPosition().y) / (p1->sp.getPosition().x - p2->sp.getPosition().y)) * (180 / M_PI);
			l1.setLocation(p1->sp.getPosition().x, p1->sp.getPosition().y);
			//l1.sp.setOrigin(200, 0);
			l1.sp.setRotation(angle + 180);

			//l1.sp.setScale(dist, 1);
			p11 = false;
		}
		l1.draw(window);
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
			{
				if (p1 == nullptr)
				{
					p11 = true;
					p1 = new sprite(mouse.getPosition(window).x, mouse.getPosition(window).y);
					p1->setTexture("Assets/Point.png");
				
				}
				else if (!p22)
				{
					p22 = true;
					p2 = new sprite(mouse.getPosition(window).x, mouse.getPosition(window).y);
					p2->setTexture("Assets/Point.png");

				}

				else if (!p33)
				{
					p33 = true;
					p3 = new sprite(mouse.getPosition(window).x, mouse.getPosition(window).y);
					p3->setTexture("Assets/Point.png");

				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
	window.display();
	}
}

