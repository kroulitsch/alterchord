#include "alterchord.h"
#include <stdio.h>

int main() {
    Tuning myTuning = createTuning(6, "FACGCG", 24);

    Chord myChord = createChord("Fmaj7sus4");
    
    printf("Looking for shapes for a chord Fmaj7sus4 in tuning FACGCG\n");
    printf("--------------------------------------------------\n");

    Shape s = getShape(myChord, myTuning, 2, 0, 12);
    
    if (s.frets == NULL) {
        printf("No shape for this chord found.\n");
        return 0;
    }

    Shape *current = &s;
    int counter = 1;

    while (current != NULL) {
        printf("Shape %02d: ", counter++);
        
        for (int i = 0; i < current->tuning.stringCount; i++) {
            if (current->frets[i] == MUTED) {
                printf("X ");
            } else {
                printf("%d ", current->frets[i]);
            }
        }
        printf("\n");

        current = getNextShape(current, 2, 0, 12);
    }

    printf("--------------------------------------------------\n");
    printf("All possible combinations printed out.\n");

    printf("\n\n");
    Shape clickedShape;
    clickedShape.tuning = myTuning;
    clickedShape.frets = (int[]){2, MUTED, 2, 4, 0, 0};

    ChordKind foundKinds[MAX_RESULTS];
    Tone foundRoots[MAX_RESULTS];

    int count = analyzeShape(clickedShape, foundKinds, foundRoots, MAX_RESULTS);

    printf("Shape analysis: 2 X 2 4 0 0 in tuning FACGCG\n");
    printf("Found options (%d):\n", count);
    printf("----------------------------------------\n");

    if(count == 0) {
        printf("No option found.");
    }

    for (int i = 0; i < count; i++) {
        char *kindStr = chordKindNames[foundKinds[i]];
        char *rootStr = toneToStr(foundRoots[i]);

        printf("Option %d: %s%s\n", i + 1, rootStr, kindStr);
    }
    printf("----------------------------------------\n");

    // 6. Úklid paměti
    freeShapesList(&s);
    freeTuning(myTuning);
    return 0;
}