
#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include  <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

//структурный массив
typedef struct toys {
	
	char toys_name[100];
	char toys_cost[100];
	char toys_category[100];


}toys_table;


void memory(toys_table** massiv, size_t howmany) {	
	*massiv = (toys_table*)realloc(*massiv, howmany * (sizeof(toys_table)));
}


//проверка файла
bool Check(FILE* input)
{
	if (input == NULL)
	{
		printf("ОШИБКА! Файл не был открыт!!\n");
		return false;
	}
	return true;
}

//управление с клавы
int GetKey()
{
	int key = _getch();
	if ((key == 0) || (key == 224))
	{
		key = _getch();
	}
	return key;
}

//кол-во строк в блокноте
int CountLine(FILE* input)
{
	int line = 0;
	int ch = 0;
	while (!feof(input))
	{
		if (getc(input) == '\n')
		{
			line++;
		}
	}
	rewind(input);
	line++;
	return line;
}

//Загрузка данных
void LoadData(FILE* input, toys_table*& massiv, int& line)
{
	int i = line;
	while (!feof(input))
	{

		line++;
		memory(&massiv, line);
		int r = fscanf(input, "%s\t%s\t%s\n", massiv[i].toys_name, massiv[i].toys_cost, massiv[i].toys_category);
		i++;
	}
}

//печать данных
void PrintCurrent(int number, toys_table* massiv) 
{
	system("cls");
	printf("\n");
	printf("Название игршки: %s\n Цена игрушки: %s\n Возрастная категория: %s\n\n", massiv[number].toys_name, massiv[number].toys_cost, massiv[number].toys_category);
	printf("\n");

}

//удаление данных
void delete_data(int number, int& line, toys_table*& massiv) {
	for (int j = number; j < line; j++) 
	{
		massiv[j] = massiv[j + 1];
	}
	line--;
	memory(&massiv, line);
}

// стрелочка -->
void Arrow(int real_position, int position)
{
	if (real_position == position)
	{
		printf("-->");
	}
	else
	{
		printf("    ");
	}
}

// лево-право
int MenuHelp()
{
	printf("\n");
	printf("Вперёд -> \n Назад <-\n Выход: Esc");
	while (true)
	{
		int key = GetKey();
		if ((key == 27) || (key == 75) || (key == 77))
			system("cls");
			return key;
	}
	
}
//выход из списка
int MenuEnd()
{
	printf("\n");
	printf("Выход: Esc");
	while (true)
	{
		int key = GetKey();
		if ((key == 27))
			system("cls");
		return key;
	}

}



//первое меню
int Menu1()
{
	int position = 1;
	int KeyPres = 0;

	while (KeyPres != 13)
	{
		printf("\tМЕНЮ\t\n");
		Arrow(1, position); printf("Загрузить данные из файла\n");
		Arrow(2, position); printf("Работа с данными\n");
		Arrow(3, position); printf("Сохранить данные в файл\n");
		Arrow(4, position); printf("Сохранить данные с указанной категорией\n");
		Arrow(5, position); printf("Выход\n\n");
		KeyPres = GetKey();
		system("cls");
		if (KeyPres == 72 && position != 1)
			position--;
		else if (KeyPres == 80 && position != 5)
		{
			position++;
		}
	}
	return position;
}
//второе меню
int Menu2()
{
	int position = 1;
	int KeyPres = 0;
	while (KeyPres != 13)
	{
		printf("\tМЕНЮ_2\t\n");
		Arrow(1, position); printf("Просмотр записей (по одной, а также выбор для удаления или изменения)\n");
		Arrow(2, position); printf("Просмотр всех записей списком\n");
		Arrow(3, position); printf("Добавить запись\n");
		Arrow(4, position); printf("Удалить запись\n");
		Arrow(5, position); printf("Изменить запись\n");
		Arrow(6, position); printf("Назад\n");

		KeyPres = GetKey();
		system("cls");
		if (KeyPres == 72 && position != 1)
			position--;
		if (KeyPres == 80 && position != 6)
		{
			position++;
		}
	}
	return position;
}

//третье меню(для изменений)
int Menu3()
{
	int position = 1;
	int KeyPres = 0;
	system("cls");
	while (KeyPres != 13)
	{
		printf("\n\tЧто вы хотите изменить?\t\n");
		Arrow(1, position); printf("Название игрушки\n");
		Arrow(2, position); printf("Цену игрушки\n");
		Arrow(3, position); printf("Возрастную категорию\n");
		Arrow(4, position); printf("Полностью запись\n");
		Arrow(5, position); printf("Назад\n\n");
		KeyPres = GetKey();
		system("cls");
		if (KeyPres == 72 && position != 1)
			position--;
		else if (KeyPres == 80 && position != 5)
		{
			position++;
		}


	}
	return position;
}

//сортировка по имени
void SortByName(toys_table*&massiv, int end)
{
	toys_table temp;
	for (int k = 0; k < end - 1; k++)
	{
		for (int j = k + 1; j < end; j++)
		{
			int cmp = strcmp(massiv[k].toys_name, massiv[j].toys_name);

			if (cmp > 0)
			{
				temp = massiv[k];
				massiv[k] = massiv[j];
				massiv[j] = temp;
			}
		}
	}
}


//среднее значение
int average_value(toys_table*& massiv, int end) // end - кол-во строк
{
	int average = 0;
	long summ = 0;
	for (int k = 0; k < end; k++)
	{
		long l = strtol(massiv[k].toys_cost, NULL, 10);
		summ = summ + l;
	}
	average = summ / end;
	
	return average;
}

//фильтр по категории
void FilterByCategory(int& line, char* category, toys_table*& massiv)
{
	int num = 0;
	
	for (int j = 0; j < line; j++)
	{
		if (strcmp(massiv[j].toys_category, category) == 0)
		{
			massiv[num] = *(struct toys*)&massiv[j];
			num++;
			
		}
	}
	line = num;
	memory(&massiv, line);


}
//фильтр по среднему значению
void FilterByAverage(int &line, int average, toys_table *& massiv)
{
	int num = 0;

	for (int k = 0; k < line; k++)
	{
		if (strtol(massiv[k].toys_cost, NULL, 10) >= average)
		{
			massiv[num] = *(struct toys*)&massiv[k];
			num++;
		}
	}
	line = num;
	memory(&massiv, line);
}



//просмотр записей
int cheсk_massiv(int number, toys_table* massiv, int line)
{
	while (true)
	{
		PrintCurrent(number, massiv);
		int m3 = MenuHelp();
		if (m3 == 27)
		{
			break;
		}
		switch (m3)
		{
		case 75:
			if (number > 0)
			{
				number--;
			} break;
		case 77:
			if (number < line - 1)
			{
				number++;
			}
			break;
		}
	}
	return number;
}

//добавление записей
void add_data(int& line, toys_table*& massiv)
{
	printf("Введите данные в виде: Название игрушки, цена игрушки, возрастная категория\n");
	memory(&massiv, line + 1);
	scanf("%s %s %s", massiv[line].toys_name, massiv[line].toys_cost, massiv[line].toys_category);
	line++;
}

//сохранение файла
void SaveFile1(int end, FILE* input, toys_table* massiv)
{
	for (int k = 0; k < end; k++)
	{
		fprintf(input, "%-25s\t%-25s\t%-25s\n", massiv[k].toys_name, massiv[k].toys_cost, massiv[k].toys_category);
	}
}



//печать всех данных
void PrintAllData(toys_table*& massiv, int& line) 
{

	for (int i = 0; i < line; i++)
	{
		printf("Название игрушки : %s\n Цена игрушки : %s\n Возрастная категория: %s\n\n", massiv[i].toys_name, massiv[i].toys_cost, massiv[i].toys_category);
	}
	
}

//вывод списком
void PrintList(toys_table*& massiv, int& line)
{
	while (true)
	{
		PrintAllData(massiv, line);
		int m4 = MenuEnd();
		if (m4 == 27)
		{
			break;
		}
	}
}





void SaveRes(int &line, char* category, toys_table*& massiv, FILE* output)
{
	FilterByCategory(line, category, massiv);
	int b = average_value(massiv, line);
	FilterByAverage(line, b, massiv);
	SortByName(massiv, line);
	SaveFile1(line, output, massiv);


}









int main()
{
	setlocale(LC_ALL, "");
	setlocale(LC_CTYPE, "Russian");

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int line = 0, number = 0;
	toys_table* massiv = {};
	char category[100];
	memory(&massiv, 0);
	int choice2 = 1, choice3 = 1;
	char user_path[1000];
	while (true)
	{
		
		int choice1 = Menu1();
		switch (choice1)
		{
		case 1:
		{
			FILE* input = NULL;
			printf("Введите путь к файлу из которого хотите считать данные(если такого файла не существует, он будет создан по этому пути):\n");
			scanf("%[^\n]", user_path);
			input = fopen(user_path, "a+");
			if (Check(input))
			{
				LoadData(input, massiv, line);
				fclose(input);
			}
			system("cls");
			break;
		}
		case 2:
		{
			while (choice2)
			{
				int men2 = Menu2();
				switch (men2)
				{
				case 1:
				{
					if (line != 0)
						number = cheсk_massiv(number, massiv, line);
					else
						printf("Добавьте или считайте запись\n");
					break;
				}
				case 2:
				{
					PrintList(massiv, line);
					break;
				}
				case 3:
				{
					add_data(line, massiv);
					break;
				}
				case 4:
				{
					if (line != 0)
						delete_data(number, line, massiv);
					else
						printf("Добавьте или считайте запись\n");
					break;
				}
				case 5:
				{
					if (line != 0)
					{
						int men3 = Menu3();
						switch (men3)
						{
						case 1:
						{
							printf("Текущее название: %s \n", massiv[number].toys_name);
							printf("Введите новое название: ");
							scanf("%s", massiv[number].toys_name);
							system("cls");

							break;
						}
						case 2:
						{
							printf("Текущая цена: %s \n", massiv[number].toys_cost);
							printf("Введите новую цену: ");
							scanf("%s", massiv[number].toys_cost);
							system("cls");
							break;
						}
						case 3:
						{
							printf("Текущая категория: %s \n", massiv[number].toys_category);
							printf("Введите новую категорию: ");
							scanf("%s", massiv[number].toys_category);
							system("cls");
							break;
						}
						case 4:
						{
							printf("Введите данные в виде: Название игрушки, цена игрушки, возрастная категория\n");
							scanf("%s %s %s", massiv[number].toys_name, massiv[number].toys_cost, massiv[number].toys_category);
							system("cls");
							break;
						}
						case 6:
						{
							men3 = 0;
							choice3 = 0;
							break;
						}
						choice3 = 1;
						}

					}
					else
						printf("Добавьте или считайте запись\n");
					break;
				}
				case 6:
				{
					choice1 = 0;
					choice2 = 0;
					break;
				}
				}
				choice2 = 1;
				break;

			}
		}
		case 3:
		{
			
			FILE* input = fopen("C:\\Users\\mrtim\\Desktop\\res.txt", "w"); //новый файл с результатом
			if (Check(input)) {
				SaveFile1(line, input, massiv);
				fclose(input);
			}
			break;
		}

		case 4:
		{
			FILE* output = fopen("C:\\Users\\mrtim\\Desktop\\res.txt", "w");
			if (Check(output))
			{
				printf("Введите необходимую категорию(0+; 6+; 12+; 16+; 18+)\n");
				scanf("%s", &category);
				SaveRes(line, category, massiv, output);
				fclose(output);
			}
			break;
		}

		case 5:
		{
			free(massiv);
			printf("Программа была завершена!\n");
			return 0;
		}
		}
	}
	return 0;
}
