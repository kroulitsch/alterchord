#include "alterchord.h"

// Quick Start Example

int main() {
    Tuning myTuning = createTuning(6, "FACGCG", 24);
    Chord myChord = createChord("Gadd4");

    // Generate the first shape (span = 4, capo = 0, maxFret = 12)
    Shape s = getShape(myChord, myTuning, 4, 0, 12);
    
    // Iterate to the next available shape
    Shape *next = getNextShape(&s, 4, 0, 12);

    // Memory cleanup
    freeShapesList(&s);
    freeTuning(myTuning);
    return 0;
}