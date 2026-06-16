#include "alterchord.h"
#include <stdio.h>

int main() {
    Tuning myTuning = createTuning(6, "FACGCG", 24);

    Chord myChord = createChord("Fmaj7sus4");
    
    printf("Looking for shapes for a chord Fmaj7sus4\n");
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

    // 6. Úklid paměti
    freeShapesList(&s);
    freeTuning(myTuning);
    return 0;
}