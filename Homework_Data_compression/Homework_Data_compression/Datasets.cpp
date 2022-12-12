#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Datasets.h"

std::string mainDictionary{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

std::string createDatatset(uint16_t size)
{
	std::string dataString;
	uint16_t i = 0;
	while (i < size)
	{
		dataString.resize(i + 2);
		std::uint16_t index = rand() % 35;
		dataString[i] = mainDictionary[index];
		i += 1;
	}

	return dataString;
}

