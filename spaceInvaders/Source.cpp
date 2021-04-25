#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include"sprite.h"
#include <math.h>

# define M_PI           3.14159265358979323846


struct line
{
	float a;
	float b;
	float c;
	float x1, x2, y1, y2;
	bool intersected = false;
	void calculate(sf::Vector2f p1, sf::Vector2f p2)
	{
		x1 = p1.x; x2 = p2.x; y1 = p1.y; y2 = p2.y;
		float m = (p2.y - p1.y) / (p2.x - p1.x);
		a = m;
		b = -1.0f;
		c = m * p1.x - p1.y;
	}

	sf::Vector2f intersectWith;
	bool inBetween(sf::Vector2f _1, sf::Vector2f _2, sf::Vector2f t)
	{
		float x1, x2, y1, y2;

		x1 = _1.x < _2.x ? _1.x : _2.x;
		x2 = _1.x < _2.x ? _2.x : _1.x;

		y1 = _1.y < _2.y ? _1.y : _2.y;
		y2 = _1.y < _2.y ? _2.y : _1.y;

		if (t.x > x1 && t.x < x2 && t.y > y1 && t.y < y2)
		{
			return true;
		}
		else
		{
			return false;
		}



	}

	bool intersect(line l2, sf::Vector2f& result)
	{
		float determinant = a * l2.b - l2.a * b;

		if (determinant == 0)
		{

			return false;
		}

		result.x = (c * l2.b - l2.c * b) / determinant;
		result.y = (a * l2.c - l2.a * c) / determinant;
		float x = result.x;
		float y = result.y;

		if (inBetween(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2), result) && inBetween(sf::Vector2f(l2.x1, l2.y1), sf::Vector2f(l2.x2, l2.y2), result))
			return true;
		else
		{
			result.x = 19200.0f;
			result.y = 19200.0f;
			return false;
		}
	}
};

int main()
{
	bool lineSet = false;
	bool triangleSet = false;

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML");

	sprite* p1 = nullptr, * p2 = nullptr, * p3 = nullptr, * n1 = nullptr, * n2 = nullptr;
	bool p11 = false, p22 = false, p33 = false;

	sf::Vector2f* result1 = new sf::Vector2f(19200.0f, 19200.0f), * result2 = new sf::Vector2f(19200.0f, 19200.0f);

	sf::ConvexShape convex;
	sf::ConvexShape intersect;
	sf::ConvexShape triangleShape[3];

	for (int i = 0; i < 3; i++)
	{
		triangleShape[i].setPointCount(3);
	}

	line triangle[3];

	line cut;

	// resize it to 5 points
	convex.setPointCount(3);
	intersect.setPointCount(4);


	//Game Loop
	while (window.isOpen())
	{

		window.setKeyRepeatEnabled(true);
		sf::Mouse mouse;

		window.clear();


		// define the points
		if (p1 != nullptr && p2 != nullptr && p3 != nullptr && !triangleSet)
		{
			convex.setFillColor(sf::Color::Blue);
			convex.setPoint(0, p1->sp.getPosition());
			convex.setPoint(1, p2->sp.getPosition());
			convex.setPoint(2, p3->sp.getPosition());
			triangleSet = true;
			triangle[0].calculate(convex.getPoint(0), convex.getPoint(1));
			triangle[1].calculate(convex.getPoint(1), convex.getPoint(2));
			triangle[2].calculate(convex.getPoint(2), convex.getPoint(0));


		}
		else if (!triangleSet)
		{
			if (p1 != nullptr)
			{
				p1->draw(window);
			}

			if (p2 != nullptr)
			{
				p2->draw(window);
			}

			if (p3 != nullptr)
			{
				p3->draw(window);
			}


		}

		if (p1 != nullptr && p2 != nullptr && p3 != nullptr && n1 != nullptr && n2 != nullptr && !lineSet)
		{
			lineSet = true;
			intersect.setFillColor(sf::Color::Red);
			intersect.setPoint(0, n1->sp.getPosition());
			intersect.setPoint(1, n2->sp.getPosition());
			intersect.setPoint(2, n2->sp.getPosition() + sf::Vector2f(0.0f, 0.0f));
			intersect.setPoint(3, n1->sp.getPosition() + sf::Vector2f(0.0f, 0.0f));
			intersect.setOutlineThickness(1.5f);
			intersect.setOutlineColor(sf::Color::Red);

			cut.calculate(intersect.getPoint(0), intersect.getPoint(1));


			for (int i = 0; i < 3; i++)
			{

				if (*result1 == sf::Vector2f(19200.0f, 19200.0f) && triangle[i].intersect(cut, *result1))
				{
					std::cout << "int1";
					triangle[i].intersected = true;
					triangle[i].intersectWith = *result1;
					continue;
				}

				else if (*result2 == sf::Vector2f(19200.0f, 19200.0f) && triangle[i].intersect(cut, *result2))
				{
					triangle[i].intersected = true;
					triangle[i].intersectWith = *result2;

					std::cout << "int 2";
				}
			}

			if (*result1 != sf::Vector2f(19200.0f, 19200.0f) && *result2 != sf::Vector2f(19200.0f, 19200.0f))
			{
				for (int i = 0; i < 3; i++)
				{
					if (triangle[i].intersected == false)
					{
						if (i == 1 || i == 0)
						{
							line temp = triangle[i];
							triangle[i] = triangle[2];
							triangle[2] = temp;
						}

					}
				}

				if (triangle[0].x1 == triangle[1].x2 && triangle[0].y1 == triangle[1].y2)
				{
					float tx = triangle[1].x1;
					triangle[1].x1 = triangle[1].x2;
					triangle[1].x2 = tx;

					float ty = triangle[1].y1;
					triangle[1].y1 = triangle[1].y2;
					triangle[1].y2 = ty;

				}

				else if (triangle[0].x2 == triangle[1].x1 && triangle[0].y2 == triangle[1].y1)
				{
					float tx = triangle[0].x1;
					triangle[0].x1 = triangle[0].x2;
					triangle[0].x2 = tx;

					float ty = triangle[0].y1;
					triangle[0].y1 = triangle[0].y2;
					triangle[0].y2 = ty;

				}

				else if (triangle[0].x2 == triangle[1].x2 && triangle[0].y2 == triangle[1].y2)
				{
					float tx = triangle[0].x1;
					triangle[0].x1 = triangle[0].x2;
					triangle[0].x2 = tx;

					float ty = triangle[0].y1;
					triangle[0].y1 = triangle[0].y2;
					triangle[0].y2 = ty;

					tx = triangle[1].x1;
					triangle[1].x1 = triangle[1].x2;
					triangle[1].x2 = tx;

					ty = triangle[1].y1;
					triangle[1].y1 = triangle[1].y2;
					triangle[1].y2 = ty;

				}
				triangleShape[0].setFillColor(sf::Color::Red);
				triangleShape[0].setPoint(0, sf::Vector2f(triangle[0].x1, triangle[0].y1));
				triangleShape[0].setPoint(1, *result1);
				triangleShape[0].setPoint(2, *result2);

				triangleShape[1].setFillColor(sf::Color::Blue);
				triangleShape[1].setPoint(0, sf::Vector2f(triangle[0].x2, triangle[0].y2));
				triangleShape[1].setPoint(1, *result1);
				triangleShape[1].setPoint(2, *result2);

				triangleShape[2].setFillColor(sf::Color::Green);
				triangleShape[2].setPoint(0, sf::Vector2f(triangle[0].x2, triangle[0].y2));
				triangleShape[2].setPoint(1, sf::Vector2f(triangle[1].x2, triangle[1].y2));
				triangleShape[2].setPoint(2, triangle[1].intersectWith);

			}
		}

		else if (!lineSet)
		{
			if (n1 != nullptr)
			{
				n1->draw(window);
			}
			if (n2 != nullptr)
			{
				n2->draw(window);
			}
		}

		window.draw(intersect);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			/*p1 = nullptr;
			p2 = nullptr;
			p3 = nullptr;
			n1 = nullptr;
			n2 = nullptr;
			triangleSet = false;

			for (int i = 0; i < 3; i++)
			{
				triangleShape[i].setPointCount(0);
				triangleShape[i].setPointCount(3);
			}
			result1->x = 19200.0f;
			result1->y = 19200.0f;

			result2->x = 19200.0f;
			result2->y = 19200.0f;

			lineSet = false;*/
			window.close();
			main();
		}
		if (triangleSet)
		{
			window.draw(convex);

			for (int i = 0; i < 3; i++)
			{
				window.draw(triangleShape[i]);
			}
		}
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
				else if (p2 == nullptr)
				{
					p22 = true;
					p2 = new sprite(mouse.getPosition(window).x, mouse.getPosition(window).y);
					p2->setTexture("Assets/Point.png");

				}

				else if (p3 == nullptr)
				{
					p33 = true;
					p3 = new sprite(mouse.getPosition(window).x, mouse.getPosition(window).y);
					p3->setTexture("Assets/Point.png");

				}

				else if (n1 == nullptr)
				{
					n1 = new sprite(mouse.getPosition(window).x, mouse.getPosition(window).y);
					n1->setTexture("Assets/Point.png");
				}

				else if (n2 == nullptr)
				{
					n2 = new sprite(mouse.getPosition(window).x, mouse.getPosition(window).y);
					n2->setTexture("Assets/Point.png");
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.display();
	}
}

