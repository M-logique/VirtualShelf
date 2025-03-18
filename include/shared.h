// shared.h
#ifndef SHARED_H
#define SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

extern int rgb_enabled;  // Shared variable

int is_rgb_enabled();
void toggle_rgb();
const char** get_book_values(int* size, int check_av);
const char** get_student_values(int* size);
void free_values(const char** values, int size);

#ifdef __cplusplus
}
#endif

#endif // SHARED_H
