#include "utils.h"
#include "basics.h"

char *toneNames[TONES_COUNT] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};;

/**
 * @brief This function is used to create a `Tuning` with a given `stringCount` and `tuning`
 * @param stringCount number of strings to use
 * @param tuning Tuning of each string
 * @returns Created tuning
 */
Tuning createTuning(int stringCount, char *tuning) {
    Tuning t;
    t.stringCount = stringCount;
    t.strings = malloc(stringCount * sizeof(String));

    for(int i = 0; i < stringCount; i++) {
        t.strings[i].id = i;
        t.strings[i].tuning = NO_TONE;
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

    generateBasics();

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
 * @returns Created chord type
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
 * @brief This function is used to get a chord type based on its `kind`
 * @param kind Chord kind
 * @returns Correspondent chord type
 */
ChordType getChordType(ChordKind kind) {
    for(int i = 1; i < CHORD_KIND_SIZE; i++) {
        if(basics_arr[i].kind == kind) {
            return basics_arr[i];
        }
    }

    return basics_arr[NO_CHORD_KIND];
}

/**
 * @brief This function creates a chord based on the `root` note and chord `kind`
 * @example createChord(F, MAJ7) creates a Fmaj7 chord
 * @param root Root note of the chord
 * @param kind Chord kind
 * @returns Created chord
 */
Chord createChord(Tone root, ChordKind kind) {
    Chord chord;
    chord.kind = kind;
    chord.root = root;
    chord.type = getChordType(kind);
    chord.tonesCount = chord.type.intervalCount;

    for(int i = 0; i < chord.tonesCount; i++) {
        chord.tones[i] = (Tone)((chord.root + chord.type.intervals[i]) % TONES_COUNT);
    }

    return chord;
}

/**
 * @brief This function converts `Tone` instance to a human readable string
 * @param t Tone to be converted
 * @returns Converted string
 */
char *toneToStr(Tone t) {
    if(t == NO_TONE) {
        return "(No tone)";
    }
    return toneNames[t];
}

/**
 * @brief This function converts string tone name to a `Tone` instance
 * @param str String to be converted
 * @returns Converted tone
 */
Tone strToTone(char *str) {
    if(strcmp("(No tone)", str) == 0) {
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

char *chordToStr(Chord c, char *buff) {
    buff[0] = '\0';
    if(c.tonesCount == 0) {
        strcat(buff, "(No chord)");
    }

    for(int i = 0; i < c.tonesCount; i++) {
        strcat(buff, toneToStr(c.tones[i]));
        if (i < c.tonesCount - 1) {
            strcat(buff, " ");
        }
    }

    return buff;
}