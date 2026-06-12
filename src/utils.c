#include "utils.h"
#include <stdlib.h>

/**
 * @brief This function is used to create a `Tuning` with a given `stringCount` and `tuning`
 * @param stringCount number of strings to use
 * @param tuning Tuning of each string
 * @returns Pointer to a created string
 */
Tuning *createTuning(int stringCount, Tone *tuning) {
    Tuning *t = malloc(sizeof(Tuning));
    t->stringCount = stringCount;
    t->strings = malloc(stringCount * sizeof(String));

    for(int i = 0; i < stringCount; i++) {
        t->strings[i].id = i;
        t->strings[i].tuning = tuning[i];
    }

    return t;
}

/**
 * @brief This function correctly frees the tuning
 * @param s Tuning to be freed
 */
void freeTuning(Tuning *t) {
    free(t->strings);

    free(t);
}

/**
 * @brief This function creates a chord type, assigns its kind and the intervals composing the chord
 * @param kind Kind of the chord
 * @param intervalCount Number of different intervals
 * @param intervals Number array of distances from the root note
 */
ChordType createChordType(ChordKind kind, int intervalCount, int *intervals) {
    ChordType type;
    type.kind = kind;
    type.intervalCount = intervalCount;
    for (int i = 0; i < intervalCount && i < MAX_CHORD_INTERVALS; i++) {
        type.intervals[i] = intervals[i];
    }

    return type;
}

Chord createChord(Tone root, ChordKind kind) {
    Chord chord;
    chord.kind = kind;
    chord.root = root;

    return chord;
}