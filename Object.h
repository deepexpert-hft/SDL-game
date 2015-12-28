#ifndef OBJECT_H
#define OBJECT_H

#include "Main.h"
#include "Const.h"

class Object								//����һ������
{
protected:
	SDL_Rect *objClip = nullptr;
	SDL_Rect *objRect = nullptr;
	SDL_Texture *objectImage = nullptr;
	int x, y;								//����
	int speed;								//�ƶ��ٶ�
public:
	int HP;									//Ѫ��
	Object(SDL_Texture *Image)				//�����캯��
	{
		objectImage = Image;
		objClip = new SDL_Rect;
		x = 0;
		y = 0;
		speed = 0;
		HP = 1;
	};
	~Object()
	{
		delete objClip;
	};
	void setclip(int x,int y,int w,int h)	//�и����
	{
		objClip->x = x;
		objClip->y = y;
		objClip->w = w;
		objClip->h = h;
	};
	void setxy(int xx, int yy)				//��������
	{
		x = xx;
		y = yy;
	};
	SDL_Rect GetClip()						//��þ���
	{
		return *objClip;
	};
	int GetX()								//��ú�����
	{
		return x;
	}
	int GetY()								//���������
	{
		return y;
	}
	void Show()								//��ʾ����
	{
		;
	};
	void MinusHP()							//Ѫ����1
	{
		HP = HP - 1;
	}
	void AddHP()							//Ѫ����1
	{
		HP = HP + 1;
	}
	void Move()								//�˶�����
	{
		;
	};	
	void handle_events(SDL_Event *event)	//�����¼�
	{
		;
	};
};

class BackGround :public Object				//������
{
public:
	BackGround(SDL_Texture *Image) :Object(Image)
	{ 
		speed = 2; 
		setclip(0, 0, 512, 768);
	};
	void Move()
	{
		y -= speed;
		if (y <= -768)
		{
			y = 768;
		}
	};
	void Show()
	{
		ApplySurface(x, y, objectImage, Main_Renderer, objClip);
		Move();
	};
};

class Plane :public Object					//�ɻ���
{
public:
	int wave;
	Plane(SDL_Texture* Image) :Object(Image) 
	{ 
		x = (Windows_Width - MY_PLANE_WIDTH) / 2;
		y = Windows_Height - MY_PLANE_HEIGHT;
		HP = 3;
		speed = 10;
		wave = 3;
		setclip(132, 150, MY_PLANE_WIDTH, MY_PLANE_HEIGHT);
	};
	~Plane()
	{
		;
	};
	void handle_events(SDL_Event *event)
	{
		//�������ҵ��ƶ�
		if (SDL_KeyBoardKeyPressed(SDL_SCANCODE_A))
		{
			x -= speed;
			if (x < 0)
			{
				x = 0;
			}
		}
		else if (SDL_KeyBoardKeyPressed(SDL_SCANCODE_D))
		{
			x += speed;
			if (x > Windows_Width - MY_PLANE_WIDTH)
			{
				x = Windows_Width - MY_PLANE_WIDTH;
			}
		}
		else if (SDL_KeyBoardKeyPressed(SDL_SCANCODE_W))
		{
			y -= speed;
			if (y < 0)
			{
				y = 0;
			}
		}
		else if (SDL_KeyBoardKeyPressed(SDL_SCANCODE_S))
		{
			y += speed;
			if (y > Windows_Height - MY_PLANE_HEIGHT)
			{
				y = Windows_Height - MY_PLANE_HEIGHT;
			}
		}
	};
	bool isdead()
	{
		if (HP <= 0)
		{
			return 1;
		}
		return 0;
	}
	void Show()
	{
		ApplySurface(x, y, objectImage, Main_Renderer, objClip);
		SDL_Texture *heart = loadTexture("IMG\\heart.png", Main_Renderer);
		SDL_Texture *the_wave = loadTexture("IMG\\the_wave.png", Main_Renderer);
		for (int i = 0; i < HP; i++)
		{
			ApplySurface(i*20, 560, heart, Main_Renderer);
		}
		for (int i = 0; i < wave; i++)
		{
			ApplySurface(i *20,580, the_wave, Main_Renderer);
		}
	};
};

class Bullet :public Object							//�ӵ���
{	
public:
	Bullet(SDL_Texture* Image) :Object(Image)
	{
		speed = BULLET_HEIGHT;
		setclip(356, 198, BULLET_WIDTH, BULLET_HEIGHT);
		HP = 1;
	};
	~Bullet()
	{
		;
	};
	void Move()
	{
		y -= speed;
	};
	void Show()
	{
		ApplySurface(x, y, objectImage, Main_Renderer, objClip);
	}
	bool isdead()
	{
		if (HP <= 0 || y < -BULLET_HEIGHT)
		{
			return 1;
		}
		return 0;
	}
};

class Ship :public Object						//�л���
{
public:
	int Ship_type;
	~Ship()
	{
		;
	}
	Ship(SDL_Texture* Image, int type, int x, int y) : Object(Image)
	{
		if (type == 0)
		{
			setclip(94, 278, Enemy_PLANE_WIDTH_1, Enemy_PLANE_HEIGHT_1);
			HP = 2;
			speed = 3;
		}
		else if (type == 1)
		{
			setclip(213, 306, Enemy_PLANE_WIDTH_2, Enemy_PLANE_HEIGHT_2);
			HP = 2;
			speed = 3;
		}
		else if (type == 2)
		{
			setclip(215, 256, Enemy_PLANE_WIDTH_3, Enemy_PLANE_HEIGHT_3);
			HP = 4;
			speed = 2;
		}
		else if (type == 3)
		{
			setclip(214, 200, 80, 58);
			HP = 8;
			speed = 2;
		}
		else if (type == 4)
		{
			setclip(0, 135, 110, 78);
			HP = 10;
			speed = 1;
		}
		Ship_type = type;
		setxy(x, y);
	};
	bool is_dead()
	{
		if (HP <= 0 || y >= Windows_Height)
		{
			return 1;
		}
		return 0;
	};
	void Move()
	{
		y += speed;
	};
	void Show()
	{
		ApplySurface(x, y, objectImage, Main_Renderer, objClip);
	};
};

class Property :public Object					//����Ʒ��
{
public:
	int Property_type;
	Property(SDL_Texture* Image,int type, int x, int y) :Object(Image)
	{
		HP = 1;
		Property_type = type;
		setclip(0, 0, 60, 60);
		speed = 3;
		setxy(x, y);
	};
	bool is_dead()
	{
		if (HP <= 0 || y >= Windows_Height || x >= Windows_Width)
		{
			return 1;
		}
		return 0;
	};
	void Move()
	{
		y += speed;
		x += speed - 1;
	};
	void Show()
	{
		ApplySurface(x, y, objectImage, Main_Renderer, objClip);
	};
};

class Wave :public Object						//������
{
public:
	Wave(SDL_Texture* Image) :Object(Image)
	{
		HP = 1;
		setclip(0, 0, 512, 220);
		speed = 20;
		setxy(0, 650);
	}
	bool is_dead()
	{
		if (HP <= 0 || y <= -220 )
		{
			return 1;
		}
		return 0;
	};
	void Move()
	{
		y -= speed;
	};
	void Show()
	{
		ApplySurface(x, y, objectImage, Main_Renderer, objClip);
	};
};

#endif