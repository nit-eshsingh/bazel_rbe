#ifndef BRAKE_H
#define BRAKE_H

typedef enum {
    BRAKE_RELEASED,
    BRAKE_APPLIED,
    BRAKE_ABS_ACTIVE
} BrakeState;

typedef struct {
    BrakeState state;
    float brake_pressure;      // 0.0 to 100.0 bar
    int pad_thickness_mm;      // Minimum safe: 3mm
    int has_abs;               // Anti-lock Braking System
    int temperature_celsius;   // Operating temperature
} Brake;

// Brake operations
Brake* brake_create(int has_abs);
void brake_destroy(Brake* brake);
void brake_apply(Brake* brake, float pressure);
void brake_release(Brake* brake);
void brake_activate_abs(Brake* brake);
int brake_pads_need_replacement(Brake* brake);
void brake_print_status(Brake* brake);

#endif // BRAKE_H
