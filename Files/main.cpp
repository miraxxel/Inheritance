#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<ctime>
using std::cin;
using std::cout;
using std::endl;

// ctrl+shift+u - в верхний регистр
//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	// При работе с файлами нужно:
	std::ofstream fout;		// 1) создать поток
	fout.open("File.txt", std::ios_base::app);	// 2) открыть поток
							// std::ios_base::app - append (дописать в конец файла)
	//fout << "HelloWorld" << endl; // 3) пишем в поток
	//fout << "Сам привет!" << endl;

	time_t now = time(NULL);
	fout << ctime(&now) << endl;

	fout.close();			// 4) закрываем поток
	// !!! Потоки как холодильник, если они были открыты, их обяз. нужно закрыть

	system("notepad File.txt");
#endif // WRITE_TO_FILE

#ifdef READ_FROM_FILE
	// 1) Создаем и открываем поток:
	std::ifstream fin("File.txt");
	if (fin.is_open())
	{
		// чтение файла:

		const int SIZE = 256;	// размер буфера
		char buffer[SIZE]{};	// буфер

		while (!fin.eof())	// NOT EndOfFile
		{
			//fin >> buffer; // читает до пробела
			fin.getline(buffer, SIZE); // читает строку с пробелами
			cout << buffer << endl;
		}

		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
#endif // READ_FROM_FILE

}