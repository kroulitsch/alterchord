#ifndef UTILS_H
#define UTILS_H

typedef enum {C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B} Tone;

typedef struct string_t {
    int id;
    Tone tuning;
} String;

typedef struct guitar_t {
    String **strings;
} Guitar;

#endif