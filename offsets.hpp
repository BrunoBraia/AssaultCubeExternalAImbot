#pragma once

#include <iostream>

namespace offsets
{
	//offsets.hpp
	constexpr std::ptrdiff_t localPlayer = 0x0017E0A8;
	constexpr std::ptrdiff_t entityList = 0x18AC04;
	constexpr std::ptrdiff_t playerCount = 0x18AC0C;

	//deslocamentos
	constexpr std::ptrdiff_t positionX = 0x4; //0x2C; 
	constexpr std::ptrdiff_t positionY = 0x8; //0x30;
	constexpr std::ptrdiff_t positionZ = 0xC; //0x28;

	constexpr std::ptrdiff_t headPositionX = 0x4;
	constexpr std::ptrdiff_t headPositionY = 0xC;
	constexpr std::ptrdiff_t headPositionZ = 0x8;

	constexpr std::ptrdiff_t playerCameraX = 0x34;
	constexpr std::ptrdiff_t playerCameraY = 0x38 ;

	constexpr std::ptrdiff_t healthValue = 0xEC;
	constexpr std::ptrdiff_t flagTeam = 0x30C;

	

}
