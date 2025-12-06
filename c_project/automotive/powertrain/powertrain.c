#include "powertrain.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Powertrain* powertrain_create(EngineType type) {
    Powertrain* powertrain = (Powertrain*)malloc(sizeof(Powertrain));
    powertrain->engine_type = type;
    powertrain->state = POWERTRAIN_OFF;
    powertrain->rpm = 0.0f;
    powertrain->torque_nm = 0.0f;
    powertrain->power_kw = 0.0f;
    powertrain->fuel_consumption = 0.0f;
    powertrain->temperature_celsius = 20;
    return powertrain;
}

void powertrain_destroy(Powertrain* powertrain) {
    if (powertrain) {
        free(powertrain);
    }
}

void powertrain_start(Powertrain* powertrain) {
    if (!powertrain) return;
    
    powertrain->state = POWERTRAIN_IDLE;
    
    switch (powertrain->engine_type) {
        case ENGINE_ICE:
            powertrain->rpm = 800.0f;  // Idle RPM for ICE
            break;
        case ENGINE_HYBRID:
            powertrain->rpm = 600.0f;
            break;
        case ENGINE_ELECTRIC:
            powertrain->rpm = 0.0f;  // Electric motors don't idle
            break;
    }
    
    powertrain->temperature_celsius = 60;
}

void powertrain_stop(Powertrain* powertrain) {
    if (!powertrain) return;
    
    powertrain->state = POWERTRAIN_OFF;
    powertrain->rpm = 0.0f;
    powertrain->torque_nm = 0.0f;
    powertrain->power_kw = 0.0f;
    powertrain->fuel_consumption = 0.0f;
}

void powertrain_set_throttle(Powertrain* powertrain, float throttle_percent) {
    if (!powertrain || powertrain->state == POWERTRAIN_OFF) return;
    
    if (throttle_percent < 0.0f) throttle_percent = 0.0f;
    if (throttle_percent > 100.0f) throttle_percent = 100.0f;
    
    // Update state based on throttle
    if (throttle_percent == 0.0f) {
        powertrain->state = POWERTRAIN_IDLE;
    } else if (throttle_percent >= 90.0f) {
        powertrain->state = POWERTRAIN_MAX_POWER;
    } else {
        powertrain->state = POWERTRAIN_RUNNING;
    }
    
    // Calculate RPM, torque, and power based on engine type
    switch (powertrain->engine_type) {
        case ENGINE_ICE:
            powertrain->rpm = 800.0f + (throttle_percent * 60.0f);  // Up to 6800 RPM
            powertrain->torque_nm = 150.0f + (throttle_percent * 2.0f);
            powertrain->fuel_consumption = 0.5f + (throttle_percent * 0.15f);
            break;
            
        case ENGINE_HYBRID:
            powertrain->rpm = 600.0f + (throttle_percent * 50.0f);
            powertrain->torque_nm = 180.0f + (throttle_percent * 2.5f);
            powertrain->fuel_consumption = 0.3f + (throttle_percent * 0.10f);
            break;
            
        case ENGINE_ELECTRIC:
            powertrain->rpm = throttle_percent * 120.0f;  // Up to 12000 RPM
            powertrain->torque_nm = 250.0f + (throttle_percent * 1.5f);  // Instant torque
            powertrain->fuel_consumption = throttle_percent * 0.8f;  // kWh
            break;
    }
    
    powertrain->power_kw = powertrain_calculate_power(powertrain->torque_nm, powertrain->rpm);
    
    // Temperature increases with load
    powertrain->temperature_celsius = 60 + (int)(throttle_percent * 0.5f);
    if (powertrain->temperature_celsius > 110) {
        powertrain->temperature_celsius = 110;
    }
}

float powertrain_calculate_power(float torque_nm, float rpm) {
    // Power (kW) = (Torque * RPM) / 9549
    if (rpm == 0.0f) return 0.0f;
    return (torque_nm * rpm) / 9549.0f;
}

void powertrain_print_status(Powertrain* powertrain) {
    if (!powertrain) return;
    
    printf("Powertrain Status:\n");
    printf("  Engine Type: ");
    switch (powertrain->engine_type) {
        case ENGINE_ICE: printf("Internal Combustion\n"); break;
        case ENGINE_HYBRID: printf("Hybrid\n"); break;
        case ENGINE_ELECTRIC: printf("Electric\n"); break;
    }
    printf("  State: ");
    switch (powertrain->state) {
        case POWERTRAIN_OFF: printf("Off\n"); break;
        case POWERTRAIN_IDLE: printf("Idle\n"); break;
        case POWERTRAIN_RUNNING: printf("Running\n"); break;
        case POWERTRAIN_MAX_POWER: printf("Max Power\n"); break;
    }
    printf("  RPM: %.0f\n", powertrain->rpm);
    printf("  Torque: %.1f Nm\n", powertrain->torque_nm);
    printf("  Power: %.1f kW (%.1f HP)\n", powertrain->power_kw, powertrain->power_kw * 1.341f);
    printf("  Fuel/Energy: %.2f %s\n", 
           powertrain->fuel_consumption,
           powertrain->engine_type == ENGINE_ELECTRIC ? "kWh" : "L/h");
    printf("  Temperature: %d°C\n", powertrain->temperature_celsius);
}
