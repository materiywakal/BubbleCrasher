#include <SFML/Graphics.hpp>
#include "Bubble.h"
#include "EXP.h"
#include <list>
#include <vector>
#include <sstream>
#include "fstream"
using namespace sf;
static int maxb = 40;//������������ ���������� ����� �� �����
void Game(RenderWindow &window)//��� �������-���
{
	Clock clock;

	/////////////////////////�������� ��������� � ��.////////////////////////////
	Texture map, playbutton, cursor, cursormiddle, fullscreen, difficulty;
	map.loadFromFile("images/background.png");// �������� ����
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

	std::list<Bubble*> bubbles;// ������ �������� ������ ���
	std::list<Bubble*>::iterator it;// ��������1
	std::list<Bubble*>::iterator it2;// ��������2
	Expirience EXP;// ������ ������ EXP

	float etime = 0;//���������� ��� ������� �������(Easy)
	float mtime = 0;//���������� ��� ������� �������(Medium)
	float htime = 0;//���������� ��� ������� �������(Hard)
	char word = '#';
	std::ifstream ftake("records.bin");
	ftake >> etime;//����� ������ ����� �� �����(�����) ��� ��������� Easy;
	ftake >> word;
	ftake >> mtime;//����� ������ ����� �� �����(�����) ��� ��������� Medium;
	ftake >> word;
	ftake >> htime;//����� ������ ����� �� �����(�����) ��� ��������� Hard;
	ftake.close();
	bool menu = true;//���������� ��� ������� ����
	bool game = false;//��� ������� ����
	bool spawn = false;//��� ������ �����
	bool zoom = false;//��� ����������/���������� �������
	bool FS = false;//��� ���������/���������� ���������
	bool diff = false;// ��� ����������
	float difftime = 0.5;//�������� ���������� �����
	int difficult = 0;//���������(1-Easy,2-Medium,3-Hard)
	int bufcount = 0;
	int maxcount = 0;
	float rotate = 0;//���������� �������� ���� �������� �������
	bool esc = false;
	while (window.isOpen())//���� ��� ����
	{
		float time = clock.getElapsedTime().asMicroseconds();//����� � ������������� �� ���� ������ �����
		float gtime = clock.getElapsedTime().asSeconds();//����� � �������� �� ���� ������ �����
		clock.restart();//������� �������
		time = time / 3000;//����� �����, ����� ��������� �������� ����
		if (menu)//���� ����
		{
			window.setMouseCursorVisible(true);//�������� ������
			Vector2i pixelPos = Mouse::getPosition(window); // ���������� �������� ���������� ���� ������������ ����
			Vector2f pos = window.mapPixelToCoords(pixelPos);


			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)//���� ������ �� ������� ������ ������ �� ����, �� ���� ���������!
					window.close();
				if (event.type == Event::KeyPressed)//������� Escape ����� ��������� ����(� ����)
					if (event.key.code == Keyboard::Escape)
						window.close();

				if (s_playbutton.getGlobalBounds().contains(pos.x, pos.y))//���� ��������� �������� ������ PLAY, �� ������ ��������������
				{
					s_playbutton.setTextureRect(IntRect(0, 200, 250, 200));
				}
				else//���� ���, �� ��������� ��� ����
				{
					s_playbutton.setTextureRect(IntRect(0, 0, 250, 200));
				}
				if (s_easy.getGlobalBounds().contains(pos.x, pos.y))//��������� �� ������ Easy, �� ��� �������������� � ���������� ������ �����
				{//														����� � �� ����� ���������� �������� ����������
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
				if (s_fullscreen.getGlobalBounds().contains(pos.x, pos.y))//���������� ������ ����������
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
				if (event.type == Event::MouseButtonPressed)//�� ������ ��� �� ������ PLAY ���������� ���������
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
			window.clear();//������� ����
			//����� ��������� ���������
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
				text.setPosition(20, 20);//������ ������� ������, �������� �� ������ ������
				window.setMouseCursorVisible(false);//��������� ������ windows
				cankill = false;
				EXP.afrmt = true;
				//����� ����, ���������� ������� ������ �����, ����� �����.
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
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// ������� � ������ ����
				}
				else if (EXP.gametime >= 1.2 && bufcount == 1)
				{
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// ������� � ������ ����
				}
				else if (EXP.gametime >= 1.8 && bufcount == 2)
				{
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// ������� � ������ ����
				}
				else if (EXP.gametime >= 2.4 && bufcount == 3)
				{
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// ������� � ������ ����
				}
				else if (EXP.gametime >= 2.9 && bufcount == 4)
				{
					bubbles.push_back(new Bubble("images/bubblePack.png", 640, 360, 100, 100));// ������� � ������ ����
				}
			}
			if (EXP.gametime > 3.2)
			{
				text2.setString("");
			}
			///////////////////////////////////////////////////////////////
			Vector2i pixelPos = Mouse::getPosition(window); // ���������� �������� ���������� ���� ������������ ����
			Vector2f pos = window.mapPixelToCoords(pixelPos);
			s_cursor.setPosition(pos.x, pos.y);//������ ������� ������ �� ����� ������� windows
			s_cursormiddle.setPosition(pos.x, pos.y);//
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)//���� ������ �� �������� ���������(� ������� ������ ������ ������), �� ��������� ���������.
					window.close();
				if (event.type == Event::KeyPressed)//���� ������ Escape ����� � ������� ����
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
				if (event.type == Event::MouseButtonPressed)//���� ������ ���, �� ����������� ��������/������ �� ����, � �����. ������ ��� ��� ���. 
				{											//����� ��������� ������� ������, ��� ������������ �������������.
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
				if (event.type == Event::MouseButtonReleased)//������ ��������� ������ �������.
				{
					if (event.key.code == Mouse::Left)
					{
						zoom = false;
					}
				}
			}
			for (it = bubbles.begin(); it != bubbles.end(); it++)//������� �����
			{
				bubblecount++;
			}
			if (bubblecount > maxcount)//������ ������������ ���������� �����, ������� ���� � ����� ����
			{
				maxcount = bubblecount;
			}
			bufcount = bubblecount;
			for (it = bubbles.begin(); it != bubbles.end();)
			{
				(*it)->update(time, gtime);//��������� ������ ���
				for (it2 = bubbles.begin(); it2 != bubbles.end(); it2++)//�������� ������������
				{
					if (it != it2)
						(*it)->Collision(&(*it2)->bcord, &(*it2)->direct, &(*it2)->life);
				}
				if ((*it)->life == false)//���� ��� �������
				{
					/////////////////////   �������� ������ ����   //////////////////////
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
						if ((*it)->dublTime > float(maxcount*difftime))//����������� ���� ����� �������
						{
							bubbles.push_back(new Bubble("images/bubblePack.png", (*it)->bcord.x, (*it)->bcord.y, 100, 100));
							bufcount++;
							(*it)->dublTime = 0;
						}
					}
					else//���� ����� ������ 40, � ��������� �� ��������
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

			std::ostringstream OStrX;    // �������� ����������
			OStrX << EXP.gametime;		//������� � ��� ����� �����, �� ���� ��������� ������
			text.setString("Time: " + OStrX.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str()

			 //������������ ������ � ����
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



			window.clear();//������� ������
			window.draw(s_map);//���������� ����
			for (it = bubbles.begin(); it != bubbles.end(); it++)//���������� �����
			{
				window.draw((*it)->sprite);
			}
			if (bubblecount == 0 && EXP.gametime > 1)//���� ����� �� ��������, �� ������� ���� ���������� ����
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
				//� ����������� �� ��������� ������� ������ �����.
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
				if (event.type == Event::MouseButtonPressed)//���� ������ ���, ������� � ����
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
			if (menu)//����� ������� � ����
			{
				if (esc == false)//���� �� ���� ������ ������� Escape, �� ���������� ���������, ���� �� ����� �������������.
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
			//���������� ��������� ���������.
			if (!spawn)
				window.draw(text);
			window.draw(text2);
			window.draw(s_cursor);
			window.draw(s_cursormiddle);
			window.display();
		}
	}
}
