#pragma once
#include <iostream>
#include <vector>

#include "..\Tik_Tak_Toe\Exceptions.h"
#include "Config.h"

class Field
{
public:
	using Mask = std::vector<int>;
private:
	int size{ 3 };

	std::vector<char> pole_state;
	std::vector<int> available_pos;

	std::vector<Mask> win_masks_vec;

	class FieldItem
	{
		Field* current{ nullptr };
		int row_index{ 0 };

	public:
		FieldItem(Field* current, int row_index) : current(current), row_index(row_index) { /*std::cout << "constructor FieldItem" << std::endl;*/ }

		operator char() const
		{
			return current->pole_state[row_index];
		}

		char& operator[](int col_index)
		{
			int pos{ 0 };

			if (row_index < 0 || row_index >= current->size || col_index < 0 || col_index >= current->size)
			{
				throw ExceptionErrorIndex("[Error msg] ExceptionIndex i and j should be in size", row_index, col_index);
			}

			pos = row_index * current->size + col_index;

			return current->pole_state[pos];
		}
	};

	void print_horizontal_nums() const;
	void print_horizontal_seps() const;
	void generate_win_masks();
	bool check_coord(int coord);

public:

	Field(int size = field_min_size)
	{
		/*std::cout << "constructor Field" << std::endl;*/

		if (!check_size(size))
			throw ExceptionErrorSize("[Error msg] ExceptionSize error. You can\'t create a field with that size...", size);

		this->size = size;

		for (int i = 0; i < size * size; i++)
		{
			this->pole_state.push_back('#');
			this->available_pos.push_back(i);
		}

		generate_win_masks();
	}
	~Field() { /*std::cout << "destructor ~Field" << std::endl;*/ }

	FieldItem operator[](int index)
	{
		try
		{
			return FieldItem(this, index);
		}
		catch (ExceptionErrorIndex& e)
		{
			throw;
		}
	}

	bool check_size(int size) const;
	void print_pole() const;
	int get_field_size() const;
	int get_size_of_win_masks() const;
	const std::vector<Mask>& get_win_masks() const;
	const std::vector<int>& get_available_pos() const;
	Mask get_mask_for_fig(char fig) const;

	bool change_the_field(int row, int col, char symbol);
	bool change_the_field(int index, char symbol);

	bool check_win_for(const Mask& mask) const;
};

