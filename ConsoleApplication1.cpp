﻿// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include<cstdio>
#include<string.h>
char res[500]];
FILE*stream, *stream1;

int main(void)
{
	char rer[] = { 6, 2, 66 };
	fopen_s( &stream,"C:/Users/aiman/Desktop/111/sign.txt", "r+");
	fopen_s(&stream1, "C:/Users/aiman/AppData/Local/Temp/6a5699ff91e64db0ace7e175814d6890/ATmega162/mys.h", "w+");
	int i = 0;
	
	
	while (fgets(res, sizeof(500), stream)!= NULL)
	{fputs(res, stream1);
		i++;}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
