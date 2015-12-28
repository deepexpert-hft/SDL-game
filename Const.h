#ifndef CONST_H
#define CONST_H

typedef enum eGameStatus { PreStart, Running, Pause, Over, Quit } eGameStatus;

const char Windows_Title[] = "Plane Game";	//���ڵı���
const int Windows_Width = 512;				//���ڿ��
const int Windows_Height = 650;				//���ڸ߶�

const int MY_PLANE_WIDTH = 62;				//�ɻ����
const int MY_PLANE_HEIGHT = 46;				//�ɻ��߶�

const int BULLET_WIDTH = 15;				//�ӵ����
const int BULLET_HEIGHT = 20;				//�ӵ��߶�

const int Enemy_PLANE_WIDTH_1 = 61;
const int Enemy_PLANE_HEIGHT_1 = 44;

const int Enemy_PLANE_WIDTH_2 = 60;
const int Enemy_PLANE_HEIGHT_2 = 45;

const int Enemy_PLANE_WIDTH_3 = 66;
const int Enemy_PLANE_HEIGHT_3 = 50;


const int FRAMES_PER_SECOND = 30;			//��Ϸ֡��

const int TOTAL_Plane_Bullets = 20;			//�ҷ��ɻ�����
const int TOTAL_Ships_NUMBER  = 15;			//�л�����

#endif