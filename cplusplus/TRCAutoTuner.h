#pragma once

#include <iostream>
#include <complex>
#include <iomanip>
#include <cmath>
#include <map>
#include <string>
#include <algorithm>

// Accepts a numerical value with certain siPrefix and returns scaled value in Farads
inline double getScaledCapValue(double capacitorValue, char* siPrefixPiece)
{
	std::string siPrefix = siPrefixPiece;

	//trim the white spaces for cases like "10 uF" or "10   uF"
	siPrefix.erase(std::remove_if(siPrefix.begin(), siPrefix.end(), isspace), siPrefix.end());

	//check the first letter to see units. this allows for 10 pico or 10pF format
	if (siPrefix.at(0) == 'p')
	{
		return capacitorValue * 1e-12;
	}
	else if (siPrefix.at(0) == 'n')
	{
		return capacitorValue * 1e-9;
	}
	else if (siPrefix.at(0) == 'u')
	{
		return capacitorValue * 1e-6;
	}
	else if (siPrefix.at(0) == 'm')
	{
		return capacitorValue * 1e-3;
	}
	else
	{
		return capacitorValue;
	}
}

// Accepts a numerical value with certain siPrefix and returns scaled value in Hertz
inline double getScaledVoltageGainBandwidth(double voltageGainBandwidth, char* siPrefixPiece)
{
	std::string siPrefix = siPrefixPiece;

	//trim the white spaces for cases like "10 kH" or "10   M"
	siPrefix.erase(std::remove_if(siPrefix.begin(), siPrefix.end(), isspace), siPrefix.end());

	if (siPrefix.at(0) == 'k')
	{
		return voltageGainBandwidth * 1e3;
	}
	else if (siPrefix.at(0) == 'M')
	{
		return voltageGainBandwidth * 1e6;
	}
	else
	{
		return voltageGainBandwidth;
	}
}

