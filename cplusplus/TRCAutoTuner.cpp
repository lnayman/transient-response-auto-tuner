// TRCAutoTuner.cpp :
//

#include <iostream>
#include <complex>
#include <iomanip>
#include <cmath>
#include <map>
#include <string>
#include <algorithm>
#include <conio.h> //getch
#include "TRCAutoTuner.h"

// requires c++ 11
std::map<std::string, double> shuntResistanceForIRange = {
	{"kIRange1uA", 499.0e3},
	{"kIRange10uA", 49.9e3},
	{"kIRange100uA", 4.99 + 48.83 + 499.0 + 4.99e3},
	{"kIRange1mA", 4.99 + 48.83 + 499.0},
	{"kIRange10mA", 4.99 + 48.83},
	{"kIRange100mA", 4.99},
	{"kIRange3A",0.00}
};

// requires c++ 11
std::map<int, std::string> IRangeStringForIndex = {
	{1, "kIRange1uA"},
	{2, "kIRange10uA"},
	{3, "kIRange100uA"},
	{4, "kIRange1mA"},
	{5, "kIRange10mA"},
	{6, "kIRange100mA"},
	{7, "kIRange3A"}
};

double getOutputResistanceForCurrentRange(int currentRangeIndex)
{
	constexpr double powerStageOutputRInOhms = 0.280;
	constexpr double threeAmpShuntValueInOhms = 50.0e-3;
	std::string IRangeString = IRangeStringForIndex[currentRangeIndex];
	double shuntResistance = shuntResistanceForIRange[IRangeString];
	return shuntResistance + powerStageOutputRInOhms + threeAmpShuntValueInOhms;
}
	

int main()
{
	char c;
	std::cout << "Transient Response Auto Tuner\n";
	std::cout << "press ESC to exit or Enter to continue! " << "\n";
	while (true)
	{
		c = _getch();
		if (c == 27) //ESC key
			break;
	
		int currentRangeIndex = 0;
		std::cout << "\n";
		std::cout << "Select current range: (typically driver would have this)\n";
		std::cout << "1. 1uA range\n";
		std::cout << "2. 10uA range\n";
		std::cout << "3. 100uA range\n";
		std::cout << "4. 1mA range\n";
		std::cout << "5. 10mA range\n";
		std::cout << "6. 100mA range\n";
		std::cout << "7. 3A range\n";
		std::cin >> currentRangeIndex;
		double outputR = getOutputResistanceForCurrentRange(currentRangeIndex);
		std::cout << "Output Resistance (ohms): " << outputR << "\n";
		std::cin.ignore(); //this swallows the new line above

		// Ask user for their voltage GBW optionally
		double voltageGBW = 10e3;
		double scaledGBW = 0.0;
		std::string voltageGBWStr = "";
		char* unitsForVoltageGBW;
		std::cout << "Specify Voltage GBW [default = " << voltageGBW << "]: ";

		std::getline(std::cin, voltageGBWStr);
		if (voltageGBWStr.empty())
		{
			scaledGBW = voltageGBW;
		}
		else
		{
			voltageGBW = strtod(voltageGBWStr.c_str(), &unitsForVoltageGBW);
			scaledGBW = getScaledVoltageGainBandwidth(voltageGBW, unitsForVoltageGBW);
		}
		
		std::cout << "Total Voltage GBW Value = " << scaledGBW << "\n";
		
		// Ask for their capacitive DUT value
		double capValue = 1e-6;
		double scaledCapValue = 0.0;
		std::string capStr = "";
		char* unitsForCap;
		std::cout << "Specify your capacitor Value [default = " << capValue << "]: ";

		std::getline(std::cin, capStr);

		if (capStr.empty())
		{
			scaledCapValue = capValue;
		}
		else
		{
			capValue = strtod(capStr.c_str(), &unitsForCap);
			scaledCapValue = getScaledCapValue(capValue, unitsForCap);
		}

		std::cout << "Total Capacitor Value = " << scaledCapValue << "\n";

		// perform the math and output the coefficients
		double PI = std::acos(-1);
		constexpr double flexLoopDelay = 1e-6;
		constexpr int maxPoleZeroRatio = 8;
		double sqrtOfMaxPZR = std::sqrt(maxPoleZeroRatio);
		double poleAddedByCapacitor = 1 / (2 * PI * ((outputR * scaledCapValue) + flexLoopDelay));

		std::cout << "Pole added by capacitor = " << poleAddedByCapacitor << "\n";

		double provisionalZero = std::fmax(poleAddedByCapacitor,
			std::sqrt(scaledGBW * poleAddedByCapacitor / sqrtOfMaxPZR));
		double Fp = std::fmin(provisionalZero * maxPoleZeroRatio, scaledGBW * 4);
		double Fz = std::fmin(provisionalZero, Fp * maxPoleZeroRatio);
		double compFrequency = std::sqrt(Fp * Fz);
		double poleZeroRatio = Fp / Fz;

		std::cout << "===================================" << "\n";
		std::cout << "Your Coefficients are as follows:" << "\n";
		std::cout << "===================================" << "\n";
		std::cout << "Voltage Gain Bandwidth: " << scaledGBW << "\n";
		std::cout << "Voltage Compensation Frequency: " << compFrequency << "\n";
		std::cout << "Voltage Pole Zero Ratio: " << poleZeroRatio << "\n";
		std::cout << "press esc to exit or enter to do it again! " << "\n";
	}

	std::cout << "exited: " << "\n";

}
