# perform the math and output the PID loop coefficients

import math


def calculate_coefficients(output_resistance, voltage_gain_bandwidth, capacitor_value):
    flex_loop_delay = 1e-6
    maximum_pole_zero_ratio = 8
    maxpzr_square = math.sqrt(maximum_pole_zero_ratio)
    pole_added_by_cap = 1 / (2 * math.pi * ((output_resistance * capacitor_value) + flex_loop_delay))

    print('Pole added by capacitor = ', pole_added_by_cap)

    provisional_zero = max(pole_added_by_cap, math.sqrt(voltage_gain_bandwidth * pole_added_by_cap / maxpzr_square))
    fp = min(provisional_zero * maximum_pole_zero_ratio, voltage_gain_bandwidth * 4)
    fz = min(provisional_zero, fp * maximum_pole_zero_ratio)
    comp_frequency = math.sqrt(fp * fz)
    pole_zero_ratio = fp / fz

    print('===================================')
    print('Your Coefficients are as follows:')
    print('===================================')
    print('Voltage Gain Bandwidth', voltage_gain_bandwidth)
    print('Voltage Compensation Frequency:', comp_frequency)
    print('Voltage Pole Zero Ratio: ', pole_zero_ratio)
    return
