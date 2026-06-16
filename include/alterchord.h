#ifndef ALTERCHORD_H
#define ALTERCHORD_H

#include "utils.h"
#include "basics.h"

#include <stdbool.h>

#define MAX_RESULTS CHORD_KIND_SIZE

bool isInChord(Tone base, int fret, Chord chord);
int getSpan(int *frets, int currentFret, int capo);
Shape getShape(Chord chord, Tuning tuning, int span, int capo, int maxFret);

Shape *getNextShape(Shape *current, int span, int capo, int maxFret);
Shape *getPrevShape(Shape *current);

int analyzeShape(Shape shape, Chord *foundChords, int maxResults);

#endif