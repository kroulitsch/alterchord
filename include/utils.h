#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

#define TONES_COUNT 12
#define MAX_FRET 30

typedef enum {C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B, NO_TONE} Tone;
extern char *toneNames[TONES_COUNT];

typedef enum {NO_CHORD_KIND, MAJ, MIN, DIM, AUG, MAJ7, MIN7, SUS2, SUS4, CHORD_KIND_SIZE} ChordKind;
extern char *chordKindNames[CHORD_KIND_SIZE];

typedef struct tuning_t {
    int stringCount;
    Tone *strings;
    int fretCount;
} Tuning;

typedef struct chord_type_t {
    ChordKind kind;
    int intervalCount;
    int intervals[TONES_COUNT];
} ChordType;

typedef struct chord_t {
    Tone root;
    ChordKind kind;
    int tonesCount;
    Tone tones[TONES_COUNT];
} Chord;

typedef struct shape_t {
    Tuning tuning;
    Chord chord;
    int *frets;
} Shape;

Tuning createTuning(int stringCount, char *tuning);
void freeTuning(Tuning t);

ChordType createChordType(ChordKind kind, int intervalCount, int *intervals);
ChordType getChordType(ChordKind kind);
Chord createChord(char *name);

void freeShape(Shape s);

char *toneToStr(Tone t);
Tone strToTone(char *str);
char *chordToStr(Chord c, char *buff);
ChordKind strToChordKind(char *str);

#endif