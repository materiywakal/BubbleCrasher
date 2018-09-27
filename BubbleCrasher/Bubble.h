#include <SFML/Graphics.hpp>
#include "math.h"
using namespace sf;
class Bubble//����� ������
{
public:
	float  w, h, speed, CurrentFrame, dublTime; // ������ ����, ������ ����, ��������, ������� ����(��� �������� ������), ����� ����������
	int random;//���������� ��� ������������ �����������
	bool life;// ����� ����
	Vector2f bcord, direct;// ���������� ����, ����� ����
	String File; //������ ��� �������� ����, �� �������� ����� ������� �������� ����
	Texture texture;// �������� ��� �������� �������� ����
	Sprite sprite;// ������ ����
	Bubble(String F, float X, float Y, float W, float H)// �����������, � ������� �� ������� ���� � �������� ����, �����. � ����, � ����, ������ ����, ������ ����
	{
		bcord.x = X; bcord.y = Y;

		//������� ���������� ���������� �����������
		direct.x = (float)rand() / RAND_MAX*(1);
		random = rand() % 2;
		switch (random)
		{
		case 0:
		{
			direct.y = sqrt(1 - pow(direct.x, 2));
			break;
		}
		case 1:
		{
			direct.y = -sqrt(1 - pow(direct.x, 2));
			direct.x = -direct.x;
			break;
		}
		}

		speed = 0.3;
		File = F;
		w = W; h = H;
		texture.loadFromFile(File);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));//������� ��� ������� �������. �������
		sprite.setOrigin(W / 2, H / 2);//��������� ������ ��������� ������� � �����
		life = true;
		CurrentFrame = 0;
		dublTime = 0;
	}
	void update(float time, float seconds)//������� ������� ��������� ���(�������, ����������� ��������)
	{
		if (life)//���� ��� ���
		{
			dublTime += seconds;//��������� ����� ����������
			bcord += direct*time;//������ �������
			sprite.setPosition(bcord.x, bcord.y); // ������ ������� ��� ������� ����� ������
			interactionWithMap();//������������ � ������
		}
		else//���� ���
		{
			speed = 0;
			sprite.setPosition(bcord.x, bcord.y);
		}
	}
	void interactionWithMap()// ������� �������� ������������ ���� � �������� (������� ����)
	{
		//������� �������
		if (bcord.y < h / 2)
		{
			Vector2f normal(0, 1);
			direct = direct - (normal*2.f)*(normal.x*direct.x + normal.y*direct.y);
			bcord.y = h / 2;
		}
		//������ �������
		if ((1280 - (bcord.x + w / 2)) < 0)
		{
			Vector2f normal(-1, 0);
			direct = direct - (normal*2.f)*(normal.x*direct.x + normal.y*direct.y);
			bcord.x = 1280 - w / 2;
		}
		//������ �������
		if ((720 - (bcord.y + h / 2)) < 0)
		{
			Vector2f normal(0, -1);
			direct = direct - (normal*2.f)*(normal.x*direct.x + normal.y*direct.y);
			bcord.y = 720 - w / 2;
		}
		//����� �������
		if (bcord.x < w / 2)
		{
			Vector2f normal(1, 0);
			direct = direct - (normal*2.f)*(normal.x*direct.x + normal.y*direct.y);
			bcord.x = w / 2;
		}
	}
	void Collision(Vector2f *cord2, Vector2f *direct2, bool life2)//������������ ����� ���� � ������
	{
		if (sqrt(pow(cord2->x - bcord.x, 2) + pow(cord2->y - bcord.y, 2)) <= 70 && life == true && life2 == true) {}//���� ���������� ����� �� �������� < 70 �� ������ �� ����������
		else if (sqrt(pow(cord2->x - bcord.x, 2) + pow(cord2->y - bcord.y, 2)) <= 100 && life == true && life2 == true)//���� >70 � <100 �� ���������� ������������
		{
			//���������� ����� ��������
			Vector2f buf;
			buf.x = cord2->x - bcord.x;
			buf.y = cord2->y - bcord.y;
			buf.x = buf.x / (sqrt(pow(buf.x, 2) + pow(buf.y, 2)));
			buf.y = buf.y / (sqrt(pow(buf.x, 2) + pow(buf.y, 2)));

			//�������� �����
			int buff = 100 - sqrt(pow(cord2->x - bcord.x, 2) + pow(cord2->y - bcord.y, 2)) + 5;
			bcord.x -= buf.x * buff;
			bcord.y -= buf.y * buff;
			cord2->x += buf.x * buff;
			cord2->y += buf.y * buff;

			//��������� ����������� ��������
			Vector2f directbuf = (buf*2.f)*(buf.x*direct2->x + buf.y*direct2->y);
			direct = direct - (buf*2.f)*(buf.x*direct.x + buf.y*direct.y);
			direct2->x -= (directbuf.x);
			direct2->y -= (directbuf.y);

			//������������ ��������
			direct.x = direct.x / (sqrt(pow(direct.x, 2) + pow(direct.y, 2)));
			direct.y = direct.y / (sqrt(pow(direct.x, 2) + pow(direct.y, 2)));
			direct2->x = direct2->x / (sqrt(pow(direct2->x, 2) + pow(direct2->y, 2)));
			direct2->y = direct2->y / (sqrt(pow(direct2->x, 2) + pow(direct2->y, 2)));
		}
	}
};

