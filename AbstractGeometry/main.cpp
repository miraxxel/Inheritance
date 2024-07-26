#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
#include<math.h>
using namespace std;

namespace Geometry
{
	enum Color	//enum (Enumeration) - ��� ������������. ������������ - ��� ����� ������������� ��������
	{
		CONSOLE_BLUE = 0x09,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_RED = 0xCC,
		CONSOLE_DEFAULT = 0x07,
		// ��� ����� �������� �� 1 ����, ������� ������ ����� ��������, ��� ��� ���������� 1 ���� ��������� � ������� 4 �����

		// ��� ����� �������� �� 4 ���� 
		RGB_RED = (0xFF0000), 
		RGB_GREEN = (0x00FF00),
		BLUE = 0x00FF0000,
		RGB_WHITE = (0xFFFFFF),
		YELLOW = 0x0000FFFF
	};

#define SHAPE_TAKE_PARAMETERS  unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS  start_x, start_y, line_width, color
	class Shape
	{
	protected: // ���������� ����
		// ��������� protected, � ���� ����� ����� ����� ���������� �������� � �������� ������� (��� get � set �������)
		Color color;
		// ����������, �� ���. ����� �����-�� ������:
		unsigned int start_x; // ��� x - ����� �������
		unsigned int start_y; // ��� y - ������ ����
		// � ����� ����.�������� ���������� �������� � ������� (������� - ����� �� ������)
		// ������ ��������� - ����� ������� ���� ������
		unsigned int line_width; // ������� �����, ���. ����� ���. ������ ������

	public:
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		// ����� ����������� � �� ���� ���� ������������� ������ ������, ������ � ���������� ����� ����������� (������� ���� ��������, �������� �� ���������, ���� ���� �� ��������)
		virtual ~Shape() {} // ������� {} ����� �������, ��� ���������� ��������� ����� � ������ �����������
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		Color get_color()const
		{
			return color;
		}
		void set_color(Color color)
		{
			this->color = color;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			this->line_width = line_width;
		}

		virtual void info()const
		{
			cout << "������� ������: " << get_area() << endl;
			cout << "�������� ������:" << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
	{
		double side; // ����� �������
	public:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		virtual ~Square() {}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, get_color());
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
		}
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "����� �������: " << side << endl;
			Shape::info();
		}
	};*/

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}
		// ��������� ����� ����������� ������
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, "Inheritance - Microsoft Visual Studio");
			//HWND hwnd = GetConsoleWindow();	// 1) �������� ����������� ���� �������
											// HWND - Handler to Window (���������� (��� ���������� - ���������� � ������� �������� �������� ����-����) ����)
			HDC hdc = GetDC(hwnd);			// 2) �������� ��������� ���������� (Device Context) ���� �������
											//	 DC - ��� ��, �� ��� �� ����� ��������
			HPEN hPen = CreatePen(PS_SOLID, 5, get_color());	// 3) ������� ��������. pen ������ ������ ������
																// PS_SOLID - �������� �����
																// 5 - ������� ����� � ��������
			// 4) ������� �����
			HBRUSH hBrush = CreateSolidBrush(get_color());
			 
			// 5) �������� ��� � �� ��� ��������:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			// 6) ������ �������������:
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);
			// start_x, start_y - ���������� �������� ������ ����
			// start_x + width, start_y + height - ���������� ������� ������� ����.

			// 7) ���������� �������:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc); // ����������� �������� ����������
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������: " << get_width() << endl;
			cout << "������: " << get_height() << endl;
			Shape::info();
		}
	};

	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS):Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return 2 * radius;
		}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diameter();
		}
		void set_radius(double radius)
		{
			this->radius = radius;
		}

		void draw()const override
		{
			HWND hwnd =	FindWindow(NULL, "Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			// PS_SOLID - ����������� �����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_BLUE);
	Geometry::Square square(50, 300, 50, 5, Geometry::Color::BLUE);
	/*cout << "����� ������� ���������: " << square.get_side() << endl;
	cout << "������� ��������:  " << square.get_area() << endl;
	cout << "�������� ��������: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect{ 150, 80, 500, 50, 3,  Geometry::Color::BLUE };
	rect.info();

	Geometry::Circle circle(75, 700, 50, 5, Geometry::Color::YELLOW);
	circle.info();
}