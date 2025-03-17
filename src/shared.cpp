#include <shared.h>

int rgb_enabled = 1;

int is_rgb_enabled() {
    return rgb_enabled;
}

void toggle_rgb() {
    rgb_enabled = !rgb_enabled; 
}