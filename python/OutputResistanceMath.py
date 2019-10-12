IRangeStringForIndex = {
    1: "kIRange1uA",
    2: "kIRange10uA",
    3: "kIRange100uA",
    4: "kIRange1mA",
    5: "kIRange10mA",
    6: "kIRange100mA",
    7: "kIRange3A"
}

shuntResistanceForIRange = {
    "kIRange1uA": 499.0e3,
    "kIRange10uA": 49.9e3,
    "kIRange100uA": 4.99 + 48.83 + 499.0 + 4.99e3,
    "kIRange1mA": 4.99 + 48.83 + 499.0,
    "kIRange10mA": 4.99 + 48.83,
    "kIRange100mA": 4.99,
    "kIRange3A": 0.00
}


def get_output_resistance_for_current_range():
    print('1. 1uA range')
    print('2. 10uA range')
    print('3. 100uA range')
    print('4. 1mA range')
    print('5. 10mA range')
    print('6. 100mA range')
    print('7. 3A range')
    current_range = input('Enter current range index: ')
    power_stage_output_r_in_ohms = 0.280
    three_amp_shunt_value_in_ohms = 50.0e-3
    i_range_string = IRangeStringForIndex[int(current_range)]
    shunt_resistance = shuntResistanceForIRange[str(i_range_string)]
    print(shunt_resistance + power_stage_output_r_in_ohms + three_amp_shunt_value_in_ohms)
    return shunt_resistance + power_stage_output_r_in_ohms + three_amp_shunt_value_in_ohms
