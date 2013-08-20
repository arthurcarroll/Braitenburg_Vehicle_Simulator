#pragma once
class LineSegment
{
private:
int x1;
	int x2;
	int y1;
	int y2;
	
public:
	int pointNumberOne;
	int pointNumberTwo;
	void setx1(int X1);
	void setx2(int X2);
	void sety1(int Y1);
	void sety2(int Y2);

	int getx1();
	int getx2();
	int gety1();
	int gety2();
	LineSegment(void);
	LineSegment(int X1, int X2, int Y1, int Y2, int NumberOne, int NumberTwo);
	~LineSegment(void);
};

