#ifndef ALTERCHORD_H
#define ALTERCHORD_H

#include "utils.h"
#include "basics.h"

#include <stdbool.h>

bool isInChord(Tone base, int fret, Chord chord);
int getSpan(int *frets, int currentFret, int capo);
Shape getShape(Chord chord, Tuning tuning, int span, int capo, int maxFret);

Shape *getNextShape(Shape *current, int span, int capo, int maxFret);
Shape *getPrevShape(Shape *current);

#endif