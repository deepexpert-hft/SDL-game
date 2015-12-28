#include "Main.h"
#include "Timer.h"
#include "Const.h"
#include "Object.h"

void game();								//游戏主函数
int istouch(SDL_Rect A,SDL_Rect B);			//碰撞检测

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)//初始化SDL
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);		//频率/格式/混音/采样

	Main_Windows = SDL_CreateWindow(Windows_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Windows_Width, Windows_Height, SDL_WINDOW_SHOWN);

	if (Main_Windows == nullptr){
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		return 1;
	}

	Main_Renderer = SDL_CreateRenderer(Main_Windows, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//创建了一个页面,这里叫渲染器

	if (Main_Renderer == nullptr){
		cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}

	if (TTF_Init() == -1) {
		cout << "TTF init Error!" << endl;
		return 1;
	}

	Main_Font = TTF_OpenFont("msyhbd.ttf", 18);

	int While_Quit = 0;
	int Arrow_id = 0;
	SDL_Event event;

	SDL_Texture *Help = loadTexture("IMG\\help.png",Main_Renderer);					//加载提示图片
	SDL_Texture *BG_PIC = loadTexture("IMG\\background2.png", Main_Renderer);		//加载背景图片
	SDL_Texture *point_PIC = loadTexture("IMG\\12.png", Main_Renderer);				//加载选择图片

	Mix_Music *BGSound = Mix_LoadMUS("MUSIC\\BGMusic.wav");
	BackGround bg1(BG_PIC), bg2(BG_PIC);
	bg2.setxy(0, 768);
	Timer fps;
	SDL_ShowCursor(0);															//隐藏光标
	Mix_PlayMusic(BGSound, -1);													//播放背景音乐

	while (!While_Quit)
	{
		fps.start();
		SDL_RenderClear(Main_Renderer);	
		bg1.Show();
		bg2.Show();
		SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "开始游戏", 200, 400, 255, 255, 0);
		SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "关于", 200, 440, 255, 255, 0);
		SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "退出", 200, 480, 255, 255, 0);
		ApplySurface(10, 100, Help, Main_Renderer);
		ApplySurface(150, 395 + Arrow_id * 40, point_PIC, Main_Renderer);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				While_Quit = 1;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					While_Quit = 1;
				else if (event.key.keysym.sym == SDLK_w)
				{
					if (Arrow_id > 0)
						Arrow_id--;
					else
						Arrow_id = 2;
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					if (Arrow_id < 2)
						Arrow_id++;
					else
						Arrow_id = 0;
				}
				else if (event.key.keysym.sym == SDLK_RETURN)
				{
					if (Arrow_id == 0)
					{
						game();											//开始游戏
					}
					else if (Arrow_id == 1)
					{
						int whilequit = 0;
						while (!whilequit)
						{
							while (SDL_PollEvent(&event))
							{
								if (event.type == SDL_KEYDOWN)
								{
									whilequit = 1;
								}
								if (event.type == SDL_QUIT)
								{
									whilequit = 1;
								}
							}
							bg1.Show();
							bg2.Show();
							SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "游戏名:飞机大战", 180, 120, 255, 255, 0);
							SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "操作:上(W)下(S)左(A)右(D),1释放大招", 115, 160, 255, 255, 0);
							SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "飞机的血量消耗完游戏结束", 150, 200, 255, 255, 0);
							SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "逃跑的敌人超过30个游戏结束", 145, 240, 255, 255, 0);
							SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "图片来自网络", 190, 280, 255, 255, 0);
							SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "图形库:SDL2.0", 190, 320, 255, 255, 0);
							SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "编译平台:VS2013", 180, 360, 255, 255, 0);
							SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "鸣谢:百度", 200, 400, 255, 255, 0);
							SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "按  任  意  键  返  回", 170, 440, 255, 255, 0);
							SDL_RenderPresent(Main_Renderer);
						}
					}
					else if (Arrow_id == 2)
					{
						While_Quit = 1;
					}
				}
			}
			if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)				//捕获帧率
			{
				SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
			}
		}
		SDL_RenderPresent(Main_Renderer);
	}

	SDL_DestroyTexture(Help);
	SDL_DestroyTexture(BG_PIC);
	SDL_DestroyTexture(point_PIC);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	return 0;
}

void game()
{
	SDL_Texture *BG_PIC = loadTexture("IMG\\img_bg.jpg", Main_Renderer);						//加载背景
	SDL_Texture *MYPLANE_PIC = loadTexture("IMG\\img_myplane.png", Main_Renderer);				//加载飞机
	SDL_Texture *BULLET_PIC = loadTexture("IMG\\img_bullet.png", Main_Renderer);				//加载子弹
	SDL_Texture *ENEMY_PLANE_PIC = loadTexture("IMG\\img_plane_enemy.png", Main_Renderer);		//加载敌机
	SDL_Texture *Property0 = loadTexture("IMG\\property0.png", Main_Renderer);					//加载补给品0
	SDL_Texture *Property1 = loadTexture("IMG\\property1.png", Main_Renderer);					//加载补给品1
	SDL_Texture *Wave_PIC = loadTexture("IMG\\wave.png", Main_Renderer);						//加载大招
	SDL_Texture *GameOver = loadTexture("IMG\\gameover.png", Main_Renderer);					//加载游戏结束图片

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);							//频率/格式/混音/采样

	Mix_Chunk *Sound_Bullet = Mix_LoadWAV("MUSIC\\shoot.wav");									
	Mix_Chunk *Sound_kill = Mix_LoadWAV("MUSIC\\kill.wav");
	Mix_Chunk *Sound_Gover = Mix_LoadWAV("MUSIC\\GameOver.wav");
	Mix_Chunk *Sound_wave = Mix_LoadWAV("MUSIC\\wave.WAV");
	Mix_Chunk *Sound_hurt = Mix_LoadWAV("MUSIC\\boom.WAV");

	char tempstring1[30],tempstring2[30];
	Timer fps;																					//控制游戏帧率
	Timer Bullet_time;																			//控制子弹发射频率
	Timer Enemy_time;																			//控制敌机出现频率
	Timer Property_time;																		//控制补给品出现频率

	SDL_Event event;																			//事件
	int While_Quit = 0, WhileGameOver = 0;														
	BackGround bg1(BG_PIC), bg2(BG_PIC);														//背景对象
	bg2.setxy(0, 768);

	Plane Myplane(MYPLANE_PIC);																	//飞机对象

	Bullet *Bullets[TOTAL_Plane_Bullets];
	int Bullets_num[TOTAL_Plane_Bullets] = {0};													//我方飞机的弹匣

	Ship *Ships[TOTAL_Ships_NUMBER];
	int Ships_num[TOTAL_Ships_NUMBER] = { 0 };													//敌机数量

	Property *pro;																				//补给品对象
	int pro_num = 0;

	Wave *wave;																					//大招对象
	int wave_num = 0 ;

	int yourscore = 0;																			//得分
	int not_eliminate = 0;																		//逃跑的敌机数量

	Bullet_time.start();																		//计时器开启
	Enemy_time.start();
	Property_time.start();

	while (!While_Quit)
	{
		fps.start();
		SDL_RenderClear(Main_Renderer);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				While_Quit = 1;
			}
			else if (event.type == SDL_KEYDOWN&&WhileGameOver == 0)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					While_Quit = 1;
				}
			}
			else if (event.type == SDL_KEYDOWN&&WhileGameOver==1)
			{
				While_Quit = 1;
			}
		}
		bg1.Show();
		bg2.Show();
		if (WhileGameOver == 0)
		{
			sprintf(tempstring1, "你的分数:%d", yourscore);
			sprintf(tempstring2, "逃跑的敌机:%d", not_eliminate);
			Myplane.Show();
			Myplane.handle_events(&event);
			SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, tempstring1, 0, 500, 255, 255, 0);
			SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, tempstring2, 0, 520, 255, 255, 0);
			if (pro_num == 0)
			{
				if (Property_time.get_ticks() > 30000)												//30s出现一次补给品
				{
					int type = rand() % 2;															//随机产生补给品类型
					int x = rand() % (Windows_Width / 2);											//随机坐标
					int y = rand() % 100;
					if (type == 0)
					{
						pro = new Property(Property0, type, x, y);
						pro_num = 1;
					}
					else if (type == 1)
					{
						pro = new Property(Property1, type, x, y);
						pro_num = 1;
					}
					Property_time.start();															//重新计时
				}
			}
			else if (pro_num == 1)
			{
				pro->Show();																		//显示补给品
				pro->Move();
				SDL_Rect A = { Myplane.GetX(), Myplane.GetY(), MY_PLANE_WIDTH, MY_PLANE_HEIGHT };
				SDL_Rect B = { pro->GetX(), pro->GetY(), pro->GetClip().w, pro->GetClip().h };
				if (istouch(A, B))
				{
					pro->MinusHP();
					if (pro->Property_type == 0)
					{
						if (Myplane.HP < 3)
						{
							Myplane.HP++;
						}
					}
					else if (pro->Property_type == 1)
					{
						if (Myplane.wave < 3)
						{
							Myplane.wave++;
						}
					}
				}
				if (pro->is_dead())
				{
					delete pro;																		//删除补给品对象
					pro_num = 0;
				}
			}

			for (int i = 0; i < TOTAL_Plane_Bullets; i++)
			{
				if (Bullets_num[i] == 0)
				{
					if (Bullet_time.get_ticks()> 100)												//每隔100ms装载子弹
					{
						Bullets[i] = new Bullet(BULLET_PIC);
						Bullets[i]->setxy(Myplane.GetX() + MY_PLANE_WIDTH / 2 - BULLET_WIDTH / 2, Myplane.GetY() - BULLET_HEIGHT);
						Bullets_num[i] = 1;
						Bullet_time.start();
					}
				}
				else if (Bullets_num[i] == 1)
				{
					Bullets[i]->Show();
					Bullets[i]->Move();
					if (Bullets[i]->isdead())
					{
						delete Bullets[i];
						Bullets_num[i] = 0;
					}
				}
			}

			for (int i = 0; i < TOTAL_Ships_NUMBER; i++)
			{
				if (Ships_num[i] == 0)
				{
					if (Enemy_time.get_ticks()> 300)												//每隔300ms产生一个敌机
					{
						int x = rand() % (Windows_Width - 70);
						int y = -100 - rand() % 100;
						int type = rand() % 5;														//随机敌机类型
						Ships[i] = new Ship(ENEMY_PLANE_PIC, type, x, y);
						Ships_num[i] = 1;
						Enemy_time.start();
					}
				}
				else if (Ships_num[i] == 1)
				{
					Ships[i]->Show();
					Ships[i]->Move();
					if (Ships[i]->is_dead())
					{
						not_eliminate++;
						if (not_eliminate >= 30)
						{
							While_Quit = 1;
						}
						Ships_num[i] = 0;
						delete Ships[i];
					}
				}
			}

			for (int i = 0; i < TOTAL_Plane_Bullets; i++)
			{
				for (int j = 0; j < TOTAL_Ships_NUMBER; j++)
				{
					if (Ships_num[j] == 1 && Bullets_num[i] == 1)
					{
						SDL_Rect A = { Bullets[i]->GetX(), Bullets[i]->GetY(), Bullets[i]->GetClip().w, Bullets[i]->GetClip().h };
						SDL_Rect B = { Ships[j]->GetX(), Ships[j]->GetY(), Ships[j]->GetClip().w, Ships[j]->GetClip().h };
						if (istouch(A, B))														//子弹与敌机的碰撞检测
						{
							Ships[j]->MinusHP();
							delete Bullets[i];
							Bullets_num[i] = 0;
							if (Ships[j]->is_dead())
							{
								if (Ships[j]->Ship_type == 0)
								{
									yourscore += 24;
								}
								else if (Ships[j]->Ship_type == 1)
								{
									yourscore += 24;
								}
								else if (Ships[j]->Ship_type == 2)
								{
									yourscore += 68;
								}
								else if (Ships[j]->Ship_type == 3)
								{
									yourscore += 78;
								}
								else if (Ships[j]->Ship_type == 4)
								{
									yourscore += 100;
								}
								Mix_PlayChannel(-1, Sound_kill, 0);
								delete Ships[j];
								Ships_num[j] = 0;
							}
						}
					}
				}
			}

			for (int j = 0; j < TOTAL_Ships_NUMBER; j++)
			{
				if (Ships_num[j] == 1)
				{
					SDL_Rect A = { Myplane.GetX(), Myplane.GetY(), MY_PLANE_WIDTH, MY_PLANE_HEIGHT };
					SDL_Rect B = { Ships[j]->GetX(), Ships[j]->GetY(), Ships[j]->GetClip().w, Ships[j]->GetClip().h };
					if (istouch(A, B))															//敌机与我方飞机的碰撞检测
					{
						Myplane.MinusHP();
						Mix_PlayChannel(-1, Sound_hurt, 0);
						Mix_PlayChannel(-1, Sound_kill, 0);
						delete Ships[j];
						Ships_num[j] = 0;
						if (Myplane.isdead())
						{
							WhileGameOver = 1;
						}
					}
				}
			}

			if (wave_num == 0)
			{
				if (SDL_KeyBoardKeyPressed(SDL_SCANCODE_1))										//发大招
				{
					if (Myplane.wave > 0)
					{
						Mix_PlayChannel(-1, Sound_wave, 0);
						wave = new Wave(Wave_PIC);
						wave_num = 1;
						Myplane.wave--;
					}
				}
			}
			else if (wave_num == 1)
			{
				wave->Show();
				wave->Move();
				for (int j = 0; j < TOTAL_Ships_NUMBER; j++)
				{
					if (Ships_num[j] == 1)
					{
						SDL_Rect A = { wave->GetX(), wave->GetY(), wave->GetClip().w, wave->GetClip().h };
						SDL_Rect B = { Ships[j]->GetX(), Ships[j]->GetY(), Ships[j]->GetClip().w, Ships[j]->GetClip().h };
						if (istouch(A, B))														//大招与敌机的碰撞检测
						{
							Mix_PlayChannel(-1, Sound_kill, 0);
							if (Ships[j]->Ship_type == 0)
							{
								yourscore += 24;
							}
							else if (Ships[j]->Ship_type == 1)
							{
								yourscore += 24;
							}
							else if (Ships[j]->Ship_type == 2)
							{
								yourscore += 68;
							}
							else if (Ships[j]->Ship_type == 3)
							{
								yourscore += 78;
							}
							else if (Ships[j]->Ship_type == 4)
							{
								yourscore += 100;
							}
							delete Ships[j];
							Ships_num[j] = 0;
						}
					}
				}
				if (wave->is_dead())
				{
					delete wave;
					wave_num = 0;
				}
			}
		}
		else if (WhileGameOver == 1)					//游戏结束
		{
			Mix_PlayChannel(-1, Sound_Gover, 0);
			ApplySurface(10, 100, GameOver, Main_Renderer);
			SDL_ShowTTFtoRenderer(Main_Font, Main_Renderer, "按任意键返回主界面", 180, 400, 255, 255, 0);
		}

		SDL_RenderPresent(Main_Renderer);
		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)				//捕获帧率
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}
	Mix_HaltChannel(-1);
	SDL_DestroyTexture(BG_PIC);
	SDL_DestroyTexture(MYPLANE_PIC);
	SDL_DestroyTexture(BULLET_PIC);
	SDL_DestroyTexture(ENEMY_PLANE_PIC);
	SDL_DestroyTexture(Property0);
	SDL_DestroyTexture(Property1);
	SDL_DestroyTexture(Wave_PIC);
	SDL_DestroyTexture(GameOver);
	Mix_CloseAudio();
}

int istouch(SDL_Rect A, SDL_Rect B)													//碰撞检测函数
{
	if (A.x > B.x&&A.x < B.x + B.w&&A.y>B.y&&A.y < B.y + B.h)
		return 1;
	if (B.x > A.x&&B.x < A.x + A.w&&B.y > A.y&&B.y < A.y + A.h)
		return 2;
	return 0;
}