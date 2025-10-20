#pragma once

#include <vector>
#include <iostream>

#include "MyExceptions.h"
#include "Config.h"

struct Point
{
	size_t x, y;
	
	Point() = default;
	Point(size_t x, size_t y) : x(x), y(y) {}

	bool operator<(const Point& point) const
	{
		if (this->x != point.x) return this->x < point.x;
		return this->y < point.y;
	}
};

class FieldPoint
{
private:
	EnFieldPointType point_type = EN_EMPTY_POINT;
	Point coord_point;

public:
	FieldPoint(size_t x, size_t y) : coord_point{ x, y }
	{
	}

	const Point& get_coord_point() const
	{
		return this->coord_point;
	}

	EnFieldPointType get_type() const
	{
		return this->point_type;
	}

	void set_type(EnFieldPointType new_point_type)
	{
		this->point_type = new_point_type;
		return;
	}
};

class GameField
{
private:
	std::vector<std::vector<std::shared_ptr<FieldPoint>>> game_field;

	void change_int_zone(size_t row_idx, size_t col_idx)
	{
		std::vector<Point> points = { {col_idx - 1, row_idx - 1}, {col_idx, row_idx - 1}, {col_idx + 1, row_idx - 1},
												{col_idx - 1, row_idx}, {col_idx + 1, row_idx},
												{col_idx - 1, row_idx + 1,}, {col_idx, row_idx + 1}, {col_idx + 1, row_idx + 1}
																};

		for (size_t idx = 0; idx < points.size(); idx++)
		{
			try
			{
				check_coords(points[idx].y, points[idx].x);
				game_field[points[idx].y][points[idx].x].get()->set_type(EN_INTERVAL_ZONE);
			}
			catch (...)
			{

			}
		}
	}

	void update_interval_zones(const std::vector<Point>& ship_coords)
	{
		for (size_t idx = 0; idx < ship_coords.size(); idx++)
		{
			size_t row = ship_coords[idx].y;
			size_t col = ship_coords[idx].x;

			change_int_zone(row, col);
		}
	}

public:
	GameField()
	{
		game_field.resize(Config::row_size);

		for (size_t i = 0; i < Config::row_size; i++)
		{
			game_field[i].resize(Config::col_size);

			for (size_t j = 0; j < Config::col_size; j++)
			{
				game_field[i][j] = std::make_shared<FieldPoint>(i, j);
			}
		}
	}

	void print_row_with_u_ptr(wchar_t litera, size_t idx, size_t u_ptr_col, bool print_key) const;
	void print_row(wchar_t litera, size_t idx, bool print_key) const;

	void print_field_large() const;
	void print_field() const;

	const std::vector<std::vector<std::shared_ptr<FieldPoint>>> get_field() const
	{
		return game_field;
	}

	bool check_coords(size_t row, size_t col, bool fire_mode = false)
	{
		if (row >= Config::row_size || col >= Config::col_size)
		{
			if(!fire_mode)
				throw ExceptionFieldCoords("\t[Chief Officer] These coords aren\'t seem correct, captain...\n");
			return false;
		}

		switch (game_field[row][col].get()->get_type())
		{
		case EN_EMPTY_POINT:
			//game_field[raw][col].get()->set_type(EN_SHIP_POINT);
			return true;

		case EN_FIRED_POINT:
			if (!fire_mode)
				throw ExceptionFieldPoint("\t[Chief Officer] This point doesn\'t seem safly for our ships, Captain...\n");
			break;
		case EN_SHIP_POINT:
			if (!fire_mode)
				throw ExceptionFieldPoint("\t[Chief Officer] One of our ship is already here, Captain\n");
			break;
		case EN_INTERVAL_ZONE:
			if (!fire_mode)
				throw ExceptionFieldPoint("\t[Chief Officer] We have another our ship close to this point, Captain\n");
			break;
		case EN_DESTROY_COMPARTMENT:
			if(!fire_mode)
				throw ExceptionFieldPoint("\t[Chief Officer] There's already no life, Captain\n");
			break;
		}

		return false;
	}

	void give_fire_point(const Point& fire_point)
	{
		size_t row = fire_point.y;
		size_t col = fire_point.x;

		if (this->game_field[row][col]->get_type() == EN_SHIP_POINT)
		{
			this->game_field[row][col]->set_type(EN_DESTROY_COMPARTMENT);
		}
		else
		{
			this->game_field[row][col]->set_type(EN_FIRED_POINT);
		}
	}

	EnFireOptions check_fire_point(const Point& p)
	{
		switch (game_field[p.y][p.x].get()->get_type())
		{
		case EN_EMPTY_POINT:
		case EN_INTERVAL_ZONE:
			return EN_MISSED;

		case EN_FIRED_POINT:
		case EN_DESTROY_COMPARTMENT:
			return EN_ERROR_COORDS;

		case EN_SHIP_POINT:
		default:
			return EN_HIT;
		}
	}

	void put_ship_on_the_map(const std::vector<Point>& ship_coords)
	{
		for (size_t idx = 0; idx < ship_coords.size(); idx++)
		{
			size_t raw = ship_coords[idx].y;
			size_t col = ship_coords[idx].x;

			game_field[raw][col].get()->set_type(EN_SHIP_POINT);
		}

		update_interval_zones(ship_coords);
	}
};

