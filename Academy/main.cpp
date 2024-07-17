#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define delimiter "\n------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS	const std::string& last_name, const std::string& first_name, unsigned int age // взять
#define HUMAN_GIVE_PARAMETERS	last_name, first_name, age // передать

class Human
{
	static const int HUMAN_TYPE_WIDTH = 10;
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 5;
	std::string last_name;
	std::string first_name;
	unsigned int age;

public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	const unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	//				Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//				Methods:
	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age << " y/o " << endl;
	}

	virtual std::ostream& info(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age << " y/o ";
	}
	virtual std::ofstream& write(std::ofstream& ofs)const
	{
		//ofs << strchr(typeid(*this).name(), ' ') + 1 << ":\t" << last_name << " " << first_name << " " << age;
		ofs.width(HUMAN_TYPE_WIDTH);	ofs << left << std::string(strchr(typeid(*this).name(), ' ') + 1) + ":";
		ofs.width(LAST_NAME_WIDTH);		ofs << left << last_name;
		ofs.width(FIRST_NAME_WIDTH);	ofs << left << first_name;
		ofs.width(AGE_WIDTH);			ofs << left << age;
		return ofs;
	}
		// strchr(typeid(*this).name() - cортировка, класс выводится без слова "Class".
	virtual std::ifstream& read(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.write(ofs);
}
std::ifstream& operator>>(std::ifstream& is, Human& obj)
{
	return obj.read(is);
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance
class Student :public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 8;
	static const int ATTENDANCE_WIDTH = 8;

	std::string speciality;
	std::string group;
	double rating;
	double attendance;

public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//				Constructors:
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//				Methods:
	void info()const override //переопределить
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ostream& info(std::ostream& os)const override
	{
		return Human::info(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		Human::write(ofs);
		ofs.width(SPECIALITY_WIDTH);	ofs << speciality;
		ofs.width(GROUP_WIDTH);			ofs << group;
		ofs.width(RATING_WIDTH);		ofs << rating;
		ofs.width(ATTENDANCE_WIDTH);	ofs << attendance;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs) override
	{
		Human::read(ifs);
		char buffer[SPECIALITY_WIDTH]{};
		ifs.read(buffer, SPECIALITY_WIDTH);
		for (int i = SPECIALITY_WIDTH - 1; buffer[i] == ' '; i--)buffer[i] = 0;
		while (buffer[0] == ' ')for (int i = 0; buffer[i]; i++)buffer[i] = buffer[i + 1];
		this->speciality = buffer;
		ifs >> group >> rating >> attendance;
		return ifs;
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, unsigned int experience 
#define TEACHER_GIVE_PARAMETERS speciality, experience 
class Teacher : public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int EXPERIENCE_WIDTH = 5;

	std::string speciality;
	unsigned int experience;

public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}

	//					Constructors:
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//					Methods:
	void info()const override
	{
		Human::info();
		cout << speciality << " " << experience << " ";
	}

	std::ostream& info(std::ostream& os)const override
	{
		return Human::info(os) << " " << speciality << " " << experience;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		Human::write(ofs);
		ofs.width(SPECIALITY_WIDTH); ofs << speciality;
		ofs.width(EXPERIENCE_WIDTH); ofs << experience;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Human::read(ifs);
		// read принимает 2 параметра и не умеет работать со строками, только с массивом char
		const int SIZE = SPECIALITY_WIDTH;
		char buffer[SIZE]{};
		ifs.read(buffer, SIZE);
		// strrchr - находит символ в строке, но просматривает строку справа налево, от конца к началу
		int poz = strrchr(buffer, ' ') - buffer; // poz - позиция символа пробела, здесь мы находим последний символ пробела в строке
		buffer[poz] = 0;
		// когда мы видим пробел, мы двигаем часть строки, до тех пор, пока не затрём этот пробел
		for (int i = SIZE - 1; buffer[i] == ' '; i--) buffer[i] = 0; // удаляем пробелы в конце; Здесь в buffer[i] = 0; 0 (детерминирующий ноль) - означает конец строки (char это int)
		while (buffer[0] == ' ') // удаляем пробелы в начале
		{
			for (int i = 0; buffer[i]; i++) buffer[i] = buffer[i + 1];
		}
		this->speciality = buffer;
		ifs >> experience;
		return ifs;
	}
};

class Graduate :public Student
{
	static const int SUBJECT_WIDTH = 32;
	std::string subject;

public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}

	//		Constructors:
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject) :Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//					Methods:
	void info() const override
	{
		Student::info();
		cout << subject << endl;
	}
	
	std::ostream& info(std::ostream& os) const override
	{
		return Student::info(os) << subject; // return Student:: для непосредств родителя
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		Student::write(ofs);
		ofs.width(SUBJECT_WIDTH); ofs << subject;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Student::read(ifs);
		std::getline(ifs, subject);
		return ifs;
	}
};

void Print(Human* group[], const int n)
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		//group[i]->info();
		cout << *group[i] << endl;
		cout << delimiter << endl;
	}
}
void Clear(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}
void Save(Human* group[], const int n, const std::string& filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
	std::string cmd = "notepad " + filename;
	system(cmd.c_str());
	// c_str() возвращает содержимое объекта std::string в виде обычно C-string (NULL Terminated line)
}
Human* HumanFactory(const std::string& type)
{
	Human* human = nullptr;
	if (type == "Human:")human = new Human("", "", 0);
	if (type == "Student:")human = new Student("", "", 0, "", "", 0, 0);
	if (type == "Teacher:")human = new Teacher("", "", 0, "", 0);
	if (type == "Graduate:")human = new Graduate("", "", 0, "", "", 0, 0, "");
	return human;
}
Human** Load(const std::string& filename, int& n)
{
	Human** group = nullptr;

	std::ifstream fin(filename);
	if (fin.is_open())
	{
		// 1. Считаем кол-во объектов, оно точно соответсвует кол-ву не пустых строк 
		n = 0;

		// условие проверяет, не достигнут ли конец файла (End Of File) после чтения данных из файла
		while (!fin.eof())
		{
			std::string buffer;
			//const int SIZE = 256;
			//char buffer[SIZE]{}; // NULL-Terminated Lines (C-strings - char arrays)
			//fin.getline(buffer, SIZE); // for NULL-Terminated Lines (C-strings - char arrays)
			std::getline(fin, buffer); // for std::string global func. std::getline(stream, string) used
			if (buffer.size() < 16)continue;
			n++; // только если строка не пустая
		}
		cout << "Кол-во строк в файле: " << n << endl;

		// 2. Выделяем память под массив
		group = new Human* [n] {};

		// 3. Возвращаемся в начало файла
		cout << fin.tellg() << endl;
		fin.clear();
		// get - чтение, put - запись
		fin.seekg(0);
		cout << fin.tellg() << endl;

		// 4. Выполняем чтение объектов
		for (int i = 0; i < n; i++)
		{
			std::string type;
			fin >> type;
			if (type.size() < 5)continue;
			group[i] = HumanFactory(type);
			if (group[i])fin >> *group[i];
			else continue;
		}

		fin.close();
	}
	else std::cerr << "Ошибка: файл не найден!" << endl;

	return group;
}

//#define INHERITANCE_CHECK
//#define POLYMORPHISM

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE_CHECK
	Human human("Vercetty", "Tommy", 30);
	human.info();

	Student student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 70, 97);
	student.info();

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.info();
#endif // INHERITANCE_CHECK
#ifdef POLYMORPHISM	
	//	Generalization:
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 70, 97),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Shreder", "Hank", 40, "Criminalistic", "OBN", 80, 90, "How to catch Heisenberg"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 97, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};
	cout << delimiter << endl;

	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	Clear(group, sizeof(group) / sizeof(group[0]));
#endif //POLYMORPHISM

	int n = 0;
	Human** group = Load("group.txt", n);
	Print(group, n);
	Clear(group, n);
}