#pragma once

#include <windows.h>
#include <map>

#include "Fleet.h"

class Player
{
private:
	std::shared_ptr<GameField> ptr_player_field;
	std::shared_ptr<Fleet> ptr_player_fleet;
	std::map<Point, std::shared_ptr<Ship>> point_to_ship_dict;

	static size_t players_count;
	size_t player_id;
	size_t point_count;
	std::string name;
	bool cur_state = false;

	EnShipDirection parse_direction(std::string direction_str);
	
	void parse_coordinates(const std::string& input, size_t& row, size_t& col);

	bool modify_ship_hull(std::vector<Point>& ship_hull, size_t data_raw, size_t data_col);

	EnSystemCode set_positions(Ship& ship, std::vector<Point>& ship_hull, EnShipDirection en_ship_direction, size_t data_raw, size_t data_col);

	EnSystemCode set_ship_hull(Ship& ship, std::vector<Point>& ship_hull);

	void set_ship_stern(Point& stern_point);

	void set_player_ship(std::shared_ptr<Ship> ship);

	void set_random_location_ship(std::shared_ptr<Ship> ship);

public:
	Player(std::string name, const Config& config) : point_count(0)
	{
		ptr_player_field = std::make_shared<GameField>();
		ptr_player_fleet = std::make_shared<Fleet>(config);

		this->name = name;
		player_id = Player::players_count;
		Player::players_count++;
	}
	Player(const Player& other_player)
	{
		this->player_id = other_player.player_id;
		this->name = other_player.name;
		this->point_count = other_player.point_count;
		this->cur_state = other_player.cur_state;

		this->ptr_player_field = other_player.ptr_player_field;
		this->ptr_player_fleet = other_player.ptr_player_fleet;
		this->point_to_ship_dict = other_player.point_to_ship_dict;
	}

	void set_player_fleet();

	Point make_turn();

	void get_fleet_damage(const Point& fire_point);

	void print_player_field() const;

	const std::shared_ptr<GameField> get_field() const;

	const std::shared_ptr<Fleet> get_fleet() const;

	const std::map<Point, std::shared_ptr<Ship>>& get_point_to_ship_dict() const;

	size_t get_player_id() const;

	size_t get_point_count() const;
	
	const std::string& get_player_name() const;
	
	bool get_cur_state() const;
};