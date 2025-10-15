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

	EnPlayers player_id;
	bool cur_state = false;

	size_t point_count;
	std::string name;

	EnShipDirection parse_direction(std::string direction_str);
	
	void parse_coordinates(const std::string& input, size_t& row, size_t& col);

	bool modify_ship_hull(std::vector<Point>& ship_hull, size_t data_raw, size_t data_col);

	EnSystemCode set_positions(Ship& ship, std::vector<Point>& ship_hull, EnShipDirection en_ship_direction, size_t data_raw, size_t data_col);

	EnSystemCode set_ship_hull(Ship& ship, std::vector<Point>& ship_hull);

	void set_ship_stern(Point& stern_point);

	void set_player_ship(std::shared_ptr<Ship> ship);

	void set_random_location_ship(std::shared_ptr<Ship> ship);

public:

	Player(std::string name, EnPlayers player_id, const Config& config) : point_count(0), name(name), player_id(player_id)
	{
		ptr_player_field = std::make_shared<GameField>();
		ptr_player_fleet = std::make_shared<Fleet>(config);
	}

	Player(const Player& other_player) 
		: point_count(other_player.point_count), name(other_player.name), player_id(other_player.player_id), cur_state(other_player.cur_state),
			ptr_player_field(other_player.ptr_player_field), ptr_player_fleet(other_player.ptr_player_fleet),
			point_to_ship_dict(other_player.point_to_ship_dict) {}

	void set_player_fleet();

	Point make_turn();

	void get_fleet_damage(const Point& fire_point);

	void print_player_field() const;

	const std::shared_ptr<GameField> get_field() const;

	const std::shared_ptr<Fleet> get_fleet() const;

	const std::map<Point, std::shared_ptr<Ship>>& get_point_to_ship_dict() const;

	EnPlayers get_player_id() const;

	size_t get_point_count() const;
	
	const std::string& get_player_name() const;
	
	bool get_cur_state() const;
	void set_cur_state(bool state)
	{
		this->cur_state = state;
	}
};