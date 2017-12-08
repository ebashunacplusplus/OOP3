#include "head.h"
#include "container.h"
using namespace std;

int main(int argc, char *argv[]) {
	vector<int> iter;
	int menu = -1,number,r,g,b,sr,sg,sb,style,sizepen;
	POINT a, bb, c, d;
	Multitude myContainer;
	Trapeze temp;
	HWND hwnd = FindWindowA("notepad", nullptr);
	HDC hdc = GetDC(hwnd);
	string namefile;
	std::vector<int> v_p;
	std::vector<int> v_s;
	Cell* el;
	Cell* itemp;
	int flag = 0;

	while (menu != 0) {
		system("cls");
		cout << "0 - Exit" << endl;
		cout << "1 - Get number figure" << endl;
		cout << "2 - Print table Right to Left" << endl;
		cout << "3 - Print table Left to Right" << endl;
		cout << "4 - Search by points" << endl;
		cout << "5 - Search by style" << endl;
		cout << "6 - Load file" << endl;
		cout << "7 - Insert element" << endl;
		cin >> menu;

		try {
			switch (menu)
			{
			case 7:
				flag = 0;
				system("cls");
				std::cout << "x1: ";
				std::cin >> a.x;
				std::cout << "y2: ";
				std::cin >> a.y;
				std::cout << "x2: ";
				std::cin >> bb.x;
				std::cout << "y2: ";
				std::cin >> bb.y;
				std::cout << "x3: ";
				std::cin >> c.x;
				std::cout << "y3: ";
				std::cin >> c.y;
				std::cout << "x4 : ";
				std::cin >> d.x;
				std::cout << "y4: ";
				std::cin >> d.y;
				std::cout << "Style: ";
				std::cin >> style;
				std::cout << "Size border: ";
				std::cin >> sizepen;
				std::cout << "Color pen (r): ";
				std::cin >> r;
				std::cout << "Color pen (g): ";
				std::cin >> g;
				std::cout << "Color pen (b): ";
				std::cin >> b;
				std::cout << "Color solid (r): ";
				std::cin >> sr;
				std::cout << "Color solid (g): ";
				std::cin >> sg;
				std::cout << "Color solid (b): ";
				std::cin >> sb;

				v_p = myContainer.searchbypoints(a, bb, c, d);
				v_s = myContainer.searchbystyle(r, g, b, sr, sg, sb, style, sizepen);
				for (int k = 0; k < v_p.size(); k++) {
					for (int j = 0; j < v_s.size(); j++)
						if (v_p[k] == v_s[j]) flag++;
				}
				if (flag) {
					cout << "The figure is already in the table" << endl;
					system("pause");
					break;
				}
			    itemp = new Cell(a,bb,c,d,r,g,b,sr,sg,sb,style,sizepen);

				myContainer.insertElem(*itemp);

				break;
			case 6:
				system("cls");
				cout << "Inter the name of file: " << endl;
				cin >> namefile;
				myContainer.loadfile(namefile);
				cout << "Data if reading" << endl;
				system("pause");
				break;
			case 5:
				system("cls");
				if (myContainer.isempty())throw 1;
				std::cout << "Parametrs for search:" << std::endl;
				std::cout << "Color pen r = ";
				std::cin >> r;
				std::cout << "Color pen g = ";
				std::cin >> g;
				std::cout << "Color pen b = ";
				std::cin >> b;
				std::cout << "Color solid r = ";
				std::cin >> sr;
				std::cout << "Color solid g = ";
				std::cin >> sg;
				std::cout << "Color solid b = ";
				std::cin >> sb;
				std::cout << "Style pen = ";
				std::cin >> style;
				std::cout << "Size pen = ";
				std::cin >> sizepen;
				iter = myContainer.searchbystyle(r,g,b,sr,sg,sb,style,sizepen);
				if (!iter.size()) {
					system("cls");
					cout << "item not found" << endl;
					system("pause");
					break;
				}
				system("cls");
				cout << "The desired figure stands on ";
				for (int k = 0; k < iter.size(); k++)cout << iter[k] << ", ";
				cout << "iteration" << endl;
				system("pause");
				break;
			case 4:
				system("cls");
				if (myContainer.isempty())throw 1;
				std::cout << "Parametrs for search:" << std::endl;
				std::cout << "x1: ";
				std::cin >> a.x;
				std::cout << "y1: ";
				std::cin >> a.y;
				std::cout << "x2: ";
				std::cin >> bb.x;
				std::cout << "y2: ";
				std::cin >> bb.y;
				std::cout << "x3: ";
				std::cin >> c.x;
				std::cout << "y3: ";
				std::cin >> c.y;
				std::cout << "x4: ";
				std::cin >> d.x;
				std::cout << "y4: ";
				std::cin >> d.y;
				iter = myContainer.searchbypoints(a,bb,c,d);
				if (!iter.size()) {
					system("cls");
					cout << "item not found" << endl;
					system("pause");
					break;
				}
				system("cls");
				cout << "The desired figure stands on ";
				for (int k = 0; k < iter.size(); k++)cout << iter[k] << ", ";
				cout << "iteration" << endl;
				system("pause");
				break;
			case 3:
				system("cls");
				for(int i = 1; i <= myContainer.get_sizeM(); i++)
					cout << "Trapeze " << i << " : " 
					<< "x1: "  << myContainer[i].get_pointx(0).x 
					<< " y1: " << myContainer[i].get_pointx(0).y
					<< " x2: " << myContainer[i].get_pointx(1).x 
					<< " y2: " << myContainer[i].get_pointx(1).y 
					<< " x3: " << myContainer[i].get_pointx(2).x
					<< " y3: " << myContainer[i].get_pointx(2).y
					<< " x4: " << myContainer[i].get_pointx(3).x 
					<< " y4: " << myContainer[i].get_pointx(3).y 
					<< " stylePen: " << myContainer[i].get_stylePen()
					<< " sizePen: " << myContainer[i].get_sizePen() << endl;
				system("pause");
				break;
			case 2:
				system("cls");
				for (int i = myContainer.get_sizeM(); i > 0; i--)
					cout << "Trapeze " << i << " : "
					<< "x1: " << myContainer[i].get_pointx(0).x
					<< " y1: " << myContainer[i].get_pointx(0).y
					<< " x2: " << myContainer[i].get_pointx(1).x
					<< " y2: " << myContainer[i].get_pointx(1).y
					<< " x3: " << myContainer[i].get_pointx(2).x
					<< " y3: " << myContainer[i].get_pointx(2).y
					<< " x4: " << myContainer[i].get_pointx(3).x
					<< " y4: " << myContainer[i].get_pointx(3).y
					<< " stylePen: " << myContainer[i].get_stylePen()
					<< " sizePen: " << myContainer[i].get_sizePen() << endl;
				system("pause");
				break;
			case 1:
				system("cls");
				cout << "Press number figure: ";
				cin >> number;
				if (!myContainer.get_sizeM()) {
					system("cls");
					cout << "Container is empty" << endl;
					system("pause");
					break;
				}
				if (number <= 0 || number > myContainer.get_sizeM()) {
					cout << "Element does not exist" << endl;
					system("pause");
					break;
				}
				myContainer[number].drawShadedTrapeze(hdc,hwnd);
				break;
			case 0:
				system("cls");
				cout << "Write namefile for save: ";
				cin >> namefile;
				myContainer.savefile(namefile);
				break;
			default:
				system("cls");
				cout << "Error..." << endl;
				system("pause");
				break;
			}
		}
		catch (int a) {
			
			if (a == 4) {
				system("cls");
				cout << "The figure is not a trapezoid" << endl;
				system("pause");
			}
			if (a == 5) {
				system("cls");
				cout << "The figure is beyond the screen" << endl;
				system("pause");
			}
			if (a == 6) {
				system("cls");
				cout << "File not found" << endl;
				system("pause");
			}
		}
	}
	system("pause");
	return 0;
}