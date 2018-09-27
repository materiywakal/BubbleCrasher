#include <SFML/Graphics.hpp>
#include "Bubble.h"
#include "EXP.h"
#include <list>
#include <vector>
#include <sstream>
#include "fstream"
using namespace sf;
static int maxb = 40;//максимальное количество шаров на карте
void Game(RenderWindow &window)//Эта функция-все
{
	Clock clock;

	/////////////////////////ЗАГРУЗКА ТЕКСТУРОК И ПР.////////////////////////////
	Texture map, playbutton, cursor, cursormiddle, fullscreen, difficulty;
	map.loadFromFile("images/background.png");// текстура фона
	difficulty.loadFromFile("images/difficulty.png");
	fullscreen.loadFromFile("images/fullscreen.png");
	playbutton.loadFromFile("images/playbutton.png");
	cursor.loadFromFile("images/cursor.png");
	cursor.setSmooth(true);
	cursormiddle.loadFromFile("images/cursormiddle.png");
	cursormiddle.setSmooth(true);
	Sprite s_map, s_playbutton, s_cursor, s_cursormiddle, s_fullscreen, s_easy, s_medium, s_hard;
	s_fullscreen.setTexture(fullscreen);
	s_easy.setTexture(difficulty);
	s_easy.setTextureRect(IntRect(0, 0, 96, 34));
	s_easy.setPosition(460, 440);
	s_medium.setTexture(difficulty);
	s_medium.setTextureRect(IntRect(96, 0, 148, 35));
	s_medium.setPosition(560, 440);
	s_hard.setTexture(difficulty);
	s_hard.setTextureRect(IntRect(244, 0, 98, 35));
	s_hard.setPosition(720, 440);
	s_fullscreen.setTextureRect(IntRect(0, 0, 50, 52));
	s_fullscreen.setPosition(1200, 32);
	s_map.setTexture(map);
	s_playbutton.setTexture(playbutton);
	s_cursor.setTexture(cursor);
	s_cursor.setTextureRect(IntRect(0, 0, 68, 68));
	s_cursor.setOrigin(34, 34);
	s_cursormiddle.setTexture(cursormiddle);
	s_cursormiddle.setTextureRect(IntRect(0, 0, 36, 36));
	s_cursormiddle.setOrigin(18, 18);
	s_playbutton.setOrigin(125, 100);
	s_playbutton.setPosition(640, 340);
	s_playbutton.setTextureRect(IntRect(0, 0, 250, 200));
	Font font;
	font.loadFromFile("CGFont.ttf");
	Text text("", font, 20);
	Text text2("", font, 100);
	Text text3("", font, 60);
	Text text4("", font, 60);
	Text menut("", font, 20);
	text.setFillColor(Color::Cyan);
	text2.setFillColor(Color::Cyan);
	text3.setFillColor(Color::Cyan);
	text4.setFillColor(Color::Cyan);
	menut.setFillColor(Color::Cyan);
	text2.setPosition(620, 100);
	//////////////////////////////////////////////////////////////////////////////

	std::list<Bubble*> bubbles;// список объектов класса шар
	std::list<Bubble*>::iterator it;// итератор1
	std::list<Bubble*>::iterator it2;// итератор2
	Expirience EXP;// Объект класса EXP

	float etime = 0;//Переменная для лучшего времени(Easy)
	float mtime = 0;//Переменная для лучшего времени(Medium)
	float htime = 0;//Переменная для лучшего времени(Hard)
	char word = '#';
	std::ifstream ftake("records.bin");
	ftake >> etime;//берем лучшее время из файла(сэйва) для сложности Easy;
	ftake >> word;
	ftake >> mtime;//берем лучшее время из файла(сэйва) для сложности Medium;
	ftake >> word;
	ftake >> htime;//берем лучшее время из файла(сэйва) для сложности Hard;
	ftake.close();
	bool menu = true;//переменная для запуска меню
	bool game = false;//для запуска игры
	bool spawn = false;//для спавна шаров
	bool zoom = false;//для увеличения/уменьшения курсора
	bool FS = false;//для включения/выключения фулскрина
	bool diff = false;// для сложностей
	float difftime = 0.5;//скорость раздвоения шаров
	int difficult = 0;//сложность(1-Easy,2-Medium,3-Hard)
	int bufcount = 0;
	int maxcount = 0;
	float rotate = 0;//переменная хранящая угол поворота курсора
	bool esc = false;
	while (window.isOpen())//окно для игры
	{
		float time = clock.getElapsedTime().asMicroseconds();//Время в микросекундах за один проход цикла
		float gtime = clock.getElapsedTime().asSeconds();//Время в секундах за один проход цикла
		clock.restart();//Рестарт времени
		time = time / 3000;//Делим время, чтобы уменьшить скорость игры
		if (menu)//Меню игры
		{
			window.setMouseCursorVisible(true);//Включает курсор
			Vector2i pixelPos = Mouse::getPosition(window); // переменная хранящая координаты мыши относительно окна
			Vector2f pos = window.mapPixelToCoords(pixelPos);


			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)//Если нажать на крестик справа сверху на окне, то игра закроется!
					window.close();
				if (event.type == Event::KeyPressed)//Клавиша Escape Также закрывает игру(в меню)
					if (event.key.code == Keyboard::Escape)
						window.close();

				if (s_playbutton.getGlobalBounds().contains(pos.x, pos.y))//если встречаем курсором кнопку PLAY, то кнопка подсвечивается
				{
					s_playbutton.setTextureRect(IntRect(0, 200, 250, 200));
				}
				else//если нет, то оставляем как было
				{
					s_playbutton.setTextureRect(IntRect(0, 0, 250, 200));
				}
				if (s_easy.getGlobalBounds().contains(pos.x, pos.y))//Наводимся на кнопку Easy, то она подсвечивается и появляется лучшее время
				{//														Также и со всеми остальными кнопками сложностей
					s_easy.setTextureRect(IntRect(0, 34, 95, 40));
					menut.setPosition(430, 480);
					std::ostringstream e;    
					e << etime;
					menut.setString("Your time: " + e.str() + " sec.");
				}
				else
				{
					s_easy.setTextureRect(IntRect(0, 0, 96, 34));
				}
				if (s_medium.getGlobalBounds().contains(pos.x, pos.y))
				{
					s_medium.setTextureRect(IntRect(96, 35, 145, 40));
					menut.setPosition(550, 480);
					std::ostringstream e;    
					e << mtime;
					menut.setString("Your time: " + e.str() + " sec.");
				}
				else
				{
					s_medium.setTextureRect(IntRect(96, 0, 148, 35));
				}
				if (s_hard.getGlobalBounds().contains(pos.x, pos.y))
				{
					s_hard.setTextureRect(IntRect(244, 35, 96, 40));
					menut.setPosition(690, 480);
					std::ostringstream e;    
					e << htime;
					menut.setString("Your time: " + e.str() + " sec.");
				}
				else
				{
					s_hard.setTextureRect(IntRect(244, 0, 98, 35));
				}
				if (s_fullscreen.getGlobalBounds().contains(pos.x, pos.y))//Прорисовка кнопки Фуллскрина
				{
					if (FS == false)
					{
						s_fullscreen.setTextureRect(IntRect(50, 0, 50, 52));
					}
					else if (FS == true)
					{
						s_fullscreen.setTextureRect(IntRect(50, 52, 50, 52));
					}
				}
				else
				{
					if (FS == false)
					{
						s_fullscreen.setTextureRect(IntRect(0, 0, 50, 52));
					}
					else if (FS == true)
					{
						s_fullscreen.setTextureRect(IntRect(0, 52, 50, 52));
					}
				}
				if (event.type == Event::MouseButtonPressed)//по нажатю ЛКМ на кнопку PLAY появляются сложности
					if (event.key.code == Mouse::Left)
					{
						if (s_playbutton.getGlobalBounds().contains(pos.x, pos.y))
						{
							diff = !diff;
						}
						if (s_easy.getGlobalBounds().contains(pos.x, pos.y) && diff)
						{
							difftime = 0.5;
							menu = false;
							game = true;
							spawn = true;
							diff = false;
							difficult = 1;
							esc = false;
						}
						if (s_medium.getGlobalBounds().contains(pos.x, pos.y) && diff)
						{
							difftime = 0.3;
							menu = false;
							game = true;
							spawn = true;
							diff = false;
							difficult = 2;
							esc = false;
						}
						if (s_hard.getGlobalBounds().contains(pos.x, pos.y) && diff)
						{
							difftime = 0.2;
							menu = false;
							game = true;
							spawn = true;
							diff = false;
							difficult = 3;
							esc = false;
						}
						if (s_fullscreen.getGlobalBounds().contains(pos.x, pos.y))
						{
							if (FS == false)
								window.create(VideoMode(1280, 720), "Bubble Crasher!", Style::Fullscreen);
							else
								window.create(VideoMode(1280, 720), "Bubble Crasher!");
							FS = !FS;
						}
					}
			}
			window.clear();//Очистка окна
			//Далее отрисовка элементов
			window.draw(s_map);
			window.draw(s_playbutton);
			if (diff == true)
			{
				window.draw(s_easy);
				window.draw(s_medium);
				window.draw(s_hard);
			}
			if (s_hard.getGlobalBounds().contains(pos.x, pos.y) || s_easy.getGlobalBounds().contains(pos.x, pos.y) || s_medium.getGlobalBounds().contains(pos.x, pos.y))
			{
				if (diff)
					window.draw(menut);
			}
			window.draw(s_fullscreen);
			window.display();
		}
		if (game)
		{
			EXP.GameTimer(gtime);
			int bubblecount = 0;
			bool cankill = true;
			if (spawn)
			{
				text.setPosition(20, 20);//задаем позицию текста, отступая от центра камеры
				window.setMouseCursorVisible(false);//выключаем курсор windows
				cankill = false;
				EXP.afrmt = true;
				//Старт игры, прорисовка таймера спавна шаров, спавн шаров.
				if (EXP.gametime > 3.3)
				{
					spawn = false;
					EXP.gametime = 0;
				}
				if (EXP.gametime >= 0.2)
				{
					text2.setString("3");
					text2.setPosition(620, 100);
				}
				if (EXP.gametime >= 1)
				{
					text2.setString("2");
					text2.setPosition(620, 100);
				}
				if (EXP.gametime >= 2)
				{
					text2.setString("1");
					text2.setPosition(620, 100);
				}
				if (EXP.gametime >= 3)
				{
					text2.setString("Go!");
					text2.setPosition(580, 100);
				}
				else if (EXP.gametime >= 0.6 && bufcount == 0)
				{
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// заносим в список шары
				}
				else if (EXP.gametime >= 1.2 && bufcount == 1)
				{
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// заносим в список шары
				}
				else if (EXP.gametime >= 1.8 && bufcount == 2)
				{
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// заносим в список шары
				}
				else if (EXP.gametime >= 2.4 && bufcount == 3)
				{
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// заносим в список шары
				}
				else if (EXP.gametime >= 2.9 && bufcount == 4)
				{
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// заносим в список шары
				}
			}
			if (EXP.gametime > 3.2)
			{
				text2.setString("");
			}
			///////////////////////////////////////////////////////////////
			Vector2i pixelPos = Mouse::getPosition(window); // переменная хранящая координаты мыши относительно окна
			Vector2f pos = window.mapPixelToCoords(pixelPos);
			s_cursor.setPosition(pos.x, pos.y);//Ставим игровой курсор на место курсора windows
			s_cursormiddle.setPosition(pos.x, pos.y);//
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)//Если нажали на закрытие программы(в оконном режима справа сверху), то программа закроется.
					window.close();
				if (event.type == Event::KeyPressed)//Если нажали Escape выход в главное меню
					if (event.key.code == Keyboard::Escape)
					{
						for (it = bubbles.begin(); it != bubbles.end(); it++)
						{
							(*it)->life = false;
							(*it)->update(time, gtime);
						}
						game = false;
						menu = true;
						esc = true;
					}
				if (event.type == Event::MouseButtonPressed)//Если нажали ЛКМ, то засчитываем попадане/промах по шару, и соотв. лопаем шар или нет. 
				{											//Также уменьшаем игровой курсор, для динамичности происходящего.
					if (event.key.code == Mouse::Left)
					{
						zoom = true;
						if (cankill)
						{
							bool miss = true;
							for (it = bubbles.begin(); it != bubbles.end(); it++)
							{
								if ((*it)->sprite.getGlobalBounds().contains(pos.x, pos.y))
								{
									(*it)->life = false;
									EXP.BKilled();
									miss = false;
								}

							}
							if (miss == true && bufcount != 0)
								EXP.BMissed();
						}
					}
				}
				if (event.type == Event::MouseButtonReleased)//Ставим дефолтный размер курсору.
				{
					if (event.key.code == Mouse::Left)
					{
						zoom = false;
					}
				}
			}
			for (it = bubbles.begin(); it != bubbles.end(); it++)//подсчет шаров
			{
				bubblecount++;
			}
			if (bubblecount > maxcount)//Ставим максимальное количество шаров, которых было в этиой игре
			{
				maxcount = bubblecount;
			}
			bufcount = bubblecount;
			for (it = bubbles.begin(); it != bubbles.end();)
			{
				(*it)->update(time, gtime);//обновляем каждый шар
				for (it2 = bubbles.begin(); it2 != bubbles.end(); it2++)//проверка столкновений
				{
					if (it != it2)
						(*it)->Collision(&(*it2)->bcord, &(*it2)->direct, &(*it2)->life);
				}
				if ((*it)->life == false)//если шар лопнули
				{
					/////////////////////   АНИМАЦИЯ СМЕРТИ ШАРА   //////////////////////
					(*it)->CurrentFrame += 0.07*time;
					if ((*it)->CurrentFrame > 9)
					{
						it = bubbles.erase(it);
						break;
					}
					else
					{
						(*it)->sprite.setTextureRect(IntRect(0, 100 * int((*it)->CurrentFrame), 100, 100));
					}
					/////////////////////////////////////////////////////////////////////
				}
				else
				{
					if (bufcount < maxb && spawn == false)
					{
						if ((*it)->dublTime > float(maxcount*difftime))//размножение шара через секунду
						{
							bubbles.push_back(new Bubble("images/bubblePack.png", (*it)->bcord.x, (*it)->bcord.y, 100, 100));
							bufcount++;
							(*it)->dublTime = 0;
						}
					}
					else//если шаров больше 40, о перестаем их спавнить
					{
						(*it)->dublTime = 0;
					}
				}
				it++;
			}
			if (esc)
			{
				for (int i = 0; i < bubblecount; i++)
				{
					for (it = bubbles.begin(); it != bubbles.end();)
					{
						it = bubbles.erase(it);
						break;
					}
				}
			}

			std::ostringstream OStrX;    // объявили переменную
			OStrX << EXP.gametime;		//занесли в нее число очков, то есть формируем строку
			text.setString("Time: " + OStrX.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()

			 //Динамический курсор в игре
			Vector2f scale;
			scale = s_cursor.getScale();
			if (zoom == true && scale.x > 0.9f && scale.y > 0.9f)
			{
				s_cursor.scale(Vector2f(0.8, 0.8));
			}
			else if (zoom == false && scale.x < 1 && scale.y < 1)
			{
				s_cursor.scale(Vector2f(1.001, 1.001));
			}
			s_cursor.setRotation(rotate);
			rotate = rotate + time / 7;
			////////////////////////////////////



			window.clear();//Очистка экрана
			window.draw(s_map);//Прорисовка фона
			for (it = bubbles.begin(); it != bubbles.end(); it++)//прорисовка шаров
			{
				window.draw((*it)->sprite);
			}
			if (bubblecount == 0 && EXP.gametime > 1)//Если шаров не осталось, то выводим окно завершения игры
			{
				std::ostringstream OStrY, OStrZ;
				OStrY << EXP.Accuracy();
				text3.setString("Accuracy: " + OStrY.str() + "%");
				text3.setPosition(300, 420);
				EXP.afrmt = false;
				text.setPosition(300, 360);
				text.setCharacterSize(60);
				text.setString("Your time: " + OStrX.str() + " sec.");
				text4.setPosition(300, 480);
				text4.setCharacterSize(60);
				//В зависимости от сложности выводим нужное время.
				if (difficult == 1)
				{
					OStrZ << etime;
				}
				if (difficult == 2)
				{
					OStrZ << mtime;
				}
				if (difficult == 3)
				{
					OStrZ << htime;
				}
				text4.setString("Best time: " + OStrZ.str() + " sec.");
				if (event.type == Event::MouseButtonPressed)//Если нажата ЛКМ, выходим в меню
				{
					if (event.key.code == Mouse::Left)
					{
						text.setCharacterSize(20);
						game = false;
						menu = true;
					}
				}
				window.draw(text3);
				window.draw(text4);
			}
			if (menu)//когда перешли в меню
			{
				if (esc == false)//если не была нажата клавиша Escape, то запоминаем результат, если он лучше существующего.
				{
					if (difficult == 1)
					{
						if (EXP.gametime < etime || etime == 0)
						{
							etime = EXP.gametime;
						}
					}
					if (difficult == 2)
					{
						if (EXP.gametime < mtime || mtime == 0)
						{
							mtime = EXP.gametime;
						}
					}
					if (difficult == 3)
					{
						if (EXP.gametime < htime || htime == 0)
						{
							htime = EXP.gametime;
						}
					}
					std::ofstream of("records.bin");
					of.close();
					of.open("records.bin");
					of << etime;
					of << word;
					of << mtime;
					of << word;
					of << htime;
					of.close();
					EXP.Reset();
				}
			}
			//прорисовка остальных элементов.
			if (!spawn)
				window.draw(text);
			window.draw(text2);
			window.draw(s_cursor);
			window.draw(s_cursormiddle);
			window.display();
		}
	}
}
