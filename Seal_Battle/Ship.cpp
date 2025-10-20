#include "Ship.h"

void ShipCompartment::hit()
{
	this->compartment_complement.died = this->compartment_complement.ready_for_fight / 2;
	this->compartment_complement.wounded = this->compartment_complement.ready_for_fight - this->compartment_complement.died;
	this->compartment_complement.ready_for_fight = 0;

	this->compartment_state = false;
}

Complement& ShipCompartment::get_compartment_complement()
{
	return this->compartment_complement;
}

bool ShipCompartment::get_compartment_state() const
{
	return this->compartment_state;
}

EnShipCompartmentType ShipCompartment::get_compartment_type() const
{
	return this->compartment_type;
}


EnShipCompartmentType Ship::check_comp_type(size_t idx)
{
	EnShipCompartmentType comp_type;

	if (idx == 0)
	{
		comp_type = EN_STERN;
	}
	else if (idx > 0 && idx < this->ship_size - 1)
	{
		comp_type = EN_MIDDLE;
	}
	else
	{
		comp_type = EN_BOW;
	}
	return comp_type;
}

const std::string& Ship::get_ship_name() const { return this->ship_name; }

EnShipTypeSize Ship::get_ship_size() const { return this->ship_size; }

size_t Ship::get_ship_complement() const { return this->ship_complement; }

EnShipType Ship::get_ship_type() const { return this->ship_type; }

const std::vector<std::shared_ptr<ShipCompartment>>& Ship::get_ship_hull() const { return this->ship_hull; }

const std::vector<std::shared_ptr<Point>>& Ship::get_ship_coords() const { return this->ship_coords; }

void Ship::destroy_ship_compartment(size_t index)
{
	// добавить расчет ранненых, убитых и готовых к бою
	this->hp--;
	ship_hull[index]->hit();

	if(hp == 0)
		this->is_active = false;

	size_t ready_for_fight = 0;

	for (auto comp : this->ship_hull)
	{
		ready_for_fight += comp->get_compartment_complement().ready_for_fight;
	}

	this->ship_complement = ready_for_fight; // live + wounded
}

std::string Ship::get_ship_type_str() const
{
	std::string ship_type_str;

	switch (this->ship_type)
	{
	case EN_BATTLESHIP:
		ship_type_str = "Battleship";
		break;
	case EN_CRUISER:
		ship_type_str = "Cruiser";
		break;
	case EN_DESTROYER:
		ship_type_str = "Destroyer";
		break;
	case EN_TORPEDO_BOAT:
		ship_type_str = "Torpedo Boat";
		break;
	}

	return ship_type_str;
}

void Ship::print_ship_info()
{
	printf("Ship name: %s; Ship class: %s; Ship size: %zu", ship_name.c_str(), get_ship_type_str().c_str(), ship_size);
	printf("\n");
}

void Ship::set_position_on_the_map(const std::vector<Point>& points)
{
	for (auto el : points)
	{
		this->ship_coords.push_back(std::make_shared<Point>(el.x, el.y));
	}

	return;
}