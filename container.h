#pragma once
#include "head.h"

struct Cell {
	Trapeze trap;
	Cell* next;
	Cell* prev;
	Cell() {

	}
	Cell(POINT one, POINT two, POINT three,POINT f,int r,int g, int b, int sr, int sg, int sb, int style, int bord) {
		trap.set_points(one, two, three,f);
		trap.set_style(style, bord, r, g, b, sr, sg, sb);
	}
	~Cell() {
		delete next;
	}
};

class Multitude
{
public:
	Multitude();									//конструктор
	~Multitude();									//деструктор
	void savefile(std::string namefile);
	void loadfile(std::string namefile);			// загрузка множества фигур с файла
	void insertElem(Cell& temp);
	bool isempty() const;							// проверка на пустоту
	int get_sizeM() const{ return sizeMultitude; }
	std::vector<int> searchbypoints(POINT,POINT,POINT,POINT) const;
	std::vector<int> searchbystyle(int r, int g, int b, int sr, int sg, int sb, int style, int sizepen) const;

		Trapeze operator[](int i) const{
		Cell* a;
		Trapeze temp;
		a = start;
		for (int r = 1; r < i; r++)a = a->next;
		temp = a->trap;
		return temp;
	}

private:
	int sizeMultitude;
	Cell* start;
	Cell* end;
};