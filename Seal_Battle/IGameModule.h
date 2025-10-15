#pragma once

#include "GameModule.h"

class IGameModule
{
	public:
	virtual GameModuleData module_process(EnMenuOptions option) = 0;
	virtual ~IGameModule() = default;
};