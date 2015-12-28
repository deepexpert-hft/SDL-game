#ifndef CONST_H
#define CONST_H

typedef enum eGameStatus { PreStart, Running, Pause, Over, Quit } eGameStatus;

const char Windows_Title[] = "Plane Game";	//窗口的标题
const int Windows_Width = 512;				//窗口宽度
const int Windows_Height = 650;				//窗口高度

const int MY_PLANE_WIDTH = 62;				//飞机宽度
const int MY_PLANE_HEIGHT = 46;				//飞机高度

const int BULLET_WIDTH = 15;				//子弹宽度
const int BULLET_HEIGHT = 20;				//子弹高度

const int Enemy_PLANE_WIDTH_1 = 61;
const int Enemy_PLANE_HEIGHT_1 = 44;

const int Enemy_PLANE_WIDTH_2 = 60;
const int Enemy_PLANE_HEIGHT_2 = 45;

const int Enemy_PLANE_WIDTH_3 = 66;
const int Enemy_PLANE_HEIGHT_3 = 50;


const int FRAMES_PER_SECOND = 30;			//游戏帧率

const int TOTAL_Plane_Bullets = 20;			//我方飞机弹夹
const int TOTAL_Ships_NUMBER  = 15;			//敌机数量

#endif