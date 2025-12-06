#include <stdio.h>
#include <stdlib.h>
#include "c_project/automotive/clutch/clutch.h"
#include "c_project/automotive/brake/brake.h"
#include "c_project/automotive/gear/gear.h"
#include "c_project/automotive/ev/ev_battery.h"
#include "c_project/automotive/powertrain/powertrain.h"

void simulate_ice_vehicle() {
    printf("\n========================================\n");
    printf("Simulating ICE Vehicle\n");
    printf("========================================\n\n");
    
    // Create components
    Powertrain* engine = powertrain_create(ENGINE_ICE);
    Clutch* clutch = clutch_create(1);  // Hydraulic clutch
    Gearbox* gearbox = gearbox_create(TRANSMISSION_MANUAL);
    Brake* brake = brake_create(1);  // With ABS
    
    // Start the vehicle
    printf("--- Starting Engine ---\n");
    powertrain_start(engine);
    powertrain_print_status(engine);
    
    // Engage clutch and shift to first gear
    printf("\n--- Engaging Clutch and Shifting to 1st Gear ---\n");
    clutch_engage(clutch, 100.0f);
    gearbox_shift_to(gearbox, GEAR_1);
    clutch_print_status(clutch);
    gearbox_print_status(gearbox);
    
    // Accelerate
    printf("\n--- Accelerating (50%% Throttle) ---\n");
    powertrain_set_throttle(engine, 50.0f);
    powertrain_print_status(engine);
    
    // Shift to 3rd gear
    printf("\n--- Shifting to 3rd Gear ---\n");
    clutch_disengage(clutch);
    gearbox_shift_to(gearbox, GEAR_3);
    clutch_engage(clutch, 100.0f);
    gearbox_print_status(gearbox);
    
    // Apply brakes
    printf("\n--- Applying Brakes ---\n");
    brake_apply(brake, 60.0f);
    brake_activate_abs(brake);
    brake_print_status(brake);
    
    // Cleanup
    powertrain_destroy(engine);
    clutch_destroy(clutch);
    gearbox_destroy(gearbox);
    brake_destroy(brake);
}

void simulate_ev_vehicle() {
    printf("\n========================================\n");
    printf("Simulating Electric Vehicle (EV)\n");
    printf("========================================\n\n");
    
    // Create EV components
    Powertrain* motor = powertrain_create(ENGINE_ELECTRIC);
    EVBattery* battery = ev_battery_create(75.0f, 400.0f);  // 75 kWh, 400V
    Gearbox* gearbox = gearbox_create(TRANSMISSION_AUTOMATIC);
    Brake* brake = brake_create(1);
    
    // Display initial battery status
    printf("--- Initial Battery Status ---\n");
    ev_battery_print_status(battery);
    
    // Start the motor
    printf("\n--- Starting Electric Motor ---\n");
    powertrain_start(motor);
    gearbox_shift_to(gearbox, GEAR_DRIVE);
    powertrain_print_status(motor);
    gearbox_print_status(gearbox);
    
    // Accelerate (consuming battery)
    printf("\n--- Accelerating (70%% Throttle) ---\n");
    powertrain_set_throttle(motor, 70.0f);
    ev_battery_discharge(battery, 5.0f);  // Consume 5 kWh
    powertrain_print_status(motor);
    ev_battery_print_status(battery);
    
    // Regenerative braking
    printf("\n--- Regenerative Braking ---\n");
    brake_apply(brake, 40.0f);
    ev_battery_charge(battery, 1.5f);  // Recover 1.5 kWh
    brake_print_status(brake);
    ev_battery_print_status(battery);
    
    // Cleanup
    powertrain_destroy(motor);
    ev_battery_destroy(battery);
    gearbox_destroy(gearbox);
    brake_destroy(brake);
}

void simulate_hybrid_vehicle() {
    printf("\n========================================\n");
    printf("Simulating Hybrid Vehicle\n");
    printf("========================================\n\n");
    
    // Create hybrid components
    Powertrain* hybrid_engine = powertrain_create(ENGINE_HYBRID);
    EVBattery* battery = ev_battery_create(20.0f, 300.0f);  // Smaller 20 kWh battery
    Gearbox* gearbox = gearbox_create(TRANSMISSION_CVT);
    Brake* brake = brake_create(1);
    
    printf("--- Hybrid System Status ---\n");
    powertrain_start(hybrid_engine);
    gearbox_shift_to(gearbox, GEAR_DRIVE);
    powertrain_print_status(hybrid_engine);
    ev_battery_print_status(battery);
    gearbox_print_status(gearbox);
    
    // City driving (electric mode)
    printf("\n--- City Driving (Electric Mode) ---\n");
    powertrain_set_throttle(hybrid_engine, 30.0f);
    ev_battery_discharge(battery, 2.0f);
    powertrain_print_status(hybrid_engine);
    
    // Highway driving (ICE + Electric)
    printf("\n--- Highway Driving (Hybrid Mode) ---\n");
    powertrain_set_throttle(hybrid_engine, 80.0f);
    ev_battery_charge(battery, 1.0f);  // Charging while driving
    powertrain_print_status(hybrid_engine);
    ev_battery_print_status(battery);
    
    // Cleanup
    powertrain_destroy(hybrid_engine);
    ev_battery_destroy(battery);
    gearbox_destroy(gearbox);
    brake_destroy(brake);
}

int main() {
    printf("=========================================\n");
    printf("Automotive Systems Simulation\n");
    printf("=========================================\n");
    
    // Run all simulations
    simulate_ice_vehicle();
    simulate_ev_vehicle();
    simulate_hybrid_vehicle();
    
    printf("\n=========================================\n");
    printf("Simulation Complete\n");
    printf("=========================================\n");
    
    return 0;
}
