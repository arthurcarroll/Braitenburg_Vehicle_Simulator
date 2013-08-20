#pragma once
class Point2D
{
public:
	int x;
	int y;
	int color;
	int direction;
	int pointNumber;
	Point2D(void);
	Point2D(int X, int Y, int Color, int d, int number);
	~Point2D(void);
	void setX(int X);
	void setY(int Y);
	void setColor(int Color);
	void setDirection(int d);
	int getX();
	int getY();
	int getColor();
	int getDirection();
};

