#include<iostream>
#include <windows.h>

struct Color {

	int r;
	int g;
	int b;

};

struct Position {

	int left;
	int top;
	int right;
	int bottom;			// bottom + top = right + left => proportional circle
};

class Circle {
private:
	int radius{ 0 };
	Color color{ 0, 0, 0 };
	Position point{ 0, 0, 0, 0 };
	HWND handle{ 0 };
	HDC hdc{ 0 };

	Circle* arr = new Circle[5];

	int random(int MIN = 0, int MAX = 255) {
		return MIN + rand() % (MAX - MIN + 1);
	}

	Color randomColor() {
		Color randColor = { random(), random(), random() };
		return randColor;
		randColor = { 0, 0, 0 };
	}

	Position randomPosition() {
		Position arrPos[6] = { { 150, 150, 250, 250 }, { 150, 150, 200, 200 }, { 275, 275, 150, 150 },
		{ 150, 150, 175, 175 }, { 230, 230, 175, 175 }, { 125, 125, 250, 250 } };
		return arrPos[random(0, 5)];
	}

public:

	Circle(int radius = 5, Color color = { 0, 0, 0 }, Position point = { 0, 0, 0, 0 }, Circle* arr = nullptr) :
		radius{ radius },
		color{ color },
		point{ point },
		arr{ arr },
		handle{ FindWindowA("ConsoleWindowClass", NULL) },
		hdc{ GetDC(handle) }
	{}

	Circle* createArr(int newSwitchNum, Circle* newArr) {
		Circle* arr = new Circle[newSwitchNum];
		for (int i{}; i < newSwitchNum; ++i) {
			arr[i] = { 5, randomColor(), randomPosition() };
			newArr[i] = arr[i];
		}
		return newArr;
	}

	void SetRadius(int radiusNumber) { this->radius = radiusNumber; }

	void SetColor(int switchNumber) {
		switch (switchNumber) {
		case 1: this->color = { 255, 0, 0 }; break;
		case 2: this->color = { 0, 255, 0 }; break;
		case 3: this->color = { 0, 0, 255 }; break;
		}
	}

	void showCircle() {
		HPEN hPen = CreatePen(PS_SOLID, radius, (RGB(color.r, color.g, color.b))); // line color
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black color inside circle
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		// drawing circle
		Ellipse(hdc, point.left, point.top, point.right, point.bottom);
	}

	~Circle() {
		if (arr != nullptr) {
			delete[] arr;
		}
	}
};

int main() {

	srand(time(NULL));
	Circle a(5, { 255, 0, 0 }, { 100, 100, 300, 300 });
	bool whileFirst{ true };
	bool whileSecond{ true };
	while (whileFirst) {
		int radiusNum{};
		std::cout << "Chose cirle radius: " << std::endl;
		std::cin >> radiusNum;
		if (radiusNum > 15 || radiusNum < 0)
			whileFirst = true;
		else a.SetRadius(radiusNum);
		std::cout << "Chose circle color: " << std::endl;
		int switchNum{};
		std::cout << "Red - 1, Blue - 2, Green - 3" << std::endl;
		std::cin >> switchNum;
		if (switchNum != 1 || switchNum != 2 || switchNum != 3)
			whileFirst = true;
		else a.SetColor(switchNum);
		whileFirst = false;
	}
	while (whileSecond) {
		std::cout << "How many ellements you wanna add into the circle?" << std::endl;
		int switchNumber{};
		std::cin >> switchNumber;
		if (switchNumber > 5 || switchNumber < 0) {
			std::cout << "Wrong number of ellements" << std::endl;
			whileSecond = true;
		}
		Circle arr[5];
		arr->createArr(switchNumber, arr);
		a.showCircle();
		for (int i{}; i < switchNumber; ++i)
			arr[i].showCircle();
		whileSecond = false;
	}
	return 0;
}