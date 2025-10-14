#include "GameField.h"

void GameField::print_raw(wchar_t litera, size_t idx, bool print_key) const
{
	std::wcout << L"| " << litera << L"  | "; // Добавлен пробел для выравнивания
	EnFieldPointType cur_point_type;

	for (size_t i = 0; i < Config::col_size; i++)
	{
		cur_point_type = game_field[idx][i].get()->get_type();

		if (!print_key && (cur_point_type == EN_INTERVAL_ZONE || cur_point_type == EN_SHIP_POINT))
		{
			cur_point_type = EN_EMPTY_POINT;
		}

		switch (cur_point_type)
		{
		case EN_EMPTY_POINT:
			printf("~~");
			break;
		case EN_FIRED_POINT:
			printf("XX");
			break;
		case EN_INTERVAL_ZONE:
			printf("^^");
			break;
		case EN_SHIP_POINT:
			printf("[]");
			break;
		case EN_DESTROY_COMPARTMENT:
			printf("##");
			break;
		}
		if (i < Config::col_size - 1)
			printf(" | ");
	}
}

void GameField::print_field_large() const
{
	// Заголовки карт: ширина 31 символ, текст центрирован
	printf("+======================================================+\n");
	printf("|                      Your Fleet                      |\n");
	printf("|      0    1    2    3    4    5    6    7    8    9  |\n");
	printf("+====+====+====+====+====+====+====+====+====+====+====+\n");

	//game_field

	// Вывод карт и таблицы
	wchar_t litera = L'A';
	for (size_t i = 0; i < Config::row_size; i++)
	{
		print_raw(litera, i, true);

		printf(" |\n");

		litera++;
		if (i < Config::row_size - 1)
		{
			printf("+====+====+====+====+====+====+====+====+====+====+====+\n");
		}
	}

	// Нижняя рамка карт
	printf("+====+====+====+====+====+====+====+====+====+====+====+\n");
}

void GameField::print_field() const
{
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	wchar_t litera = L'A';

	for (size_t i = 0; i < Config::row_size; i++)
	{
		std::wcout << litera++ << " ";

		for (size_t j = 0; j < Config::col_size; j++)
		{
			switch (game_field[i][j].get()->get_type())
			{
			case EN_EMPTY_POINT:
				printf("~");
				//printf("≈");
				break;
			case EN_FIRED_POINT:
				printf("X");
				break;
			}

			if (j < Config::col_size - 1)
				printf(" ");
		}

		printf("\n");
	}
}