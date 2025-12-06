#include "brake.h"
#include <stdlib.h>
#include <stdio.h>

Brake* brake_create(int has_abs) {
    Brake* brake = (Brake*)malloc(sizeof(Brake));
    brake->state = BRAKE_RELEASED;
    brake->brake_pressure = 0.0f;
    brake->pad_thickness_mm = 12;  // New pads
    brake->has_abs = has_abs;
    brake->temperature_celsius = 20;
    return brake;
}

void brake_destroy(Brake* brake) {
    if (brake) {
        free(brake);
    }
}

void brake_apply(Brake* brake, float pressure) {
    if (!brake) return;
    
    if (pressure < 0.0f) pressure = 0.0f;
    if (pressure > 100.0f) pressure = 100.0f;
    
    brake->brake_pressure = pressure;
    
    if (pressure == 0.0f) {
        brake->state = BRAKE_RELEASED;
        brake->temperature_celsius -= 5;
        if (brake->temperature_celsius < 20) brake->temperature_celsius = 20;
    } else {
        brake->state = BRAKE_APPLIED;
        // Heat increases with braking
        brake->temperature_celsius += (int)(pressure / 10);
        if (brake->temperature_celsius > 400) brake->temperature_celsius = 400;
        
        // Wear down pads
        if (brake->pad_thickness_mm > 0) {
            brake->pad_thickness_mm -= (pressure > 80.0f) ? 1 : 0;
        }
    }
}

void brake_release(Brake* brake) {
    if (!brake) return;
    brake->brake_pressure = 0.0f;
    brake->state = BRAKE_RELEASED;
}

void brake_activate_abs(Brake* brake) {
    if (!brake || !brake->has_abs) return;
    if (brake->state == BRAKE_APPLIED) {
        brake->state = BRAKE_ABS_ACTIVE;
    }
}

int brake_pads_need_replacement(Brake* brake) {
    return brake && brake->pad_thickness_mm <= 3;
}

void brake_print_status(Brake* brake) {
    if (!brake) return;
    
    printf("Brake Status:\n");
    printf("  ABS: %s\n", brake->has_abs ? "Enabled" : "Disabled");
    printf("  State: ");
    switch (brake->state) {
        case BRAKE_RELEASED: printf("Released\n"); break;
        case BRAKE_APPLIED: printf("Applied\n"); break;
        case BRAKE_ABS_ACTIVE: printf("ABS Active\n"); break;
    }
    printf("  Pressure: %.1f bar\n", brake->brake_pressure);
    printf("  Pad Thickness: %d mm\n", brake->pad_thickness_mm);
    printf("  Temperature: %d°C\n", brake->temperature_celsius);
}
