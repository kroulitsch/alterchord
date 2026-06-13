#include "utils.h"
#include "basics.h"

char *toneNames[TONES_COUNT] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
char *chordKindNames[CHORD_KIND_SIZE] = {"(No chord kind)", "maj", "min", "dim", "aug", "maj7", "min7", "sus2", "sus4"};

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
 * @brief This function correctly frees the tuning allocated resources
 * @param t Tuning to be freed
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
 * @example createChord("Fmaj7") creates a Fmaj7 chord
 * @param name Name of the chord, for example "Fmaj7"
 * @returns Created chord
 */
Chord createChord(char *name) {
    Chord chord;

    int strLen = strlen(name);
    char rootStr[3];
    int rootLen = 1;
    rootStr[0] = name[0];
    rootStr[1] = '\0';
    if(strLen > 1 && (name[1] == '#' || name[1] == 'b')) {
        rootStr[1] = name[1];
        rootLen++;
    }
    rootStr[2] = '\0';
    chord.root = strToTone(rootStr);

    chord.kind = strToChordKind(&(name[rootLen]));
    chord.type = getChordType(chord.kind);
    chord.tonesCount = chord.type.intervalCount;

    for(int i = 0; i < chord.tonesCount; i++) {
        chord.tones[i] = (Tone)((chord.root + chord.type.intervals[i]) % TONES_COUNT);
    }

    return chord;
}

/**
 * @brief This function correctly frees shape's allocated resources
 */
void freeShape(Shape s) {
    free(s.frets);
}

/**
 * @brief This function converts `Tone` instance to a readable string
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

/**
 * @brief This function converts chord to a readable string into a provided buffer
 * @param c Chord to be converted
 * @param buff Buffer to be used
 * @returns Buffer with the chord string
 */
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

/**
 * @brief This function converts string chord kind to a `ChordKind` instance
 * @param str String to be converted
 * @returns Converted chord kind
 */
ChordKind strToChordKind(char *str) {
    if(strcmp("(No chord kind)", str) == 0) {
        return NO_CHORD_KIND;
    }
    for(int i = 0; i < CHORD_KIND_SIZE; i++) {
        if(strcmp(chordKindNames[i], str) == 0) {
            return (ChordKind)i;
        }
    }

    return NO_CHORD_KIND;
}