#include "utils.h"
#include <stdlib.h>
#include <string.h>

char *toneNames[TONES_COUNT] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};;

/**
 * @brief This function is used to create a `Tuning` with a given `stringCount` and `tuning`
 * @param stringCount number of strings to use
 * @param tuning Tuning of each string
 * @returns Pointer to a created string
 */
Tuning createTuning(int stringCount, char *tuning) {
    Tuning t;
    t.stringCount = stringCount;
    t.strings = malloc(stringCount * sizeof(String));

    for(int i = 0; i < stringCount; i++) {
        t.strings[i].id = i;
    }

    int index = 0;
    for(char *c = tuning; c[0] != '\0' && index < stringCount; c++) {
        char tone[3];
        if(c[1] == '#' || c[1] == 'b') {
            tone[0] = c[0];
            tone[1] = c[1];
            tone[2] = '\0';
            c++;
        } else {
            tone[0] = c[0];
            tone[1] = '\0';
        }

        t.strings[index++].tuning = strToTone(tone);
    }

    return t;
}


/**
 * @brief This function correctly frees the tuning
 * @param s Tuning to be freed
 */
void freeTuning(Tuning t) {
    free(t.strings);
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
    for (int i = 0; i < intervalCount; i++) {
        type.intervals[i] = intervals[i];
    }

    return type;
}

/**
 * @brief This function creates a chord based on the `root` note and chord `kind`
 * @example createChord(F, MAJ7) creates a Fmaj7 chord
 * @param root Root note of the chord
 * @param kind Chord kind
 */
Chord createChord(Tone root, ChordKind kind) {
    Chord chord;
    chord.kind = kind;
    chord.root = root;

    return chord;
}

/**
 * @brief This function converts `Tone` instance to a human readable string
 * @param t Tone to be converted
 */
char *toneToStr(Tone t) {
    if(t == NO_TONE) {
        return "NO TONE";
    }
    return toneNames[t];
}

/**
 * @brief This function converts string tone name to a `Tone` instance
 * @param str String to be converted
 */
Tone strToTone(char *str) {
    if(strcmp("NO TONE", str) == 0) {
        return NO_TONE;
    }
    for(int i = 0; i < TONES_COUNT; i++) {
        if(strcmp(toneNames[i], str) == 0) {
            return (Tone)i;
        } else if(str[1] == 'b' && toneNames[i][0] == str[0]) {
            return (Tone)((i - 1 + TONES_COUNT) % TONES_COUNT);
        } else if(str[1] == '#' && toneNames[i][0] == str[0]) {
            return (Tone)((i + 1) % TONES_COUNT);
        }
    }

    return NO_TONE;
}