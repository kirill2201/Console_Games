#pragma once

#include "Ship.h"

enum EnFleetSize
{
	EN_DEFAULT_SIZE = 10 // 1 корабль размером 4 клетки (четырёхпалубный, "линкор"). 
								// 2 корабля размером 3 клетки(трёхпалубные, "крейсеры").
								// 3 корабля размером 2 клетки(двухпалубные, "эсминцы").
								// 4 корабля размером 1 клетка(однопалубные, "подлодки" или "торпедные катера").
};

class Fleet
{
private:
	size_t size_def_fleet = EN_DEFAULT_SIZE;
	size_t size_oper_fleet = EN_DEFAULT_SIZE;
	size_t size_wasted_fleet = 0;

	std::vector<std::shared_ptr<Ship>> fleet;
	std::vector<std::shared_ptr<Ship>> wasted_ships;

public:
	Fleet(const Config& config)
	{
		size_t idx = 0;

		fleet.push_back(std::make_shared<ShipBattleship>(EN_BATTLESHIP, config.get_ship_names()[idx++]));

		fleet.push_back(std::make_shared<ShipCrusier>(EN_CRUISER, config.get_ship_names()[idx++]));
		fleet.push_back(std::make_shared<ShipCrusier>(EN_CRUISER, config.get_ship_names()[idx++]));

		fleet.push_back(std::make_shared<ShipDestroyer>(EN_DESTROYER, config.get_ship_names()[idx++]));
		fleet.push_back(std::make_shared<ShipDestroyer>(EN_DESTROYER, config.get_ship_names()[idx++]));
		fleet.push_back(std::make_shared<ShipDestroyer>(EN_DESTROYER, config.get_ship_names()[idx++]));

		fleet.push_back(std::make_shared<ShipTorpedoBoat>(EN_TORPEDO_BOAT, config.get_ship_names()[idx++]));
		fleet.push_back(std::make_shared<ShipTorpedoBoat>(EN_TORPEDO_BOAT, config.get_ship_names()[idx++]));
		fleet.push_back(std::make_shared<ShipTorpedoBoat>(EN_TORPEDO_BOAT, config.get_ship_names()[idx++]));
		fleet.push_back(std::make_shared<ShipTorpedoBoat>(EN_TORPEDO_BOAT, config.get_ship_names()[idx++]));
	}

	const std::vector<std::shared_ptr<Ship>>& get_wasted_ships() const;

	const std::vector<std::shared_ptr<Ship>>& get_current_fleet() const;

	const size_t get_size_of_oper_fleet() const;

	const size_t get_size_of_wasted_fleet() const;

	size_t get_def_size() const;

	bool check_situation()
	{
		size_oper_fleet = 0;
		size_wasted_fleet = 0;

		for (const auto& ship : fleet)
		{
			if (ship->get_is_active())
			{
				size_oper_fleet += 1;
			}
			else
			{
				size_wasted_fleet += 1;
				wasted_ships.push_back(ship);
			}
		}

		this->size_oper_fleet = size_oper_fleet;
		this->size_wasted_fleet = size_wasted_fleet;

		return this->size_oper_fleet != 0;
	}
};