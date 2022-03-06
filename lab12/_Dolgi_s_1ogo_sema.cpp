#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <locale.h>
#define LIMIT 50  //ограничение на массив структуры
#pragma warning(disable : 4996) //Блокировка ошибки при чтении файла

//Константы и функции для оформления
#define q 70
#define lineBreak printf("\n")
#define Space(lenghtString) for (int i = 0; i < ((80-lenghtString)/2); i++) printf(" ")


//Прототипы функций
void CreateDatabase();    //Создать бд
void ReadingFromFile();   //Читать из файла
void SaveInFile();         // Сохранить файл
void CreateZapic();       //Ввод новой записи
void FindByKey();         //Найти по ключу
void Modification();       // Изменить запись
void View(int a);              //Посмотреть всю бд
void DeleteEntry();        //Удалить запись

//Количество записей в базе данных
unsigned int CountEntry = 0; 

//Структура "Драгоценные камни"
struct CRISTALGEM
{
	unsigned int ID = 0;         //Идентификатор 
	char name[20] = { 0 };       //Название
	char color[20] = { 0 };      //Цвет
	unsigned int price = 0;      //Цена за грамм
};
CRISTALGEM CristalGem[LIMIT];    //Массив записей

int main()
{
	setlocale(LC_ALL, "Rus"); system("chcp 1251"); //Русский язык
	int user = 0; //Выбор опции
	
	//Приветственное сообщение
	lineBreak;
	Space(24); printf("Лабораторная работа # 12\n\n");
	Space(11); printf("База данных\n\n");
	Space(55); printf("Программа использует тип данных Структура как кортеж БД\n");
	Space(60); printf("------------------------------------------------------------\n\n");
	Space(29); printf("   Структура \"Драгоценные камни\"\n\n");
	Space(q);  printf("   Имя              Тип\n");
	Space(q);  printf("   --------------------------------\n");
	Space(q);  printf("   ID               unsigned int\n");
	Space(q);  printf("   Название         char[30]\n");
	Space(q);  printf("   Цвет             char[20]\n");
	Space(q);  printf("   Цена за грамм    unsigned int\n");
	Space(q);  printf("   --------------------------------\n\n");
	
	//Меню
	menu:
		Space(q); printf("  | ------------------------------- |\n");
		Space(q); printf("? |          Выберите опцию         |\n");
		Space(q); printf("  | ------------------------------- |\n");
		Space(q); printf("  | Создать Базу данных       |  1  |\n");
		Space(q); printf("  | Добавить запись           |  2  |\n");
		Space(q); printf("  | Сохранить записи в файле  |  3  |\n");
		Space(q); printf("  | Изменить запись           |  4  |\n");
		Space(q); printf("  | Посмотреть Базу данных    |  5  |\n");
		Space(q); printf("  | Прочитать из файла        |  6  |\n");
		Space(q); printf("  | Поиск записи по ID        |  7  |\n");
		Space(q); printf("  | Удалить запись            |  8  |\n");
		Space(q); printf("  | Выйти                     |  9  |\n");
		Space(q); printf("  | ------------------------------- |\n");
		Space(q); printf(">>| ");
		
		// Считываем выбор пользователя
		do
		{
			scanf("%d", &user);
			if (user > 9 || user < 1)
			{
				Space(q); printf("!!| Опции не существует\n");
				Space(q); printf(">>|");
			}
		} while (user > 9 || user < 1);
		switch (user)
		{
		case 1: {
			Space(19); printf("Создать Базу данных\n");
			Space(31); printf("-------------------------------\n");
			CreateDatabase(); goto menu; }
		case 2: {
			Space(15); printf("Добавить запись\n");
			Space(31); printf("-------------------------------\n");
			CreateZapic(); goto menu; }
		case 3: {
			Space(24); printf("Сохранить записи в файле\n");
			Space(31); printf("-------------------------------\n");
			SaveInFile(); goto menu; }
		case 4: {
			Space(15); printf("Изменить запись\n");
			Space(31); printf("-------------------------------\n");
			Modification(); goto menu; }
		case 5: {
			Space(22); printf("Посмотреть Базу данных\n");
			Space(31); printf("-------------------------------\n");
			View(CountEntry); goto menu; }
		case 6: {
			Space(18); printf("Прочитать из файла\n");
			Space(31); printf("-------------------------------\n");
			ReadingFromFile(); goto menu; }
		case 7: {
			Space(18); printf("Поиск записи по ID\n\n");
			Space(31); printf("-------------------------------\n");
			FindByKey(); goto menu; }
		case 8: {
			Space(14); printf("Удалить запись\n\n");
			Space(31); printf("-------------------------------\n"); 
			DeleteEntry(); goto menu; }
		case 9: {
			Space(5); printf("Выйти\n\n");
			Space(31); printf("-------------------------------\n"); 
			Space(12); printf("До свидания!\n");
			exit(0);}
		default:
			break;
		}
}
void CreateDatabase()
{
	// Указатель на файл
	FILE* file;
	if ((file = fopen("database.txt", "w")) == NULL)
	{
		Space(q); perror("!!| Произошла ошибка при создании файла!\n");
		exit(0);
	}
	Space(q); printf("  | Файл успешно создан!\n");
	Space(q); printf("  | ------------------------------- |\n\n");
	return;
}
void CreateZapic()
{
	//Указатель на файл
	//FILE* file;
	//if ((file = fopen("database.txt", "w")) == NULL)
	//{
	//	Space(q); perror("!!| Произошла ошибка при создании файла!\n");
	//	exit(0);
	//}

	unsigned int CountAdd = 0; //Количество добавляемых записей
	
	//Ввод количества добавляемых записей
	do
	{
		Space(q); printf("? | Введите количество добавляемых записей\n");
		Space(q); printf(">>| ");
		scanf_s("%d", &CountAdd);
		if ((CountEntry == 0) && (CountAdd > LIMIT))
		{
			Space(q); printf("!!| Невозможно добавить данное число записей\n");
		}
		else if (CountAdd + CountEntry > LIMIT) 
		{ 
			Space(q); printf("!!| База данных переполнена!\n");
			Space(q); printf("  | Удалите имеющиеся данные.\n");
			Space(q); printf("? | Удалить?\n");
			Space(q); printf("  | Да     1\n");
			Space(q); printf("  | Нет    0\n");
			Space(q); printf(">>| ");
			int c = 0;
			scanf("%d", &c);
			if (c == 1) DeleteEntry();

		}
	} while ((CountAdd + CountEntry > LIMIT) || ((CountEntry == 0) && (CountAdd > LIMIT)));
	
	//Ввод данных
	for (unsigned int index = 0; index < CountAdd; index++)
	{
		Space(q); printf("  | -------------------\n");
		Space(q); printf("  | Запись номер %d\n", index+1);
		Space(q); printf("  | -------------------\n");
		int ID = -1; //Идентификатор
		bool exists = 1; //Проверка на наличие записи
		do
		{
			exists = 1;
			Space(q); printf("? | Введите ID\n");
			Space(q); printf(">>| ");
			scanf_s("%d", &ID);

			//Поиск записи с данных идентификатором
			for (unsigned int jndex = 0; jndex < CountEntry; jndex++)
			{
				if (CristalGem[jndex].ID == ID)
				{
					Space(q); printf("!!| Запись с таким номером уже существует\n");
					exists = 0;
					break;
				}
			}
		} while (exists == 0);
		CristalGem[CountEntry].ID = ID;
		Space(q); printf("? | Введите название\n");
		Space(q); printf(">>| "); scanf("%s", &CristalGem[CountEntry].name);
		
		Space(q); printf("? | Введите цвет\n");
		Space(q); printf(">>| "); scanf("%s", &CristalGem[CountEntry].color);
		
		Space(q); printf("? | Введите цену за грамм\n");
		Space(q); printf(">>| "); scanf("%d", &CristalGem[CountEntry].price);
		CountEntry++;
	}
	printf("\n\n");

	SaveInFile();
	////Сохранение в файл и вывод таблицы
	//fprintf(file, "%d\n", CountEntry);
	//for (unsigned int i = 0; i < CountEntry; i++) fprintf(file, "%d\n%s\n%s\n%d\n", CristalGem[i].ID, CristalGem[i].name, CristalGem[i].color, CristalGem[i].price);
	//View(CountEntry);
	//fclose(file);
	//Space(q); printf("  | Изменения сохранены!\n");
	//Space(q); printf("  | ------------------------------- |\n\n");
	View(CountEntry);
	return;
}
void SaveInFile()
{
	//Указатель на файл
	FILE* file;
	if ((file = fopen("database.txt", "w")) == NULL)
	{
		Space(q); perror("!!| Произошла ошибка при открытии файла!\n");
		exit(0);
	}
	//Сохраняем кол-во записей и сами записи
	fprintf(file, "%d\n", CountEntry);
	for (int index = 0; index < CountEntry; index++)
	{
		fprintf(file, "%d\n%s\n%s\n%d\n", CristalGem[index].ID, CristalGem[index].name, CristalGem[index].color, CristalGem[index].price);
	}
	fclose(file);
	Space(q); printf("  | Изменения сохранены!\n"); 
	Space(q); printf("  | ------------------------------- |\n\n");
	return;
}
void Modification()
{
	int ID = -1;  //Идентификатор
	unsigned int NumEntry = 0; //Порядковый изменяемой записи
	bool exists = 1; //Проверка на наличие записи
	do
	{
		exists = 1;
		Space(q); printf("? | Введите ID\n");
		Space(q); printf(">>| ");
		scanf_s("%d", &ID);
		for (unsigned int index = 0; index < CountEntry; index++)  //пробег по всем записям
		{
			if (CristalGem[index].ID != ID)  //поиск нужной записи по id
			{
				if (index == CountEntry-1) //конец поиска
				{
					Space(q); printf("!!| Записи с таким номером не существует\n");
					exists = 0;
				}
			}
			else
			{
				NumEntry = index;
				exists = 1;
				break;
			}
		}
	} while (exists == 0);
	
	Space(q); printf("? | Что вы хотите изменить? |\n");
	Space(q); printf("  | ----------------------- |\n");
	Space(q); printf("  | ID                |  1  |\n");
	Space(q); printf("  | Название          |  2  |\n");
	Space(q); printf("  | Цвет              |  3  |\n");
	Space(q); printf("  | Цена за грамм     |  4  |\n");
	Space(q); printf("  | ----------------------- |\n");
	Space(q); printf(">>| ");
	int option = 0;
	scanf("%d", &option);
	switch (option)
	{
	case 1:
	{	Space(q); printf("  | Модификация   ::   ID\n");
	    Space(q); printf("  | ----------------------\n");
		bool exists = 1;
		unsigned int newID = 0;
		do
		{
			bool exists = 1;
			Space(q); printf("? | Введите новый ID\n");
			Space(q); printf(">>| ");
			scanf("%d", &newID);
			for (unsigned int jndex = 0; jndex < CountEntry; jndex++)
			{
				if (CristalGem[jndex].ID == newID)
				{
					Space(q); printf("!!| Запись с таким номером уже существует\n");
					exists = 0;
					break;
				}
			}
		} while (exists == 0);
		CristalGem[NumEntry].ID = newID;
		Space(q); printf("  | Изменения сохранены!\n");
		Space(q); printf("  | ------------------------------- |\n\n");
		break; 
	}
	case 2:
	{
		Space(q); printf("  | Модификация   ::   Название\n");
		Space(q); printf("  | ----------------------------\n");
		Space(q); printf("? | Введите новое название\n");
		Space(q); printf(">>| ");
		scanf("%s", &CristalGem[NumEntry].name);
		Space(q); printf("  | Изменения сохранены!\n");
		Space(q); printf("  | ------------------------------- |\n\n");
		break;
	}
	case 3:
	{
		Space(q); printf("  | Модификация   ::   Цвет\n");
		Space(q); printf("  | ------------------------\n");
		Space(q); printf("? | Введите новый цвет\n");
		Space(q); printf(">>| ");
		scanf("%s", &CristalGem[NumEntry].color);
		Space(q); printf("  | Изменения сохранены!\n");
		Space(q); printf("  | ------------------------------- |\n\n");
		break;
	}
	case 4:
	{
		Space(q); printf("  | Модификация   ::   Цена за грамм\n");
		Space(q); printf("  | ---------------------------------\n");
		Space(q); printf("? | Введите новую цену за грамм\n");
		Space(q); printf(">>| ");
		scanf("%d", &CristalGem[NumEntry].price);
		Space(q); printf("  | Изменения сохранены!\n"); 
		Space(q); printf("  | ------------------------------- |\n\n");
	}
	default:
		break;
	}
	return;
}
void ReadingFromFile()
{
	//Указатель на файл
	FILE* file;
	if ((file = fopen("database.txt", "rt")) == NULL)
	{
		Space(q); perror("!!| Произошла ошибка при открытии файла!\n");
		exit(0);
	}
	//Читаем кол-во записей и сами записи
	fscanf(file, "%d", &CountEntry);
	for (int index = 0; index < CountEntry; index++)
	{
		fscanf(file, "%d%s%s%d", &CristalGem[index].ID, &CristalGem[index].name, &CristalGem[index].color, &CristalGem[index].price);
	}
	fclose(file);
	Space(q); printf("  | Файл Базы данных успешно открыт!\n");
	Space(q); printf("  | ------------------------------- |\n\n");
	return;
}
void FindByKey()
{
	unsigned int ID = 0; //Идентификатор
	Space(q); printf("? | Введите ID\n");
	Space(q); printf(">>| ");
	scanf_s("%d", &ID);
	lineBreak;
	//Поиск записи с таким ID
	for (unsigned int index = 0; index < CountEntry; index++)
	{
		if (CristalGem[index].ID == ID)
		{
			Space(q); printf("|----+---------------------+---------------------+--------|\n");
			Space(q); printf("| ID | Название            | Цвет                | Цена   |\n");
			Space(q); printf("|----+---------------------+---------------------+--------|\n");
			Space(q); printf("| %-3d| %-20s| %-20s| %-6d |\n", CristalGem[index].ID, CristalGem[index].name, CristalGem[index].color, CristalGem[index].price);
			Space(q); printf("|----+---------------------+---------------------+--------|\n");
			lineBreak;
			break;
		}
		if (index == CountEntry - 1)
		{
			Space(q); printf("! | Записи не существует\n");
			Space(q); printf("  | ------------------------------- |\n\n");
		}
	}
	return;
}
void DeleteEntry()
{
	int IDdelete = -1;    //не 0, т.к. ID - неотрицательное
	int IndexDelete = -1; //индекс записи в массиве
	bool exists = 1;
	do
	{
		exists = 1;
		Space(q); printf("? | Введите ID\n");
		Space(q); printf(">>| ");
		scanf("%d", &IDdelete);
		for (unsigned int index = 0; index < CountEntry; index++)  //пробег по всем записям
		{
			if (CristalGem[index].ID != IDdelete)  //поиск нужной записи по id
			{
				if (index == CountEntry - 1) //конец поиска
				{
					Space(q); printf("! | Записи с таким номером не сущетсвует\n");
					exists = 0;
				}
			}
			else 
			{ 
				IndexDelete = index;
				exists = 1;
				break;
			}
		}
		if (exists == 0)
		{
			Space(q); printf("? | Передумали удалять?\n");
			Space(q); printf("  | Выйти       1\n");
			Space(q); printf("  | Продолжить  0\n");
			Space(q); printf(">>| ");
			int c = 0;
			scanf("%d", &c);
			if (c == 1) return;
		}
	} while (exists == 0);
	
	//Смещение записей вверх / Удаление
	for (unsigned int index = IndexDelete; index < CountEntry; index++)
	{
		CristalGem[index] = CristalGem[index + 1];
	}
	CountEntry--;
	Space(q); printf("  | Изменения сохранены!\n");
	Space(q); printf("  | ------------------------------- |\n\n");
	return;
}

void View(int a)
{
	Space(q); printf("|----+---------------------+---------------------+--------|\n");
	Space(q); printf("| ID | Название            | Цвет                | Цена   |\n");
	Space(q); printf("|----+---------------------+---------------------+--------|\n");
	for (int i = 0; i < a; i++)
	{
		Space(q); printf("| %-3d| %-20s| %-20s| %-6d |\n", CristalGem[i].ID, CristalGem[i].name, CristalGem[i].color, CristalGem[i].price);
		Space(q); printf("|----+---------------------+---------------------+--------|\n");
	}
	lineBreak;
}