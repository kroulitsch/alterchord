#include "alterchord.h"

/**
 * @brief This function generates a chord shape of a given `chord` in a given `tuning`
 * @param chord Chord to be generated the shape
 * @param tuning Tuning to generate the shape in
 * @param capo Optional, number of the fret the capo is on (no capo = 0/leave out)
 * @param maxFret Optional, highest fret usable in the shape
 * @returns Generated shape
 */
Shape getShape(Chord chord, Tuning tuning, int capo, int maxFret) {
    capo = capo ? capo : 0;
    maxFret = maxFret ? maxFret : MAX_FRET;
    Shape s;
    s.tuning = tuning;
    s.chord = chord;
    s.frets = malloc(tuning.stringCount * sizeof(int));

    // main algorithm

    return s;
}