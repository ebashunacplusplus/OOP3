#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class Trapeze {
public:

	Trapeze(POINT,POINT,POINT,POINT,int,int,int,int,int,int,int,int);

	Trapeze(){}
	void drawShadedTrapeze(HDC hdc, HWND hwnd) const;   // рисование закрашенной трапеции
	bool chek_figure() const;            // проверка фигуры на действительность
	bool chek_border(HWND hwnd) const;   // проверка выхода за границу экрана
	POINT get_pointx(int i) const{ return basicTrapeze[i]; } // возврат определенной точки трапеции
	const POINT* get_points() const{ return basicTrapeze; }
	int get_stylePen() const{ return stylePen; }
	int get_sizePen() const{ return sizePen; }
	COLORREF get_colorBorder() const{ return colorBorder; }
	COLORREF get_colorSolidBrush() const { return colorSolidBrush; }
	void set_points(POINT one, POINT two, POINT three, POINT f) {
		basicTrapeze[0].x = one.x;
		basicTrapeze[0].y = one.y;
		basicTrapeze[1].x = two.x;
		basicTrapeze[1].y = two.y;
		basicTrapeze[2].x = three.x;
		basicTrapeze[2].y = three.y;
		basicTrapeze[3].x = f.x;
		basicTrapeze[3].y = f.y;
	}
	void set_style(int style,int bord, int r, int g, int b, int sr, int sg, int sb) {
		colorBorder = RGB(r, g, b);
		colorSolidBrush = RGB(sr, sg, sb);
		stylePen = style;
		sizePen = bord;
	}
private:

	POINT basicTrapeze[4];      // основная трапеция
	COLORREF colorBorder;       // цвет контура
	COLORREF colorSolidBrush;   // цвет кисти
	int stylePen;               // стиль пера
	int sizePen;                // размер контура

};



