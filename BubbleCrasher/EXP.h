#include <SFML/Graphics.hpp>
using namespace sf;

class Expirience
{
public:
	float exp;//���������� ��� ������ ��������� 
	float miss;//���������� ��� ������ ��������
	float gametime;//���������� ���������� �����
	bool afrmt;//������/��������� �������
	float accuracy;//���������� ��� ������ �������� ��������� � %
	Expirience()
	{
		exp = 0;
		miss = 0;
		gametime = 0;
		afrmt = true;
		accuracy = 0;
	}
	void GameTimer(float time)//������ �������
	{
		if (afrmt)
			gametime = gametime + time;
	}
	void Reset()//��������� ����� ���������� ����
	{
		gametime = 0;
		exp = 0;
		miss = 0;
	}
	int Accuracy()//������� ��������
	{
		accuracy = (exp / (miss + exp)) * 100;
		return accuracy;
	}
	void BKilled()//��������� �� ����
	{
		exp++;
	}
	void BMissed()//������ �� ����
	{
		miss++;
	}
};
