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
        return containsAllTones(tuning, chord, s->frets); 
    }

    Tone base = tuning.strings[currentString];

    s->frets[currentString] = MUTED;
    if (getShapeRec(tuning, chord, span, capo, maxFret, currentString + 1, s)) {
        return true;
    }

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
    s.prev = NULL;
    s.next = NULL;

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

static bool getNextShapeRec(Tuning tuning, Chord chord, int span, int capo, int maxFret, int currentString, int *originalFrets, Shape *s, bool *skipCurrent) {
    if (currentString == tuning.stringCount) {
        if (containsAllTones(tuning, chord, s->frets)) {
            if (*skipCurrent) {
                *skipCurrent = false;
                return false; 
            }
            return true; 
        }
        return false;
    }

    int originalFret = originalFrets[currentString];
    Tone base = tuning.strings[currentString];

    if (!*skipCurrent || originalFret == MUTED) {
        bool originalSkipState = *skipCurrent;
        
        s->frets[currentString] = MUTED;
        
        if (getNextShapeRec(tuning, chord, span, capo, maxFret, currentString + 1, originalFrets, s, skipCurrent)) {
            return true;
        }
        
        *skipCurrent = originalSkipState;
    }

    int startFret = (*skipCurrent && originalFret != MUTED) ? originalFret : capo;

    for (int f = startFret; f <= maxFret && f <= tuning.fretCount; f++) {
        if (!isInChord(base, f, chord)) {
            continue;
        }

        bool originalSkipState = *skipCurrent;
        if (*skipCurrent && f != originalFret) {
            *skipCurrent = false;
        }

        s->frets[currentString] = f;

        if (getSpan(s->frets, currentString, capo) <= span) {
            if (getNextShapeRec(tuning, chord, span, capo, maxFret, currentString + 1, originalFrets, s, skipCurrent)) {
                return true;
            }
        }

        *skipCurrent = originalSkipState;
    }

    return false;
}

Shape *getNextShape(Shape *current, int span, int capo, int maxFret) {
    if (!current || !current->frets) return NULL;

    if (current->next != NULL) {
        return current->next;
    }

    capo = capo <= current->tuning.fretCount ? capo : 0;
    maxFret = maxFret <= current->tuning.fretCount ? maxFret : current->tuning.fretCount;

    Shape *nextShape = malloc(sizeof(Shape));
    if (!nextShape) return NULL;

    nextShape->tuning = current->tuning;
    nextShape->chord = current->chord;
    nextShape->frets = malloc(current->tuning.stringCount * sizeof(int));
    if (!nextShape->frets) {
        free(nextShape);
        return NULL;
    }
    nextShape->prev = current;
    nextShape->next = NULL;

    for (int i = 0; i < current->tuning.stringCount; i++) {
        nextShape->frets[i] = MUTED;
    }

    bool skipCurrent = true;
    bool found = getNextShapeRec(current->tuning, current->chord, span, capo, maxFret, 0, current->frets, nextShape, &skipCurrent);

    if (found) {
        current->next = nextShape;
        return nextShape;
    }

    free(nextShape->frets);
    free(nextShape);
    return NULL;
}

Shape *getPrevShape(Shape *current) {
    if (!current || !current->prev) return NULL;
    return current->prev;
}

int analyzeShape(Shape shape, ChordKind *foundKinds, Tone *foundRoots, int maxResults) {
    bool shapeTones[TONES_COUNT] = {false};
    int uniqueShapeTonesCount = 0;
    int matchCount = 0;

    for (int s = 0; s < shape.tuning.stringCount; s++) {
        if (shape.frets[s] == MUTED) continue;

        Tone playingTone = (Tone)(((int)shape.tuning.strings[s] + shape.frets[s]) % TONES_COUNT);
        if (!shapeTones[playingTone]) {
            shapeTones[playingTone] = true;
            uniqueShapeTonesCount++;
        }
    }

    if (uniqueShapeTonesCount == 0) return 0;

    for (int r = 0; r < TONES_COUNT; r++) {
        Tone currentRoot = (Tone)r;

        for (int k = 1; k < CHORD_KIND_SIZE; k++) {
            ChordType type = getChordType((ChordKind)k);
            if (type.kind == NO_CHORD_KIND) continue;

            if (type.intervalCount != uniqueShapeTonesCount) continue;

            bool testChordTones[TONES_COUNT] = {false};
            for (int i = 0; i < type.intervalCount; i++) {
                Tone t = (Tone)((currentRoot + type.intervals[i]) % TONES_COUNT);
                testChordTones[t] = true;
            }

            bool isMatch = true;
            for (int t = 0; t < TONES_COUNT; t++) {
                if (shapeTones[t] != testChordTones[t]) {
                    isMatch = false;
                    break;
                }
            }

            if (isMatch) {
                if (matchCount < maxResults) {
                    foundKinds[matchCount] = type.kind;
                    foundRoots[matchCount] = currentRoot;
                    matchCount++;
                } else {
                    return matchCount;
                }
            }
        }
    }

    return matchCount;
}