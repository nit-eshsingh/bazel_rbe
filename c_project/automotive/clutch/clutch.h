#ifndef CLUTCH_H
#define CLUTCH_H

typedef enum {
    CLUTCH_DISENGAGED,
    CLUTCH_ENGAGED,
    CLUTCH_SLIPPING
} ClutchState;

typedef struct {
    ClutchState state;
    float engagement_percentage;  // 0.0 to 100.0
    int wear_level;               // 0 to 100 (100 = needs replacement)
    int is_hydraulic;             // 1 for hydraulic, 0 for cable
} Clutch;

// Clutch operations
Clutch* clutch_create(int is_hydraulic);
void clutch_destroy(Clutch* clutch);
void clutch_engage(Clutch* clutch, float percentage);
void clutch_disengage(Clutch* clutch);
ClutchState clutch_get_state(Clutch* clutch);
int clutch_needs_replacement(Clutch* clutch);
void clutch_print_status(Clutch* clutch);

#endif // CLUTCH_H
