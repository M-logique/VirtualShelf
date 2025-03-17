// shared.h
#ifndef SHARED_H
#define SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

extern int rgb_enabled;  // Shared variable

int is_rgb_enabled();
void toggle_rgb();


#ifdef __cplusplus
}
#endif

#endif // SHARED_H
