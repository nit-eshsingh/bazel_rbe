#include "gear.h"
#include <stdlib.h>
#include <stdio.h>

Gearbox* gearbox_create(TransmissionType type) {
    Gearbox* gearbox = (Gearbox*)malloc(sizeof(Gearbox));
    gearbox->transmission_type = type;
    gearbox->current_gear = (type == TRANSMISSION_AUTOMATIC) ? GEAR_PARK : GEAR_NEUTRAL;
    gearbox->gear_ratio = gearbox_get_ratio(gearbox->current_gear);
    gearbox->is_shifting = 0;
    return gearbox;
}

void gearbox_destroy(Gearbox* gearbox) {
    if (gearbox) {
        free(gearbox);
    }
}

int gearbox_shift_to(Gearbox* gearbox, GearPosition target_gear) {
    if (!gearbox) return 0;
    
    // Validate shift based on transmission type
    if (gearbox->transmission_type == TRANSMISSION_AUTOMATIC) {
        if (target_gear >= GEAR_1 && target_gear <= GEAR_6) {
            return 0; // Can't manually select gears in automatic
        }
    }
    
    gearbox->is_shifting = 1;
    gearbox->current_gear = target_gear;
    gearbox->gear_ratio = gearbox_get_ratio(target_gear);
    gearbox->is_shifting = 0;
    
    return 1;
}

void gearbox_shift_up(Gearbox* gearbox) {
    if (!gearbox) return;
    
    if (gearbox->current_gear >= GEAR_1 && gearbox->current_gear < GEAR_6) {
        gearbox->current_gear++;
        gearbox->gear_ratio = gearbox_get_ratio(gearbox->current_gear);
    }
}

void gearbox_shift_down(Gearbox* gearbox) {
    if (!gearbox) return;
    
    if (gearbox->current_gear > GEAR_1 && gearbox->current_gear <= GEAR_6) {
        gearbox->current_gear--;
        gearbox->gear_ratio = gearbox_get_ratio(gearbox->current_gear);
    }
}

float gearbox_get_ratio(GearPosition gear) {
    switch (gear) {
        case GEAR_PARK: return 0.0f;
        case GEAR_REVERSE: return -3.5f;
        case GEAR_NEUTRAL: return 0.0f;
        case GEAR_DRIVE: return 3.5f;
        case GEAR_1: return 3.5f;
        case GEAR_2: return 2.1f;
        case GEAR_3: return 1.4f;
        case GEAR_4: return 1.0f;
        case GEAR_5: return 0.75f;
        case GEAR_6: return 0.6f;
        default: return 0.0f;
    }
}

const char* gearbox_get_gear_name(GearPosition gear) {
    switch (gear) {
        case GEAR_PARK: return "P";
        case GEAR_REVERSE: return "R";
        case GEAR_NEUTRAL: return "N";
        case GEAR_DRIVE: return "D";
        case GEAR_1: return "1";
        case GEAR_2: return "2";
        case GEAR_3: return "3";
        case GEAR_4: return "4";
        case GEAR_5: return "5";
        case GEAR_6: return "6";
        default: return "?";
    }
}

void gearbox_print_status(Gearbox* gearbox) {
    if (!gearbox) return;
    
    printf("Gearbox Status:\n");
    printf("  Type: ");
    switch (gearbox->transmission_type) {
        case TRANSMISSION_MANUAL: printf("Manual\n"); break;
        case TRANSMISSION_AUTOMATIC: printf("Automatic\n"); break;
        case TRANSMISSION_CVT: printf("CVT\n"); break;
        case TRANSMISSION_DCT: printf("Dual Clutch\n"); break;
    }
    printf("  Current Gear: %s\n", gearbox_get_gear_name(gearbox->current_gear));
    printf("  Gear Ratio: %.2f\n", gearbox->gear_ratio);
    printf("  Shifting: %s\n", gearbox->is_shifting ? "Yes" : "No");
}
