# transient-response-auto-tuner
algorithm accepts user input capacitor value and returns PID loop coefficients


Problem: 

A typical production test for ICs (e.g. Power Management ICs) will involve sweeping voltage set-points using an Power Supply/Source Measure Unit. "Sweeping voltage set-points" means having a list of voltages and wanting to output them in very quick succession. For each voltage being sourced, there is a test performed to make sure the IC behaves correctly. Customers want to do these sweeps as fast as possible to have faster test times.

The problem occurs when the IC pins being tested are capacitive. The capacitive DUT along with the resistance inside the Power Supply creates a filter. This filter created due to the capacitor may in many cases cause the power supply output to become unstable because the voltage set points are being changed too quickly for the internal controller loop. One solution is to really slow down the loop but then it takes forever to charge the capacitor and your test takes a really long time to run.
NOTE: This is made worse in lower current ranges with bigger capacitor values (i = C dv/dt)

Solution:

The optimal solution is for customers to provide their capacitor value and have the device driver controlling the SMU/Power Supply calculate the PID loop coefficients to allow the loop to run as fast as it possibly can BUT still be stable, providing optimal performance.

This simple console app takes as input a capacitor value and (and optionally a loop rate) and then calculates and returns the coefficients (e.g. loop rate, zero to balance out pole created by DUT, pole to balance out zero, etc.) for the control loop. 

