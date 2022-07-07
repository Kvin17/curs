
// Cursova2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif
#include <fstream>
#include "resource.h"	
#include <list>
using namespace std;


// CCursova2App:
// Сведения о реализации этого класса: Cursova2.cpp
//

class CCursova2App : public CWinApp
{
public:
	CCursova2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};
class Point
{
private: int x, y;
public:
	Point() {};
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int GetX() { return x; }
	int GetY() { return y; }
	void Draw(CPaintDC& dc) { dc.LineTo(x, y); }
	void SetPoint(CPaintDC& dc) { dc.MoveTo(x, y); }
};
class PolyGon
{
private:
	int ValueOfAngles=0;
	double Radius=0;
	double Diametr=0;
	int line=0;
	Point* ArrayPoint;
public:
	
	
	void SetPolyGon(Point *Array,int ValueOfAngles,int line)
	{
		this->ValueOfAngles = ValueOfAngles;
		ArrayPoint = new Point[ValueOfAngles];
		this->line = line;
		for (int i = 0; i < ValueOfAngles; i++)
		{
			ArrayPoint[i] = Array[i];
		}
	}
	PolyGon(){}
	void DrawingPolygon(CPaintDC &dc)
	{
		
			ArrayPoint[0].SetPoint(dc);
			for (int i = 1; i < ValueOfAngles; i++)
			{
				ArrayPoint[i].Draw(dc);
			}
			ArrayPoint[0].Draw(dc);
		
	}
	double SearchRadius()
	{
		for (int j = 0; j < ValueOfAngles; j++)
		{
			for (int i = j; i < ValueOfAngles -3 +j; i++)
			{
				int k = (i + 2) % 10;
				if (k >= j)
				{
					k -= j;
				}
				if (Diametr < sqrt(pow(ArrayPoint[j].GetX() - ArrayPoint[k].GetX(), 2) + pow(ArrayPoint[j].GetY() - ArrayPoint[k].GetY(), 2)))
				{
					Diametr = sqrt(pow(ArrayPoint[j].GetX() - ArrayPoint[k].GetX(), 2) + pow(ArrayPoint[j].GetY() - ArrayPoint[k].GetY(), 2));
				}
			}
		}
		Radius = Diametr / 2;
		return Radius;
	}
	int IsIntersect(int i,int j)
	{
		int _i = i; int _j = j;
		
		int k = _i - 1, o = _i + 1;
		if (k >= _j) { k -= _j; }
		if (o >= _j) { o -= _j; }
		if (k < 0) { k = _j - 1; }
		if (o < 0) { o = _j - 1; }
		
		
		if (Radius > (sqrt(pow(ArrayPoint[_i].GetX() - ArrayPoint[k].GetX(), 2) + pow(ArrayPoint[_i].GetY() - ArrayPoint[k].GetY(), 2)))/2 ||
			Radius> (sqrt(pow(ArrayPoint[_i].GetX() - ArrayPoint[o].GetX(), 2) + pow(ArrayPoint[_i].GetY() - ArrayPoint[o].GetY(), 2)))/2)
		{
			return 1;
		}
		else { return 0; }
		
	}
	void DrawCircle(CPaintDC& dc)
	{
		
			int j = ValueOfAngles;
			for (int i = 0; i < j; i++)
			{
				int k = i - 1, o = i + 1;
				if (k >= j) { k -= j; }
				if (o >= j) { o -= j; }
				if (k < 0) { k = j - 1; }
				if (o < 0) { o = j - 1; }

				if (sqrt(pow(ArrayPoint[i].GetX() - ArrayPoint[k].GetX(), 2) + pow(ArrayPoint[i].GetY() - ArrayPoint[k].GetY(), 2)) < line ||
					sqrt(pow(ArrayPoint[i].GetX() - ArrayPoint[o].GetX(), 2) + pow(ArrayPoint[i].GetY() - ArrayPoint[o].GetY(), 2)) < line)
				{
					/*Radius = 27.5;*/
					if (IsIntersect(i, j))
					{
						CPen Pen(PS_SOLID, 1, RGB(255, 0, 153));
						dc.SelectObject(Pen);
						dc.Ellipse(ArrayPoint[i].GetX() - Radius, ArrayPoint[i].GetY() - Radius, ArrayPoint[i].GetX() + Radius, ArrayPoint[i].GetY() + Radius);
					}
					else
					{
						CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
						dc.SelectObject(pen);
						dc.Ellipse(ArrayPoint[i].GetX() - Radius, ArrayPoint[i].GetY() - Radius, ArrayPoint[i].GetX() + Radius, ArrayPoint[i].GetY() + Radius);

					}

				
			}
		}
		
	}
	~PolyGon() { delete ArrayPoint; }
};
class SystemProgram
{
	string name;
	int x, y, line, ValueOfAngles = 0;
	ifstream ifs;
	PolyGon FirstPolygon;
public:
	void Init()
	{
		ifs.open("filePoint.txt");
		if (!ifs.is_open()) {}
		else
		{
			while (!ifs.eof())
			{
				ifs >> name;
				ifs >> x;
				ifs >> y;
				ValueOfAngles++;
			}
		}
		ifs.close();
		Point* PointArray = new Point[ValueOfAngles];
		ifs.open("filePoint.txt");
		if (!ifs.is_open()) {}
		else
		{
			for (int i = 0; i < ValueOfAngles; i++)
			{
				ifs >> name;
				ifs >> x;
				ifs >> y;
				PointArray[i] = Point(x, y);
			}
		}
		ifs.close();
		ifs.open("Line.txt");
		if (!ifs.is_open()) {}
		else
		{
			ifs >> name;
			ifs >> line;
		}
		ifs.close();
		FirstPolygon.SetPolyGon(PointArray, ValueOfAngles, line);
	}
	void Run()
	{
		FirstPolygon.SearchRadius();
		
	}
	void Draw(CPaintDC &dc)
	{
		if (ValueOfAngles > 0) 
		{
			FirstPolygon.DrawingPolygon(dc);
		}
		FirstPolygon.DrawCircle(dc);
	}
};
extern SystemProgram Program;
extern CCursova2App theApp;
