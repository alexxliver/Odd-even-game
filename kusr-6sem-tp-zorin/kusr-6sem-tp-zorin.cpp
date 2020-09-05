#include <SFML/Graphics.hpp>

using namespace sf;

//GIT TEST

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(200, 200), "SFML Works!");

	CircleShape c(100);
	c.setFillColor(Color::Magenta);

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// Тогда закрываем его
				window.close();

			window.draw(c);
		}
		// Отрисовка окна
		window.display();
	}

	return 0;
}