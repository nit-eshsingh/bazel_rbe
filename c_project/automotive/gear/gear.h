#ifndef GEAR_H
#define GEAR_H

typedef enum {
    GEAR_PARK,
    GEAR_REVERSE,
    GEAR_NEUTRAL,
    GEAR_DRIVE,
    GEAR_1,
    GEAR_2,
    GEAR_3,
    GEAR_4,
    GEAR_5,
    GEAR_6
} GearPosition;

typedef enum {
    TRANSMISSION_MANUAL,
    TRANSMISSION_AUTOMATIC,
    TRANSMISSION_CVT,
    TRANSMISSION_DCT  // Dual Clutch
} TransmissionType;

typedef struct {
    GearPosition current_gear;
    TransmissionType transmission_type;
    float gear_ratio;
    int is_shifting;
} Gearbox;

// Gearbox operations
Gearbox* gearbox_create(TransmissionType type);
void gearbox_destroy(Gearbox* gearbox);
int gearbox_shift_to(Gearbox* gearbox, GearPosition target_gear);
void gearbox_shift_up(Gearbox* gearbox);
void gearbox_shift_down(Gearbox* gearbox);
float gearbox_get_ratio(GearPosition gear);
const char* gearbox_get_gear_name(GearPosition gear);
void gearbox_print_status(Gearbox* gearbox);

#endif // GEAR_H
