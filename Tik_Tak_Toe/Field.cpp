#include "..\Tik_Tak_Toe\Field.h"

void Field::print_horizontal_nums() const
{
	// Верхний ряд координат (по столбцам)
	for (int i = 0; i < size; i++)
	{
		if (i == 0)
			std::printf("   ");

		std::printf("%d", i);

		if (i < size - 1)
			std::printf(" ");
	}
	std::printf("\n");
}
void Field::print_horizontal_seps() const
{
	// Горизонтальные линии разделители
	for (int i = 0; i < size; i++)
	{
		if (i == 0)
			std::printf("   ");

		std::printf("-");

		if (i < size - 1)
			std:printf(" ");
	}
	std::printf("\n");
}

void Field::generate_win_masks()
{
	// Horizontal masks
	for (int row = 0; row < size; row++)
	{
		Mask mask;

		for (int col = 0; col < size; col++)
		{
			mask.push_back(row * size + col);
		}

		win_masks_vec.push_back(mask);
	}

	//Vertical masks
	for (int col = 0; col < size; col++)
	{
		Mask mask;

		for (int row = 0; row < size; row++)
		{
			mask.push_back(row * size + col);
		}

		win_masks_vec.push_back(mask);
	}

	// Main diag
	{
		Mask mask;
		for (int i = 0; i < size; i++)
		{
			mask.push_back(i * size + i);
		}

		win_masks_vec.push_back(mask);
	}

	// Sub diag
	{
		Mask mask;

		for (int i = 0; i < size; i++)
		{
			mask.push_back(i * size + (size - 1 - i));
		}

		win_masks_vec.push_back(mask);
	}
}

bool Field::check_coord(int coord)
{
	return coord >= 0 && coord < size;
}

bool Field::check_size(int size) const
{
	if (size < field_min_size || size > field_max_size || size % 2 == 0)
		return false;

	return true;
}

void Field::print_pole() const
{
	int space_count = 0;

	// Верхний ряд координат (по столбцам)
	print_horizontal_nums();

	// горизонтальные линии разделители
	print_horizontal_seps();

	// вывод данных по полю
	for (int i = 0, j = 0; i < size * size; i++)
	{
		if (i % size == 0)
		{
			if (i != 0)
				std::printf("\n");

			std::printf("%d| ", j);
			j += 1;
		}

		std::printf("%c", pole_state[i]);

		if (space_count < size - 1)
		{
			std::printf(" ");
			space_count += 1;
		}
		else
		{
			std::printf(" |");
			space_count = 0;
		}
	}

	std::printf("\n");

	// повтор вывода разделителей
	print_horizontal_seps();
}

int Field::get_field_size() const { return this->size; };

int Field::get_size_of_win_masks() const
{
	return win_masks_vec.size();
}

const std::vector<Field::Mask>& Field::get_win_masks() const
{
	return this->win_masks_vec;
}

const std::vector<int>& Field::get_available_pos() const
{
	return this->available_pos;
}

Field::Mask Field::get_mask_for_fig(char fig) const
{
	Field::Mask mask;

	for (int i = 0; i < this->pole_state.size(); i++)
	{
		if(this->pole_state[i] == fig)
			mask.push_back(i);
	}

	return mask;
}

bool Field::change_the_field(int row, int col, char symbol)
{
	if (row < 0 || row >= size || col < 0 || col >= size)
		throw ExceptionErrorIndex("Invalid coordinates", row, col);

	int index = row * size + col;

	if (pole_state[index] != '#')
		return false; // Ячейка уже занята

	pole_state[index] = symbol;

	// Удаляем из available_pos
	auto it = std::find(available_pos.begin(), available_pos.end(), index);
	if (it != available_pos.end())
		available_pos.erase(it);

	return true;
}

bool Field::change_the_field(int index, char symbol)
{
	if (index < 0 || index >= pow(size, 2))
		throw ExceptionErrorIndex("Invalid coordinates", 0, index);

	if (pole_state[index] != '#')
		return false; // Ячейка уже занята

	pole_state[index] = symbol;

	// Удаляем из available_pos
	auto it = std::find(available_pos.begin(), available_pos.end(), index);
	if (it != available_pos.end())
		available_pos.erase(it);

	return true;
}

bool Field::check_win_for(const Mask& mask) const
{
	bool win_flag = true;

	for (const auto& win_mask : win_masks_vec)
	{
		win_flag = true;

		for (int index : win_mask)
		{
			if (std::find(mask.begin(), mask.end(), index) == mask.end())
			{
				win_flag = false;
				break;
			}
		}

		if (win_flag)
			return true;
	}

	return false;
}