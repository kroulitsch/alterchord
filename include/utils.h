#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

#define MAX_FRET 30
#define MUTED -1

typedef enum {C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B, TONES_COUNT, NO_TONE} Tone;
extern char *toneNames[TONES_COUNT];

typedef enum {
    NO_CHORD_KIND,
    MAJ, MIN, DIM, AUG, // basic
    DOM7, MAJ7, MIN7, MINMAJ7, M7B5, DIM7, MAJ6, MIN6,
    DOM7SUS2, DOM7SUS4, MAJ7SUS2, MAJ7SUS4, MIN7SUS4, // six-seven
    DOM9, MAJ9, MIN9, MINMAJ9, M7B5B9, DIM9, DOM7B9, DOM7SHARP9,
    DOM9SUS4, MAJ9SUS4, MIN9SUS4, DOM7B9SUS4, // nine
    DOM11, MAJ11, MIN11, MAJ7_SHARP11, // eleven
    DOM13, MAJ13, MIN13, MINMAJ13, // thirteen
    ADD9, MINADD9, ADD4, // add chords
    SUS2, SUS4, POWER, // special, power
    CHORD_KIND_SIZE
} ChordKind;

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

struct shape_t;

typedef struct shape_t {
    Tuning tuning;
    Chord chord;
    int *frets;
    struct shape_t *prev;
    struct shape_t *next;
} Shape;

Tuning createTuning(int stringCount, char *tuning, int fretCount);
void freeTuning(Tuning t);

ChordType createChordType(ChordKind kind, int intervalCount, int *intervals);
ChordType getChordType(ChordKind kind);
Chord createChord(char *name);

void freeShape(Shape s);
void freeShapesList(Shape *root);

char *toneToStr(Tone t);
Tone strToTone(char *str);
char *chordToStr(Chord c, char *buff);
ChordKind strToChordKind(char *str);

#endif