from OutputResistanceMath import get_output_resistance_for_current_range
from CalculateCoefficients import calculate_coefficients
from quantiphy import Quantity
import sys

while True:
    keyPressed = input("Transient Response Auto Tuner. Press Enter to continue or Q to quit ")
    if keyPressed is "Q" or keyPressed is "q":
        sys.exit()
    outputResistance = get_output_resistance_for_current_range()

    voltageGBW = input("Enter voltage Gain Bandwidth or press Enter (default is 10kHz) : ") or 10000
    scaledVoltageGBW = Quantity(voltageGBW)
    print(float(scaledVoltageGBW))

    capacitorValue = input("Enter capacitor value or press Enter (default is 1uF) : ") or 1e-6
    scaledCapacitorValue = Quantity(capacitorValue)
    print(float(scaledCapacitorValue))

    calculate_coefficients(outputResistance, scaledVoltageGBW, scaledCapacitorValue)









