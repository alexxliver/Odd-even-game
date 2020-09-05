#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(640, 360), "Odd Even Game.");
Clock clk;

int** field;
int size;

int startScreen()
{
	if (!window.isOpen()) return 2;

	bool
		written = false,
		faded = false;
	int r[9][16];
	float timer = 0, alpha;
	srand(time(0));

	Font font;
	font.loadFromFile("SIMPLER.TTF");

	Text nums[9][16];
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			r[i][j] = rand() % 4;
			switch (r[i][j])
			{
			case 0:
				nums[i][j].setFillColor(Color(255, 0, 58));
				nums[i][j].setString('0');
				break;
			case 1:
				nums[i][j].setFillColor(Color(0, 123, 211));
				nums[i][j].setString('0');
				break;
			case 2:
				nums[i][j].setFillColor(Color(255, 0, 58));
				nums[i][j].setString('1');
				break;
			case 3:
				nums[i][j].setFillColor(Color(0, 123, 211));
				nums[i][j].setString('1');
				break;
			}
			nums[i][j].setFont(font);
			nums[i][j].setCharacterSize(40);
			nums[i][j].move(j * 40 + 6, i * 40 - 6);
			nums[i][j].setOutlineColor(Color(255, 255, 255));
			nums[i][j].setOutlineThickness(2);
		}
	}

	Text logo[2], menu[3];
	for (int i = 0; i < 3; ++i)
	{
		menu[i].setFillColor(Color(255, 0, 58, 0));
		menu[i].setFont(font);
		menu[i].setCharacterSize(40);
		menu[i].move(120, 140 + 50 * i);
		menu[i].setOutlineColor(Color(255, 255, 255, 0));
		menu[i].setOutlineThickness(1);
		if (i != 2)
		{
			logo[i].setFont(font);
			logo[i].setCharacterSize(80);
			logo[i].move(100 + 225 * i, 30);
			logo[i].setOutlineColor(Color(255, 255, 255, 0));
			logo[i].setOutlineThickness(3);
		}
	}
	logo[0].setString(L"Чёт •");
	logo[1].setString(L"Нечет");
	logo[0].setFillColor(Color(255, 0, 58, 0));
	logo[1].setFillColor(Color(0, 123, 211, 0));
	menu[0].setString(L"• Начать игру");
	menu[1].setString(L"• Правила игры");
	menu[2].setString(L"• Выход");

	int i = 0;
	window.clear(Color::Black);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		window.clear(Color::Black);

		if ((clk.getElapsedTime().asSeconds() - timer) >= 0.01 && !written)
		{
			timer = clk.getElapsedTime().asSeconds();
			++i;
		}

		if (written && !faded)
		{
			if ((clk.getElapsedTime().asSeconds() - timer) <= 2)
			{
				alpha = (1 - (clk.getElapsedTime().asSeconds() - timer) / 2.0f) * 255.0f;
				for (int j = 0; j < i; ++j)
				{
					if(r[j / 16][j % 16] % 2 == 0)
						nums[j / 16][j % 16].setFillColor(Color(255, 0, 58, alpha));
					else
						nums[j / 16][j % 16].setFillColor(Color(0, 123, 211, alpha));
					nums[j / 16][j % 16].setOutlineColor(Color(255, 255, 255, alpha));
				}

				for (int i = 0; i < 3; ++i)
				{
					menu[i].setFillColor(Color(255, 0, 58, 255 - alpha));
					menu[i].setOutlineColor(Color(255, 255, 255, 255 - alpha));
				}	
				logo[0].setFillColor(Color(255, 0, 58, 255 - alpha));
				logo[1].setFillColor(Color(0, 123, 211, 255 - alpha));
				logo[0].setOutlineColor(Color(255, 255, 255, 255 - alpha));
				logo[1].setOutlineColor(Color(255, 255, 255, 255 - alpha));
			}
			if ((clk.getElapsedTime().asSeconds() - timer) >= 2) faded = true;
		}
		
		if (!faded)
		{
			for (int j = 0; j < i; ++j)
				window.draw(nums[j / 16][j % 16]);
		}
		if (i == (9 * 16)) written = true;

		if (written)
		{
			for (int i = 0; i < 3; ++i)
			{
				window.draw(menu[i]);
				if (i != 2)
				{
					window.draw(logo[i]);
				}
			}
		}

		window.display();
	}
}

void gameScreen()
{

}

void rulesScreen()
{

}

int main()
{
	while (1)
	{
		switch (startScreen())
		{
		case 0:
			gameScreen();
			break;
		case 1:
			rulesScreen();
			break;
		case 2:
			return 0;
		}
	}
}