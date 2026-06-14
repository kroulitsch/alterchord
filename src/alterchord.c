#include "alterchord.h"

/**
 * @brief This function checks if you press the `fret`-th fret on a `base` tuned string,
 * whether the resulting tone is contained in a `chord`
 * @param base Tone to which a string is tuned
 * @param fret which fret is pressed
 * @param chord Chord to check
 * @returns `true` if the resulting tone is in the chord, `false` otherwise
 */
bool isInChord(Tone base, int fret, Chord chord) {
    if (fret == MUTED) {
        return true; 
    }

    Tone tone = (Tone)(((int)base + fret) % TONES_COUNT);

    for(int i = 0; i < chord.tonesCount; i++) {
        if(tone == chord.tones[i]) {
            return true;
        }
    }

    return false;
}

/**
 * @brief This function calculates the current span of the pressed frets
 * @param frets array of frets pressed
 * @param currentFret Currently last modified string, assures correct span calculation
 * @param capo Fret a capo is on
 * @returns The current span
 */
int getSpan(int *frets, int currentFret, int capo) {
    int min = MAX_FRET + 1;
    int max = -1;

    for(int i = 0; i <= currentFret; i++) {
        if (frets[i] == MUTED || frets[i] == capo) continue;

        if(frets[i] < min) {
            min = frets[i];
        }
        
        if (frets[i] > max) {
            max = frets[i];
        }
    }

    if (max == -1) return 0;

    return (max - min);
}

static bool containsAllTones(Tuning tuning, Chord chord, int *frets) {
    bool found[TONES_COUNT] = {false};
    int uniqueTonesFound = 0;

    for (int s = 0; s < tuning.stringCount; s++) {
        if (frets[s] == MUTED) continue;

        Tone playingTone = (Tone)(((int)tuning.strings[s] + frets[s]) % TONES_COUNT);

        for (int i = 0; i < chord.tonesCount; i++) {
            if (playingTone == chord.tones[i] && !found[i]) {
                found[i] = true;
                uniqueTonesFound++;
            }
        }
    }

    return uniqueTonesFound == chord.tonesCount;
}

static bool getShapeRec(Tuning tuning, Chord chord, int span, int capo, int maxFret, int currentString, Shape *s) {
    if (currentString == tuning.stringCount) {
        return containsAllTones(tuning, chord, s->frets);; 
    }

    Tone base = tuning.strings[currentString];

    for (int f = capo; f <= maxFret && f <= tuning.fretCount; f++) {
        if (!isInChord(base, f, chord)) {
            continue;
        }

        s->frets[currentString] = f;

        if (getSpan(s->frets, currentString, capo) <= span) {
            if (getShapeRec(tuning, chord, span, capo, maxFret, currentString + 1, s)) {
                return true; 
            }
        }
    }

    s->frets[currentString] = MUTED;
    if (getShapeRec(tuning, chord, span, capo, maxFret, currentString + 1, s)) {
        return true;
    }
    
    return false;
}

/**
 * @brief This function generates a chord shape of a given `chord` in a given `tuning`
 * @param chord Chord to be generated the shape
 * @param tuning Tuning to generate the shape in
 * @param span Maximum distance between two pressed frets
 * @param capo Number of the fret the capo is on (no capo = 0)
 * @param maxFret Highest fret usable in the shape
 * @returns Generated shape
 */
Shape getShape(Chord chord, Tuning tuning, int span, int capo, int maxFret) {
    capo = capo <= tuning.fretCount ? capo : 0;
    maxFret = maxFret <= tuning.fretCount ? maxFret : tuning.fretCount;

    Shape s;
    s.tuning = tuning;
    s.chord = chord;
    s.frets = malloc(tuning.stringCount * sizeof(int));

    for (int i = 0; i < tuning.stringCount; i++) {
        s.frets[i] = MUTED;
    }

    bool found = getShapeRec(tuning, chord, span, capo, maxFret, 0, &s);

    if (!found) {
        free(s.frets);
        s.frets = NULL;
    }

    return s;
}