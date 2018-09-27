#include "GameMain.h"
using namespace sf;

int main()
{
	srand(time(0));// рандом
	RenderWindow window(VideoMode(1280, 720), "Bubble Crasher!");//создаем окно игры
	
	Game(window);// функция с игровым процессом

	return 0;
}