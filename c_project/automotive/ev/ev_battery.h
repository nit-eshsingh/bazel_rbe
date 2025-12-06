#ifndef EV_BATTERY_H
#define EV_BATTERY_H

typedef enum {
    BATTERY_CHARGING,
    BATTERY_DISCHARGING,
    BATTERY_IDLE,
    BATTERY_FAULT
} BatteryStatus;

typedef struct {
    float capacity_kwh;           // Total capacity
    float current_charge_kwh;     // Current charge level
    float voltage;                // Operating voltage
    float temperature_celsius;    // Battery temperature
    int charge_cycles;            // Number of charge cycles
    int health_percentage;        // Battery health (100% = new)
    BatteryStatus status;
} EVBattery;

// EV Battery operations
EVBattery* ev_battery_create(float capacity_kwh, float voltage);
void ev_battery_destroy(EVBattery* battery);
void ev_battery_charge(EVBattery* battery, float kwh);
float ev_battery_discharge(EVBattery* battery, float kwh_requested);
float ev_battery_get_soc(EVBattery* battery);  // State of Charge %
float ev_battery_get_range_km(EVBattery* battery, float efficiency_kwh_per_100km);
int ev_battery_needs_replacement(EVBattery* battery);
void ev_battery_print_status(EVBattery* battery);

#endif // EV_BATTERY_H
