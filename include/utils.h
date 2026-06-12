#ifndef UTILS_H
#define UTILS_H

typedef enum {C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B} Tone;

typedef struct string_t {
    int id;
    Tone tuning;
} String;

typedef struct tuning_t {
    int stringCount;
    String **strings;
} Tuning;

String *createString(int id, Tone tone);
void freeString(String *s);

Tuning *createTuning(int stringCount, Tone *tuning);
void freeTuning(Tuning *t);

#endif