#include "clutch.h"
#include <stdlib.h>
#include <stdio.h>

Clutch* clutch_create(int is_hydraulic) {
    Clutch* clutch = (Clutch*)malloc(sizeof(Clutch));
    clutch->state = CLUTCH_DISENGAGED;
    clutch->engagement_percentage = 0.0f;
    clutch->wear_level = 0;
    clutch->is_hydraulic = is_hydraulic;
    return clutch;
}

void clutch_destroy(Clutch* clutch) {
    if (clutch) {
        free(clutch);
    }
}

void clutch_engage(Clutch* clutch, float percentage) {
    if (!clutch) return;
    
    if (percentage < 0.0f) percentage = 0.0f;
    if (percentage > 100.0f) percentage = 100.0f;
    
    clutch->engagement_percentage = percentage;
    
    if (percentage == 0.0f) {
        clutch->state = CLUTCH_DISENGAGED;
    } else if (percentage == 100.0f) {
        clutch->state = CLUTCH_ENGAGED;
    } else {
        clutch->state = CLUTCH_SLIPPING;
    }
    
    // Simulate wear - slipping causes more wear
    if (clutch->state == CLUTCH_SLIPPING && clutch->wear_level < 100) {
        clutch->wear_level++;
    }
}

void clutch_disengage(Clutch* clutch) {
    if (!clutch) return;
    clutch->engagement_percentage = 0.0f;
    clutch->state = CLUTCH_DISENGAGED;
}

ClutchState clutch_get_state(Clutch* clutch) {
    return clutch ? clutch->state : CLUTCH_DISENGAGED;
}

int clutch_needs_replacement(Clutch* clutch) {
    return clutch && clutch->wear_level >= 80;
}

void clutch_print_status(Clutch* clutch) {
    if (!clutch) return;
    
    printf("Clutch Status:\n");
    printf("  Type: %s\n", clutch->is_hydraulic ? "Hydraulic" : "Cable");
    printf("  State: ");
    switch (clutch->state) {
        case CLUTCH_DISENGAGED: printf("Disengaged\n"); break;
        case CLUTCH_ENGAGED: printf("Engaged\n"); break;
        case CLUTCH_SLIPPING: printf("Slipping\n"); break;
    }
    printf("  Engagement: %.1f%%\n", clutch->engagement_percentage);
    printf("  Wear Level: %d%%\n", clutch->wear_level);
}
