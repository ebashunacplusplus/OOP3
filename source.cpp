#include "head.h"
#include "container.h"

void Trapeze::drawShadedTrapeze(HDC hdc, HWND hwnd) const {

	if (!chek_figure())throw 4;
	if (!chek_border(hwnd))throw 5;

	HBRUSH hBrushS = CreateSolidBrush(colorSolidBrush);
	HPEN hPen = CreatePen(stylePen, sizePen, colorBorder);
	SelectPen(hdc, hPen);
	SelectBrush(hdc, hBrushS);
	Polygon(hdc, basicTrapeze, 4);
	DeletePen(hPen);
	DeleteBrush(hBrushS);
}

bool Trapeze::chek_figure() const{
	int a, b;
	a = (basicTrapeze[2].x - basicTrapeze[1].x) * (basicTrapeze[3].y - basicTrapeze[0].y) -
		(basicTrapeze[2].y - basicTrapeze[1].y) * (basicTrapeze[3].x - basicTrapeze[0].x);
	b = (basicTrapeze[1].x - basicTrapeze[0].x) * (basicTrapeze[2].y - basicTrapeze[3].y) -
		(basicTrapeze[1].y - basicTrapeze[0].y) * (basicTrapeze[2].x - basicTrapeze[3].x);
	if (a == 0 && b != 0) return 1;
	return 0;
}

bool Trapeze::chek_border(HWND hwnd) const{
	RECT border;
	GetClientRect(hwnd, &border);
	for (int i = 0; i < 4; i++) {
		if (basicTrapeze[i].x > border.right || basicTrapeze[i].x < 0 || basicTrapeze[i].y > border.bottom || basicTrapeze[i].y < 0)
			return 0;
	}
	return 1;
}

Multitude::Multitude()
{
	sizeMultitude = 0;
	start = nullptr;
	end = nullptr;
}

Multitude::~Multitude()
{
	delete start;
}

Trapeze::Trapeze(POINT one, POINT two, POINT three,POINT f,int r,int g, int b, int sr, int sg, int sb, int style, int bord) {
	set_points(one, two, three,f);
	set_style(style, bord, r, g, b, sr, sg, sb);
}

bool Multitude::isempty() const{
	if (sizeMultitude)return 0;
	return 1;
}

std::vector<int> Multitude::searchbypoints(POINT a, POINT b, POINT c, POINT d) const{
	std::vector<int> i;
	int r = 1;
	Cell* x;
	x = start;
	while (x != nullptr) {
		if ((a.x == x->trap.get_pointx(0).x) 
			&& (a.y == x->trap.get_pointx(0).y) 
			&& (b.x == x->trap.get_pointx(1).x) 
			&& (b.y == x->trap.get_pointx(1).y) 
			&& (c.x == x->trap.get_pointx(2).x) 
			&& (c.y == x->trap.get_pointx(2).y)
			&& (d.x == x->trap.get_pointx(3).x)
			&& (d.y == x->trap.get_pointx(3).y)) i.push_back(r);
		r++;
		x = x->next;
	}
	return i;
}

std::vector<int> Multitude::searchbystyle(int r,int g,int b,int sr,int sg, int sb, int style,int sizepen) const{
	COLORREF pen, solid;
	int i = 1;
	std::vector<int> rr;
	pen = RGB(r, g, b);
	solid = RGB(sr, sg, sb);
	Cell* x;
	x = start;
	while (x != nullptr) {
		if (pen == x->trap.get_colorBorder() && solid == x->trap.get_colorSolidBrush() && style == x->trap.get_stylePen() && sizepen == x->trap.get_sizePen()) rr.push_back(i);
		i++;
		x = x->next;
	}
	return rr;
}

void Multitude::loadfile(std::string namefile) {

	Cell* a;
	int style, r, g, b, sr, sg, sb, bord, flag = 0;
	std::vector<int> v_p;
	std::vector<int> v_s;
	POINT one, two, three, f;
	std::ifstream fin;

	fin.open(namefile);
	if (!fin)throw 6;

	while (!fin.eof()) {
		fin >> one.x >> one.y >> two.x >> two.y
			>> three.x >> three.y >> f.x >> f.y
			>> style >> bord >> r >> g >> b
			>> sr >> sg >> sb;

		v_p = searchbypoints(one, two, three, f);
		v_s = searchbystyle(r, g, b, sr, sg, sb, style, bord);
		for (int k = 0; k < v_p.size(); k++) {
			for (int j = 0; j < v_s.size(); j++)
				if (v_p[k] == v_s[j])flag++;
		}
		if (flag) { flag = 0;  continue; }

			if (start == nullptr) {
				start = new Cell(one, two, three, f, r, g, b, sr, sg, sb, style, bord);
				start->next = nullptr;
				start->prev = nullptr;
				sizeMultitude++;
				end = start;
			}
			else {
				a = end;
				a->next = new Cell(one, two, three, f, r, g, b, sr, sg, sb, style, bord);
				a = a->next;
				a->next = nullptr;
				a->prev = end;
				end = a;
				sizeMultitude++;
			}
		}
	fin.close();
}

void Multitude::savefile(std::string namefile) {
	std::ofstream fout;
	fout.open(namefile, std::ofstream::ios_base::trunc);
	Cell* a;
	a = start;
	while (a != nullptr) {
		for(int r = 0;r<4;r++) fout << a->trap.get_pointx(r).x <<" "<< a->trap.get_pointx(r).y << std::endl;
		fout << a->trap.get_stylePen() << " " << a->trap.get_sizePen() << " "
			 << (int)GetRValue(a->trap.get_colorBorder()) << " " << (int)GetGValue(a->trap.get_colorBorder()) << " " << (int)GetBValue(a->trap.get_colorBorder()) << std::endl;
		fout << (int)GetRValue(a->trap.get_colorSolidBrush()) << " " << (int)GetGValue(a->trap.get_colorSolidBrush()) << " " << (int)GetBValue(a->trap.get_colorSolidBrush()) << std::endl;
		a = a->next;
	}
	fout.close();
}

void Multitude::insertElem(Cell& temp) {

	Cell* a;

	if (start == nullptr) {
		start = &temp;
		start->next = nullptr;
		start->prev = nullptr;
		sizeMultitude++;
		end = start;
	}
	else {
		a = &temp;
		a->prev = nullptr;
		a->next = start;
		start->prev = a;
		start = a;
		sizeMultitude++;
	}

}
	