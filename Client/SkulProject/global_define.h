#pragma once

#define SINGLETON(type)			\
public:							\
	static type* GetInstance()	\
	{							\
		static type manager;	\
		return &manager;		\
	}							\
private:						\
	type();						\
	~type();

#define PI 3.1415926535f

const short WINDOW_WIDTH = 1280;
const short WINDOW_HEIGHT = 960;
const byte FPS = 60;