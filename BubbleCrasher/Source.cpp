#include "GameMain.h"
using namespace sf;

int main()
{
	srand(time(0));// ������
	RenderWindow window(VideoMode(1280, 720), "Bubble Crasher!");//������� ���� ����
	
	Game(window);// ������� � ������� ���������

	return 0;
}