#include "ev_battery.h"
#include <stdlib.h>
#include <stdio.h>

EVBattery* ev_battery_create(float capacity_kwh, float voltage) {
    EVBattery* battery = (EVBattery*)malloc(sizeof(EVBattery));
    battery->capacity_kwh = capacity_kwh;
    battery->current_charge_kwh = capacity_kwh * 0.8f;  // 80% initial charge
    battery->voltage = voltage;
    battery->temperature_celsius = 25.0f;
    battery->charge_cycles = 0;
    battery->health_percentage = 100;
    battery->status = BATTERY_IDLE;
    return battery;
}

void ev_battery_destroy(EVBattery* battery) {
    if (battery) {
        free(battery);
    }
}

void ev_battery_charge(EVBattery* battery, float kwh) {
    if (!battery || kwh <= 0) return;
    
    battery->status = BATTERY_CHARGING;
    battery->current_charge_kwh += kwh;
    
    if (battery->current_charge_kwh > battery->capacity_kwh) {
        battery->current_charge_kwh = battery->capacity_kwh;
    }
    
    // Charging heats up the battery
    battery->temperature_celsius += 2.0f;
    if (battery->temperature_celsius > 45.0f) {
        battery->temperature_celsius = 45.0f;
    }
    
    // Track charge cycles (every full charge)
    if (battery->current_charge_kwh >= battery->capacity_kwh * 0.95f) {
        battery->charge_cycles++;
        // Degrade health over cycles
        if (battery->charge_cycles % 100 == 0 && battery->health_percentage > 70) {
            battery->health_percentage--;
        }
    }
}

float ev_battery_discharge(EVBattery* battery, float kwh_requested) {
    if (!battery || kwh_requested <= 0) return 0.0f;
    
    battery->status = BATTERY_DISCHARGING;
    
    float kwh_available = (kwh_requested < battery->current_charge_kwh) 
                         ? kwh_requested 
                         : battery->current_charge_kwh;
    
    battery->current_charge_kwh -= kwh_available;
    
    // Discharging also generates heat
    battery->temperature_celsius += 1.0f;
    if (battery->temperature_celsius > 40.0f) {
        battery->temperature_celsius = 40.0f;
    }
    
    return kwh_available;
}

float ev_battery_get_soc(EVBattery* battery) {
    if (!battery || battery->capacity_kwh == 0) return 0.0f;
    return (battery->current_charge_kwh / battery->capacity_kwh) * 100.0f;
}

float ev_battery_get_range_km(EVBattery* battery, float efficiency_kwh_per_100km) {
    if (!battery || efficiency_kwh_per_100km == 0) return 0.0f;
    return (battery->current_charge_kwh / efficiency_kwh_per_100km) * 100.0f;
}

int ev_battery_needs_replacement(EVBattery* battery) {
    return battery && battery->health_percentage < 80;
}

void ev_battery_print_status(EVBattery* battery) {
    if (!battery) return;
    
    printf("EV Battery Status:\n");
    printf("  Capacity: %.1f kWh\n", battery->capacity_kwh);
    printf("  Current Charge: %.1f kWh (%.1f%%)\n", 
           battery->current_charge_kwh, ev_battery_get_soc(battery));
    printf("  Voltage: %.1f V\n", battery->voltage);
    printf("  Temperature: %.1f°C\n", battery->temperature_celsius);
    printf("  Health: %d%%\n", battery->health_percentage);
    printf("  Charge Cycles: %d\n", battery->charge_cycles);
    printf("  Status: ");
    switch (battery->status) {
        case BATTERY_CHARGING: printf("Charging\n"); break;
        case BATTERY_DISCHARGING: printf("Discharging\n"); break;
        case BATTERY_IDLE: printf("Idle\n"); break;
        case BATTERY_FAULT: printf("Fault\n"); break;
    }
    printf("  Estimated Range: %.1f km (@ 20kWh/100km)\n", 
           ev_battery_get_range_km(battery, 20.0f));
}
