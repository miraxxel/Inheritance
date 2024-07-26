#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
#include<math.h>
using namespace std;

namespace Geometry
{
	enum Color	//enum (Enumeration) - это перечисление. Перечисление - это набор целочисленных констант
	{
		CONSOLE_BLUE = 0x09,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_RED = 0xCC,
		CONSOLE_DEFAULT = 0x07,
		// эти цвета занимают по 1 байт, поэтому фигуры будут красными, так как занимаемый 1 байт находится в области 4 байта

		// эти цвета занимают по 4 байт 
		RED = 0xFF0000, 
		RGB_GREEN = 0x00FF00,
		BLUE = 0x00FF0000,
		RGB_WHITE = 0xFFFFFF,
		YELLOW = 0x0000FFFF
	};

#define SHAPE_TAKE_PARAMETERS  unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS  start_x, start_y, line_width, color
	class Shape
	{
	protected: // защищенные поля
		// Благодаря protected, к этим полям можно будет обращаться напрямую в дочерних классах (без get и set методов)
		Color color;
		// Координаты, по кот. будет вывод-ся фигура:
		unsigned int start_x; // Ось x - слева направо
		unsigned int start_y; // Ось y - сверху вниз
		// В любой граф.оболочке координаты задаются в писелях (пиксель - точка на экране)
		// Начало координат - левый верхний угол всегда
		unsigned int line_width; // толщина линии, кот. будет рис. контур фигуры

		// Константы
		static const int MIN_START_X = 100;
		static const int MAX_START_X = 1000;
		static const int MIN_START_Y = 100;
		static const int MAX_START_Y = 500;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 550;
		static int count;

	public:
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);

			count++;
		}
		// Класс абстрактный и от него буду наследоваться другие классы, значит и деструктор будет виртуальным (пишется ради приличия, работает по умолчанию, даже если не прописан)
		virtual ~Shape() { count--; } // пишутся {} чтобы указать, что деструктор создается сразу с пустой реализацией
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		static int get_count(){ return count; }

		Color get_color()const{ return color; }
		void set_color(Color color){ this->color = color; }
		unsigned int get_start_x()const{ return start_x; }
		unsigned int get_start_y()const{ return start_y; }
		unsigned int get_line_width()const{ return line_width; }
		void set_start_x(unsigned int start_x)
		{
			if (start_x < MIN_START_X)start_x = MIN_START_X;
			if (start_x > MAX_START_X)start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y < MIN_START_Y)start_y = MIN_START_Y;
			if (start_y > MAX_START_Y)start_y =	MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}
		double filter_size(double size)
		{
			if (size < MIN_SIZE)size = MIN_SIZE;
			if (size > MAX_SIZE)size = MAX_SIZE;
			return size;
		}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimeter() << endl;
			draw();
		}
	};
	int Shape::count = 0;

	/*class Square :public Shape
	{
		double side; // длина стороны
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
			cout << "Длина стороны: " << side << endl;
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
		// реализуем чисто виртуальные методы
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
			//HWND hwnd = GetConsoleWindow();	// 1) Получаем десткриптор окна консоли
											// HWND - Handler to Window (Обработчик (иди Дескриптор - переменная в которой хранится описание чего-либо) окна)
			HDC hdc = GetDC(hwnd);			// 2) Получаем констекст устройства (Device Context) окна консоли
											//	 DC - это то, на чем мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());	// 3) Создаем карандаш. pen рисует контур фигуры
																// PS_SOLID - сплошная линия
																// 5 - толщина линии в пикселях
			// 4) Создаем кисть
			HBRUSH hBrush = CreateSolidBrush(get_color());
			 
			// 5) Выбираем чем и на чем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			// 6) Рисуем прямоугольник:
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);
			// start_x, start_y - координаты верхнего левого угла
			// start_x + width, start_y + height - координаты нижнего правого угла.

			// 7) Освбождаем ресурсы:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc); // освобождаем контекст устройства
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
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << get_width() << endl;
			cout << "Высота: " << get_height() << endl;
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
			this->radius = filter_size(radius);
		}

		void draw()const override
		{
			HWND hwnd =	FindWindow(NULL, "Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			// PS_SOLID - непрерывная линия
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			Shape::info();
		}
	};

	class Triangle :public Shape
	{
	public:
		virtual double get_height()const = 0;
		Triangle(SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS) {}
		~Triangle() {}

		void info()const override
		{
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public: 
		double get_side()const{ return side; }
		void set_side(double side){	this->side = filter_size(side); }
		double get_height()const{ return sqrt(side * side - side / 2 * side / 2); }
		double get_area()const override{ return side / 2 * get_height(); }
		double get_perimeter()const override{ return side * 3; }
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, "Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT apt[] =
			{
				// создаем объект структур:
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side/2, start_y + side - get_height()}
			};

			// (плоская фигура)
			::Polygon(hdc, apt, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}

		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны:\t " << side << endl;
			Triangle::info();
		}
	};

	class RightTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const { return side; }
		void set_side(double side) { this->side = filter_size(side); }
		double get_height()const { return sqrt(side * side - side / 2 * side / 2); }
		double get_area()const override { return side / 2 * get_height(); }
		double get_perimeter()const override { return side * 3; }
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, "Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT apt[] =
			{
				// создаем объект структур:
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side, start_y + side - get_height()}
			};

			// (плоская фигура)
			::Polygon(hdc, apt, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}

		RightTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~RightTriangle() {}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны:\t " << side << endl;
			Triangle::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_BLUE);
	Geometry::Square square(50, 300, 50, 5, Geometry::Color::BLUE);
	/*cout << "Длина стороны клвадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата:  " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect{ 150, 80, 500, 50, 3,  Geometry::Color::BLUE };
	rect.info();

	Geometry::Circle circle(75, 700, 50, 5, Geometry::Color::YELLOW);
	circle.info();

	Geometry::EquilateralTriangle e_triangle(100, 200, 200, 5, Geometry::Color::RGB_GREEN);
	e_triangle.info();
	
	Geometry::RightTriangle r_triangle(100, 350, 200, 5, Geometry::Color::RGB_WHITE);
	r_triangle.info();

	cout << "Кол-во фигур: " << e_triangle.get_count() << endl; // можно так вызывать метод
	cout << "Кол-во фигур: " << Geometry::Shape::get_count() << endl; // но это считается более правильным
}