#include <SFML/Graphics.hpp>
using namespace sf;

class Expirience
{
public:
	float exp;//переменна€ дл€ записи попаданий 
	float miss;//переменна€ дл€ записи промахов
	float gametime;//переменна€ содержаща€ врем€
	bool afrmt;//запуск/остановка таймера
	float accuracy;//переменна€ дл€ записи точности попаданий в %
	Expirience()
	{
		exp = 0;
		miss = 0;
		gametime = 0;
		afrmt = true;
		accuracy = 0;
	}
	void GameTimer(float time)//«апись времени
	{
		if (afrmt)
			gametime = gametime + time;
	}
	void Reset()//ќбнуление после завершени€ игры
	{
		gametime = 0;
		exp = 0;
		miss = 0;
	}
	int Accuracy()//ѕодсчет точности
	{
		accuracy = (exp / (miss + exp)) * 100;
		return accuracy;
	}
	void BKilled()//ѕопадание по шару
	{
		exp++;
	}
	void BMissed()//ѕромах по шару
	{
		miss++;
	}
};
