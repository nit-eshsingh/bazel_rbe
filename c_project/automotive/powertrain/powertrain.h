#ifndef POWERTRAIN_H
#define POWERTRAIN_H

typedef enum {
    ENGINE_ICE,        // Internal Combustion Engine
    ENGINE_HYBRID,
    ENGINE_ELECTRIC
} EngineType;

typedef enum {
    POWERTRAIN_OFF,
    POWERTRAIN_IDLE,
    POWERTRAIN_RUNNING,
    POWERTRAIN_MAX_POWER
} PowertrainState;

typedef struct {
    EngineType engine_type;
    PowertrainState state;
    float rpm;                    // Revolutions per minute
    float torque_nm;              // Newton meters
    float power_kw;               // Kilowatts
    float fuel_consumption;       // Liters/hour or kWh for electric
    int temperature_celsius;
} Powertrain;

// Powertrain operations
Powertrain* powertrain_create(EngineType type);
void powertrain_destroy(Powertrain* powertrain);
void powertrain_start(Powertrain* powertrain);
void powertrain_stop(Powertrain* powertrain);
void powertrain_set_throttle(Powertrain* powertrain, float throttle_percent);
float powertrain_calculate_power(float torque_nm, float rpm);
void powertrain_print_status(Powertrain* powertrain);

#endif // POWERTRAIN_H
