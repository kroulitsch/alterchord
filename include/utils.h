#ifndef UTILS_H
#define UTILS_H

#define TONES_COUNT 12

typedef enum {C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B, NO_TONE} Tone;
extern char *toneNames[TONES_COUNT];

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
    int intervals[TONES_COUNT];
} ChordType;

typedef struct chord_t {
    Tone root;
    ChordKind kind;
} Chord;

Tuning createTuning(int stringCount, char *tuning);
void freeTuning(Tuning t);

ChordType createChordType(ChordKind kind, int intervalCount, int *intervals);
Chord createChord(Tone root, ChordKind kind);

char *toneToStr(Tone t);
Tone strToTone(char *str);

#endif