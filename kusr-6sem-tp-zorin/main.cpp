#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(640, 360), "Odd Even Game.");
Clock clk;

int** field;
int n;

Text** num;
RectangleShape** grid;

bool
written = false,
faded = false,
server = false,
turn = false,
number = false,
ended = false;

int startScreen()
{
	if (!window.isOpen()) return 2;

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

	if (faded)
	{
		for (int i = 0; i < 3; ++i)
		{
			menu[i].setFillColor(Color(255, 0, 58, 255));
			menu[i].setOutlineColor(Color(255, 255, 255, 255));
			if (i != 2)
				logo[i].setOutlineColor(Color(255, 255, 255, 255));
		}
		logo[0].setFillColor(Color(255, 0, 58, 255));
		logo[1].setFillColor(Color(0, 123, 211, 255));
	}

	int i = 0;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return 2;
			}

			for (int i = 0; i < 3; ++i)
			{
				if (IntRect(120, 140 + 50 * i, 330, 40).contains(Mouse::getPosition(window)) && faded)
				{
					menu[i].setFillColor(Color(0, 123, 211));

					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
					{
						return i;
					}
				}
				else
				{
					menu[i].setFillColor(Color(255, 0, 58));
				}
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
			if (alpha < 1) faded = true;
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

int choiceScreen(int c)
{
	Font font;
	font.loadFromFile("SIMPLER.TTF");

	Text header[4], option[22];
	for (int i = 0; i < 22; ++i)
	{
		if (i < 4)
		{
			header[i].setFillColor(Color(0, 123, 211));
			header[i].setFont(font);
			header[i].setCharacterSize(40);
			header[i].setOutlineColor(Color(255, 255, 255));
			header[i].setOutlineThickness(1);
		}
		option[i].setFillColor(Color(255, 0, 58));
		option[i].setFont(font);
		option[i].setCharacterSize(30);
		option[i].setOutlineColor(Color(255, 255, 255));
		option[i].setOutlineThickness(1);
	}
	header[0].setString(L"Режим игры:");
	header[0].move(50, 30);
	option[0].setString(L"• 2 игрока");
	option[1].setString(L"• С компьютером");
	option[0].move(50, 120);
	option[1].move(300, 120);
	header[1].setString(L"Выбор игрока:");
	header[1].move(50, 30);
	option[2].setString(L"• Нечётный");
	option[3].setString(L"• Чётный");
	option[2].setFillColor(Color(0, 123, 211));
	option[2].move(50, 120);
	option[3].move(400, 120);
	header[2].setString(L"Размер поля:");
	header[2].move(50, 30);
	option[4].setString(L"• 3х3");
	option[5].setString(L"• 4х4");
	option[6].setString(L"• 5х5");
	option[7].setString(L"• 6х6");
	option[8].setString(L"• 7х7");
	option[9].setString(L"• 8х8");
	for (int i = 4; i < 10; ++i)
		option[i].move(50, 130 + 40 * (i - 5));
	option[10].setString(L"• 9х9");
	option[11].setString(L"• 10х10");
	option[12].setString(L"• 11х11");
	option[13].setString(L"• 12х12");
	option[14].setString(L"• 13х13");
	option[15].setString(L"• 14х14");
	for (int i = 10; i < 16; ++i)
		option[i].move(225, 130 + 40 * (i - 11));
	option[16].setString(L"• 15х15");
	option[17].setString(L"• 16х16");
	option[18].setString(L"• 17х17");
	option[19].setString(L"• 18х18");
	for (int i = 16; i < 20; ++i)
		option[i].move(400, 130 + 40 * (i - 17));
	header[3].setString(L"Пауза");
	header[3].move(50, 30);
	option[20].setString(L"• Продолжить игру");
	option[21].setString(L"• Выход");
	option[20].move(50, 120);
	option[21].move(400, 120);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return 1;
			}

			switch (c)
			{
			case 0:
				if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
				{
					if (IntRect(50, 120, 160, 40).contains(Mouse::getPosition(window)))
						server = false;
					else if (IntRect(300, 120, 270, 40).contains(Mouse::getPosition(window)))
						server = true;
					return 0;
				}
				break;
			case 1:
				if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
				{
					if (IntRect(50, 120, 175, 40).contains(Mouse::getPosition(window)))
						turn = false;
					else if (IntRect(400, 120, 140, 40).contains(Mouse::getPosition(window)))
						turn = true;
					return 0;
				}
				break;
			case 2:
				for (int i = 4; i < 20; ++i)
				{
					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
					{
						if (i < 10 && IntRect(50, 130 + 40 * (i - 5), 115, 40).contains(Mouse::getPosition(window)))
						{
							n = i - 1;
							return 0;
						} 
						else if (i < 16 && i >= 10 &&
							IntRect(225, 130 + 40 * (i - 11), 115, 40).contains(Mouse::getPosition(window)))
						{
							n = i - 1;
							return 0;
						}
						else if (i < 20 && i >= 16 &&
							IntRect(400, 130 + 40 * (i - 17), 115, 40).contains(Mouse::getPosition(window)))
						{
							n = i - 1;
							return 0;
						}
					}
				}
				break;
			case 3:
				if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
				{
					if (IntRect(50, 120, 300, 40).contains(Mouse::getPosition(window)))
						return 0;
					else if (IntRect(400, 120, 130, 40).contains(Mouse::getPosition(window)))
						return 1;
				}
				break;
			}

			switch (c)
			{
			case 0:
				if (IntRect(50, 120, 160, 40).contains(Mouse::getPosition(window)))
					option[0].setFillColor(Color(0, 123, 211));
				else if (IntRect(300, 120, 270, 40).contains(Mouse::getPosition(window)))
					option[1].setFillColor(Color(0, 123, 211));
				else
				{
					option[0].setFillColor(Color(255, 0, 58));
					option[1].setFillColor(Color(255, 0, 58));
				}
				break;
			case 1:
				if (IntRect(50, 120, 175, 40).contains(Mouse::getPosition(window)))
					option[2].setFillColor(Color(255, 0, 58));
				else if (IntRect(400, 120, 140, 40).contains(Mouse::getPosition(window)))
					option[3].setFillColor(Color(0, 123, 211));
				else
				{
					option[2].setFillColor(Color(0, 123, 211));
					option[3].setFillColor(Color(255, 0, 58));
				}
				break;
			case 2:
				for (int i = 4; i < 20; ++i)
				{
					if (i < 10 && IntRect(50, 130 + 40 * (i - 5), 115, 40).contains(Mouse::getPosition(window)))
						option[i].setFillColor(Color(0, 123, 211));
					else if (i < 16 && i >= 10 && 
						IntRect(225, 130 + 40 * (i - 11), 115, 40).contains(Mouse::getPosition(window)))
						option[i].setFillColor(Color(0, 123, 211));
					else if (i < 20 && i >= 16 &&
						IntRect(400, 130 + 40 * (i - 17), 115, 40).contains(Mouse::getPosition(window)))
						option[i].setFillColor(Color(0, 123, 211));
					else
					{
						option[i].setFillColor(Color(255, 0, 58));
					}
				}
				break;
			case 3:
				if (IntRect(50, 120, 300, 40).contains(Mouse::getPosition(window)))
					option[20].setFillColor(Color(0, 123, 211));
				else if (IntRect(400, 120, 130, 40).contains(Mouse::getPosition(window)))
					option[21].setFillColor(Color(0, 123, 211));
				else
				{
					option[20].setFillColor(Color(255, 0, 58));
					option[21].setFillColor(Color(255, 0, 58));
				}
				break;
			}
		}

		window.clear(Color::Black);

		switch(c)
		{
		case 0:
			window.draw(header[0]);
			window.draw(option[0]);
			window.draw(option[1]);
			break;
		case 1:
			window.draw(header[1]);
			window.draw(option[2]);
			window.draw(option[3]);
			break;
		case 2:
			window.draw(header[2]);
			for (int i = 4; i < 20; ++i)
				window.draw(option[i]);
			break;
		case 3:
			window.draw(header[3]);
			window.draw(option[20]);
			window.draw(option[21]);
			break;
		}

		window.display();
	}
}

void clear()
{
	for (int i = 0; i < n; ++i)
	{
		delete[] field[i];
		delete[] num[i];
		delete[] grid[i];
	}	
	delete[] field;
	delete[] num;
	delete[] grid;
}

void gameScreen()
{
	choiceScreen(0);
	if (server) 
		choiceScreen(1);
	choiceScreen(2);

	number = false;
	ended = false;

	field = new int*[n];
	for (int i = 0; i < n; ++i)
		field[i] = new int[n];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			field[i][j] = -1;

	Font font;
	font.loadFromFile("SIMPLER.TTF");

	Text cursor, tturn[2], pause;
	num = new Text* [n];
	for (int i = 0; i < n; ++i)
		num[i] = new Text[n];

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			num[i][j].setFont(font);
			num[i][j].setOutlineColor(Color(255, 255, 255));
			num[i][j].setOutlineThickness(1);
			num[i][j].move((0.1021 * n * n - 3.0154 * n + 36.6780) + (340 / n) * i,
				(-0.0579 * n * n + 1.8743 * n - 4.9971) + (340 / n) * j);
			num[i][j].setCharacterSize(340 / n - 5);
		}

		if (i == 0 || i == 1)
		{
			tturn[i].setFont(font);
			tturn[i].setOutlineColor(Color(255, 255, 255));
			tturn[i].move(400, 100 + 45 * i);
		}
	}
	cursor.setFont(font);
	cursor.setOutlineColor(Color::Yellow);
	cursor.setOutlineThickness(1.75);
	cursor.setString('0');
	cursor.setCharacterSize(20);

	pause.setFont(font);
	pause.setOutlineColor(Color(255, 255, 255));
	pause.setOutlineThickness(1);
	tturn[0].setOutlineThickness(1);
	pause.setString(L"• Пауза");
	tturn[0].setString(L"Очередь:");
	pause.setCharacterSize(40);
	tturn[0].setCharacterSize(40);
	tturn[1].setCharacterSize(30);
	tturn[0].setFillColor(Color(0, 123, 211));
	pause.move(470, 5);

	grid = new RectangleShape* [n];
	for (int i = 0; i < n; ++i)
		grid[i] = new RectangleShape[n];

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			grid[i][j].setSize(Vector2f(340 / n, 340 / n));
			grid[i][j].setOutlineColor(Color(255, 255, 255));
			grid[i][j].setOutlineThickness(2);
			grid[i][j].setFillColor(Color(0, 0, 0, 255));
			grid[i][j].move(10 + (340 / n) * i, 10 + (340 / n) * j);
		}
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				clear();
				window.close();
				return;
			}

			if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					for (int i = 0; i < n; ++i)
					{
						for (int j = 0; j < n; ++j)
						{
							if (IntRect(10 + (340 / n) * i, 10 + (340 / n) * j, 340 / n, 340 / n).
								contains(Mouse::getPosition(window)) && field[i][j] == -1)
							{
								if (turn)
									num[i][j].setFillColor(Color(255, 0, 58));
								else
									num[i][j].setFillColor(Color(0, 123, 211));
								if (number)
									num[i][j].setString('1');
								else
									num[i][j].setString('0');

								if (number)
									field[i][j] = 1;
								else
									field[i][j] = 0;

								if (!turn)
									turn = true;
								else
									turn = false;
							}
						}
					}
				}
				if (event.mouseButton.button == Mouse::Right)
				{
					if (!number)
						number = true;
					else
						number = false;
				}
			}

			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					if (IntRect(10 + (340 / n) * i, 10 + (340 / n) * j, 340 / n, 340 / n).
						contains(Mouse::getPosition(window)) && field[i][j] == -1)
					{
						if (turn)
							grid[i][j].setFillColor(Color(255, 0, 58));
						else
							grid[i][j].setFillColor(Color(0, 123, 211));
					}
					else
						grid[i][j].setFillColor(Color(0, 0, 0));
				}
			}

			if (IntRect(470, 5, 155, 40).contains(Mouse::getPosition(window)))
			{
				pause.setFillColor(Color(0, 123, 211));

				if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
				{
					if (choiceScreen(3))
					{
						turn = false;
						return;
					}
				}	
			}
			else
				pause.setFillColor(Color(255, 0, 58));
		}

		window.clear(Color::Black);

		cursor.setPosition(Vector2f(Mouse::getPosition(window)));
		cursor.move(3, -22);

		if (turn)
		{
			cursor.setFillColor(Color(255, 0, 58));
			tturn[1].setFillColor(Color(255, 0, 58));
			tturn[1].setString(L"Чётный");
		}
		else
		{
			cursor.setFillColor(Color(0, 123, 211));
			tturn[1].setFillColor(Color(0, 123, 211));
			tturn[1].setString(L"Нечётный");
		}
			
		if (number) 
			cursor.setString('1');
		else 
			cursor.setString('0');

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				window.draw(grid[i][j]);
				window.draw(num[i][j]);
			}
		}

		ended = true;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (field[i][j] == -1)
				{
					ended = false;
					break;
				}
			}
			if (!ended)
				break;
		}

		if (!ended)
		{
			window.draw(pause);
			window.draw(tturn[0]);
			window.draw(tturn[1]);
		}
		else
		{

		}
		window.draw(cursor);

		window.display();
	}
}

void rulesScreen()
{
	Font font;
	font.loadFromFile("SIMPLER.TTF");

	Text header[2], rules[11], back;
	for (int i = 0; i < 11; ++i)
	{
		if (i < 2)
		{
			header[i].setFillColor(Color(0, 123, 211));
			header[i].setFont(font);
			header[i].setCharacterSize(40);
			header[i].setOutlineColor(Color(255, 255, 255));
			header[i].setOutlineThickness(1);
			header[i].move(10, 200 * i);
		}
		rules[i].setFillColor(Color(255, 0, 58));
		rules[i].setFont(font);
		rules[i].setCharacterSize(15);
		rules[i].setOutlineColor(Color(255, 255, 255));
		rules[i].setOutlineThickness(0);
		if (i < 9)
			rules[i].move(10, 50 + 15 * i);
		else
			rules[i].move(10, 115 + 15 * i);
		
	}
	back.setFillColor(Color(255, 0, 58));
	back.setFont(font);
	back.setCharacterSize(40);
	back.setOutlineColor(Color(255, 255, 255));
	back.setOutlineThickness(1);
	back.move(450, 300);

	header[0].setString(L"Правила:");
	header[1].setString(L"Управление:");
	rules[0].setString(L"Два игрока, «нечетный» и «четный», по очереди ставят единицы и ну-");
	rules[1].setString(L"ли в незанятые позиции поля заданного размера (3х3, 4х4 и т.д.).");
	rules[2].setString(L"Каждый из игроков может ставить 1 или 0 в произвольную свободную");
	rules[3].setString(L"позицию, тем самым занимая ее. Игра продолжается до заполнения всех");
	rules[4].setString(L"позиций. После этого суммируются числа вдоль каждой строки, каждо-");
	rules[5].setString(L"го столбца и главных диагоналей. Число нечетных сумм сравнивается");
	rules[6].setString(L"с числом четных сумм. Если Число нечетных сумм больше Числа четных");
	rules[7].setString(L"сумм, выигрывает «нечетный»; иначе выигрывает «четный»; если чис-");
	rules[8].setString(L"ла равны, результат считается ничейным.");
	rules[9].setString(L"• ЛКМ - Установка числа на игровое поле");
	rules[10].setString(L"• ПКМ - Смена устанавливаемого числа (0/1)");
	back.setString(L"• Назад");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return;
			}

			if (IntRect(450, 300, 160, 40).contains(Mouse::getPosition(window)))
			{
				back.setFillColor(Color(0, 123, 211));

				if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
					return;
			}
			else
			{
				back.setFillColor(Color(255, 0, 58));
			}
		}

		window.clear(Color::Black);

		window.draw(header[0]);
		window.draw(header[1]);
		for (int i = 0; i < 11; ++i)
		{
			window.draw(rules[i]);
		}
		window.draw(back);

		window.display();
	}
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