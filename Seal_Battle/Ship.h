#pragma once

#include <string>
#include <vector>
#include <memory>

#include "GameField.h"
#include "Config.h"

enum EnShipTypeSize
{
	EN_BATTLESHIP_SIZE = 4,
	EN_CRUISER_SIZE = 3,
	EN_DESTROYER_SIZE = 2,
	EN_TORPEDO_BOAT_SIZE = 1,
	EN_EMPTY_HULL = 0
};

enum EnShipType
{
	EN_BATTLESHIP = 2000,
	EN_CRUISER = 600,
	EN_DESTROYER = 200,
	EN_TORPEDO_BOAT = 50
};

enum EnShipDirection
{
	EN_SHIP_LEFT,
	EN_SHIP_RIGHT,
	EN_SHIP_TOP,
	EN_SHIP_BOTTOM,
	EN_SHIP_RESET
};

enum EnShipCompartmentType
{
	EN_BOW,
	EN_MIDDLE,
	EN_STERN
};

class ShipCompartment
{
private:
	size_t compartment_complement;
	bool   compartment_state;
	EnShipCompartmentType compartment_type;

public:
	ShipCompartment(size_t compartment_complement, EnShipCompartmentType compartment_type) :
		compartment_complement(compartment_complement), compartment_type(compartment_type)
	{
		this->compartment_state = true;
	}
	size_t get_compartment_complement() const
	{
		return this->compartment_complement;
	}
	
	bool get_compartment_state() const
	{
		return this->compartment_state;
	}

	EnShipCompartmentType get_compartment_type() const
	{
		return this->compartment_type;
	}

	void hit();
};

// Добавить направление для корабля в left, right, top, bottom, чтобы реализовать достойную отрисовку 
// <]()()[> 
// /\
// ()
// ()
// \/

class Ship
{
	std::vector<std::shared_ptr<ShipCompartment>> ship_hull;
	EnShipTypeSize ship_size{ EN_EMPTY_HULL };
	std::string ship_name;
	size_t ship_complement{ 0 };
	EnShipType ship_type;

	// Add_Coords
	std::vector<std::shared_ptr<Point>> ship_coords;

	EnShipCompartmentType check_comp_type(size_t idx);

public:
	Ship(EnShipType ship_type, std::string ship_name) : ship_type(ship_type), ship_name(ship_name)
	{
		EnShipCompartmentType comp_type;

		switch (ship_type)
		{
		case EN_BATTLESHIP:
			this->ship_complement = EN_BATTLESHIP;
			this->ship_size = EN_BATTLESHIP_SIZE;
			this->ship_hull.resize(this->ship_size);

			for (size_t i = 0; i < this->ship_size; i++)
			{
				comp_type = check_comp_type(i);

				this->ship_hull[i] = std::make_shared<ShipCompartment>(EN_BATTLESHIP / EN_BATTLESHIP_SIZE, comp_type);
			}

			break;
		case EN_CRUISER:
			this->ship_complement = EN_CRUISER;
			this->ship_size = EN_CRUISER_SIZE;
			this->ship_hull.resize(this->ship_size);

			for (size_t i = 0; i < this->ship_size; i++)
			{
				comp_type = check_comp_type(i);

				this->ship_hull[i] = std::make_shared<ShipCompartment>(EN_CRUISER / EN_CRUISER_SIZE, comp_type);
			}

			break;
		case EN_DESTROYER:
			this->ship_complement = EN_DESTROYER;
			this->ship_size = EN_DESTROYER_SIZE;
			this->ship_hull.resize(this->ship_size);

			for (size_t i = 0; i < this->ship_size; i++)
			{
				comp_type = check_comp_type(i);

				this->ship_hull[i] = std::make_shared<ShipCompartment>(EN_DESTROYER / EN_DESTROYER_SIZE, comp_type);
			}

			break;
		case EN_TORPEDO_BOAT:
			this->ship_complement = EN_TORPEDO_BOAT;
			this->ship_size = EN_TORPEDO_BOAT_SIZE;
			this->ship_hull.resize(this->ship_size);

			for (size_t i = 0; i < this->ship_size; i++)
			{
				comp_type = check_comp_type(i);

				this->ship_hull[i] = std::make_shared<ShipCompartment>(EN_TORPEDO_BOAT / EN_TORPEDO_BOAT_SIZE, comp_type);
			}

			break;
		}
	}
	virtual ~Ship() {};

	const std::string& get_ship_name() const;
	
	EnShipTypeSize get_ship_size() const;
	
	size_t get_ship_complement() const;
	
	EnShipType get_ship_type() const;
	
	const std::vector<std::shared_ptr<ShipCompartment>>& get_ship_hull() const;

	const std::vector<std::shared_ptr<Point>>& get_ship_coords() const;
	
	void destroy_ship_compartment(size_t index);

	std::string get_ship_type_str() const;

	void print_ship_info();

	void set_position_on_the_map(const std::vector<Point>& points);
};

class ShipBattleship : public Ship
{
public:
	ShipBattleship(EnShipType ship_type, std::string ship_name) : Ship(ship_type, ship_name)
	{

	}

	~ShipBattleship() {}
};

class ShipCrusier : public Ship
{
public:
	ShipCrusier(EnShipType ship_type, std::string ship_name) : Ship(ship_type, ship_name)
	{

	}

	~ShipCrusier() {}
};

class ShipDestroyer : public Ship
{
public:
	ShipDestroyer(EnShipType ship_type, std::string ship_name) : Ship(ship_type, ship_name)
	{

	}

	~ShipDestroyer() {}
};

class ShipTorpedoBoat : public Ship
{
public:
	ShipTorpedoBoat(EnShipType ship_type, std::string ship_name) : Ship(ship_type, ship_name)
	{

	}

	~ShipTorpedoBoat() {}
};