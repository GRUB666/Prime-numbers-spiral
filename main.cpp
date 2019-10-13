#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>

#define PI 3.14159265
#define RADIUS 500
#define SCALE_K 1

using namespace sf;
using namespace std;

//Screen size
int XS, YS;
Color pointColor = Color::Green;

bool numberIsPrime(int number) //O(n) = n
{
	for (int i = 2; i < number; i++)
	{
		if (number % i == 0)
			return false;
	}

	return true;
}


void calculatePoints(vector<CircleShape> &POINTS, int count)//O(n) = n^2
{
	int number = 1; //current number

	POINTS.clear();

	for (int i = 0; i < count;)
	{
		if (numberIsPrime(number))
		{
			CircleShape NPoint;
			NPoint.setRadius(RADIUS);
			NPoint.setOrigin(RADIUS / 2, RADIUS / 2);
			NPoint.setPosition((number * cos(number) + XS/2)*SCALE_K, (YS / 2 - number * sin(number))*SCALE_K);
			NPoint.setFillColor(pointColor);

			POINTS.push_back(NPoint);
			i++;
		}
		number++;
	}
}

int main()
{
	XS = 1366, YS = 768;

	int Count = 20000; //Count of prime numbers

	vector<CircleShape> POINTS;
	View view;

	view.setSize(XS, YS);

    RenderWindow window(sf::VideoMode(XS, YS), "Prime spirals", Style::Fullscreen);

	//Control settings
	float camSpeed = 5;
	float camSizeSpeed = 0.03;

	calculatePoints(POINTS, Count);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Control
		{
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
			{
				//camPosX += camSpeed;
				view.move(camSpeed, 0);
				//isShowOrbits = false;
			}


			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
			{
				view.move(-camSpeed, 0);
			}


			if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
			{
				view.move(0, -camSpeed);
			}


			if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
			{
				view.move(0, camSpeed);
			}

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					view.zoom(1 - (event.mouseWheelScroll.delta * camSizeSpeed) * 0.5);
					camSpeed = 1 * (1 - (event.mouseWheelScroll.delta * camSizeSpeed));
				}
			}
		}

     	window.setView(view);
		window.clear();

		for (auto &var : POINTS)
		{
			window.draw(var);
		}

		window.display();
	}

	return 0;
}