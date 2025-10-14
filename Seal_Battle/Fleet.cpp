#include "Fleet.h"

const std::vector<std::shared_ptr<Ship>>& Fleet::get_wasted_ships() const
{
	return wasted_ships;
}

const std::vector<std::shared_ptr<Ship>>& Fleet::get_current_fleet() const
{
	return this->fleet;
}

const size_t Fleet::get_size_of_oper_fleet() const
{
	return this->size_oper_fleet;
}

const size_t Fleet::get_size_of_wasted_fleet() const
{
	return this->size_wasted_fleet;
}