#ifndef UTILS_H
#define UTILS_H

#define MAX_CHORD_INTERVALS 12

typedef enum {C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B} Tone;

typedef enum {MAJ, MIN, DIM, AUG, MAJ7, MIN7, SUS2, SUS4, CHORD_KIND_SIZE} ChordKind;

typedef struct string_t {
    int id;
    Tone tuning;
} String;

typedef struct tuning_t {
    int stringCount;
    String *strings;
} Tuning;

typedef struct chord_type_t {
    ChordKind kind;
    int intervalCount;
    int intervals[MAX_CHORD_INTERVALS];
} ChordType;

typedef struct chord_t {
    Tone root;
    ChordKind kind;
} Chord;

Tuning *createTuning(int stringCount, Tone *tuning);
void freeTuning(Tuning *t);

ChordType createChordType(ChordKind kind, int intervalCount, int *intervals);

Chord createChord(Tone root, ChordKind kind);

#endif