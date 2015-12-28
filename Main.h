#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_DEPRECATE

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <string>
#include<stdlib.h>

using namespace std;
SDL_Renderer *Main_Renderer = nullptr;
SDL_Window *Main_Windows = nullptr;
TTF_Font *Main_Font = nullptr;

SDL_Texture* loadTexture(const string file, SDL_Renderer *renderer)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	if (texture == nullptr){
		cout << SDL_GetError() << endl;
	}
	return texture;
}

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend, SDL_Rect *clip = nullptr)
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;

	if (clip != nullptr)
	{
		pos.w = clip->w;
		pos.h = clip->h;
	}
	else
	{
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	}
	SDL_RenderCopy(rend, tex, clip, &pos);
}

/*
���ܣ���WINDOWS���ص��ַ���ת����UTF8����
���룺SRC �ַ���ָ��
�����ת������Ժ���ַ���ָ��
*/
char *SDL_localeToUTF8(char *src)
{
	static char *buf = NULL;
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	wchar_t *unicode_buf;
	int nRetLen = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
	unicode_buf = (wchar_t*)malloc((nRetLen + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, src, -1, unicode_buf, nRetLen);
	nRetLen = WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, NULL, 0, NULL, NULL);
	buf = (char*)malloc(nRetLen + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, buf, nRetLen, NULL, NULL);
	free(unicode_buf);
	return buf;
}

/*
���ܣ����ַ�����TTF����ת��Ϊ��ͼ
���룺TTF_Font TTF����ָ�룬SDL_Renderer ��Ⱦ��ָ�룬Text ������ַ���ָ�룬Color_R ��ɫRֵ��Color_G ��ɫGֵ��Color_B ��ɫBֵ
�����SDL_Texture ��ͼָ��
*/
SDL_Texture *SDL_CreateTTFTexture(TTF_Font *Font, SDL_Renderer *Renderer, char *Text, int Color_R, int Color_G, int Color_B)
{
	SDL_Color Color = { Color_R, Color_G, Color_B };
	SDL_Surface *Surf = TTF_RenderUTF8_Blended(Font, SDL_localeToUTF8(Text), Color);
	SDL_Texture *Text_Texture = SDL_CreateTextureFromSurface(Renderer, Surf);
	SDL_FreeSurface(Surf);
	return Text_Texture;
}

/*
���ܣ�����ͼ��ʾ����Ⱦ������
���룺Renderer Ŀ����Ⱦ����Texture ��ͼ��Mode ��ʾģʽ��1����ԭʼ�����ʾ��0��ʹ��֮���Զ���Ŀ����ʾ����Src_X ԴX��Src_Y ԴY��Src_Width Դ��Src_Height Դ�ߣ�Dst_X Ŀ��X��Dst_Y Ŀ��Y��Dst_Width Ŀ���Dst_Height Ŀ���
��������֣�0���ɹ���-1��ʧ�ܣ�
*/
int SDL_CopyTextureToRenderer(SDL_Renderer *Renderer, SDL_Texture *Texture, int Mode, int Src_X, int Src_Y, int Src_Width, int Src_Height, int Dst_X, int Dst_Y, int Dst_Width, int Dst_Height)
{
	SDL_Rect Src;
	SDL_Rect Dst;

	if (Mode == 0)
	{
		Src.x = Src_X;
		Src.y = Src_Y;
		Src.w = Src_Width;
		Src.h = Src_Height;

		Dst.x = Dst_X;
		Dst.y = Dst_Y;
		Dst.w = Dst_Width;
		Dst.h = Dst_Height;

		SDL_RenderCopy(Renderer, Texture, &Src, &Dst);
	}
	else if (Mode == 1)
	{
		Dst.x = Dst_X;
		Dst.y = Dst_Y;
		SDL_QueryTexture(Texture, NULL, NULL, &Dst.w, &Dst.h);
		SDL_RenderCopy(Renderer, Texture, NULL, &Dst);
	}
	else
		return -1;

	return 0;
}


/*
���ܣ���ⰴ���Ƿ񱻰���
���룺������ScanCodeֵ��ע�����Ҫ�Ǹ�ֵ��������ܷ����������
���������������1���ð��������� 0���ð���δ�����£�
*/
int SDL_KeyBoardKeyPressed(int Key)
{
	const Uint8 *KeyState = SDL_GetKeyboardState(NULL);

	if (KeyState[Key])
		return 1;
	else
		return 0;

}

/*
���ܣ����ַ�����TTF������ʾ����Ⱦ����
���룺���壬Ŀ����Ⱦ��������ʾ���ı��ַ�������ʾ����Ⱦ����λ��X����ʾ����Ⱦ����λ��Y��������ɫRֵ��������ɫGֵ��������ɫBֵ
�����0���ɹ�
*/
int SDL_ShowTTFtoRenderer(TTF_Font *Font, SDL_Renderer *Renderer, char *text, int x, int y, int Color_R, int Color_G, int Color_B)
{
	SDL_Texture *Text_Texture = SDL_CreateTTFTexture(Font, Renderer, text, Color_R, Color_G, Color_B);
	SDL_CopyTextureToRenderer(Renderer, Text_Texture, 1, 0, 0, 0, 0, x, y, 0, 0);
	SDL_DestroyTexture(Text_Texture);
	return 0;
}

char *IntToChar(int a)
{
	static char b[20];
	sprintf(b, "%d", a);
	return b;
}

#endif