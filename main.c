#include "alterchord.h"
#include <stdio.h>

int main() {
    Tuning t = createTuning(6, "FACGCG", 24);

    for(int i = 0; i < t.stringCount; i++) {
        printf("%s ", toneToStr(t.strings[i]));
    }
    printf("\n");

    Chord fmaj = createChord("Hmin");
    char buff[TONES_COUNT * 3];
    printf("%s\n", chordToStr(fmaj, buff));

    Shape s = getShape(fmaj, t, 2, 0, t.fretCount);
    if(s.frets) {
        for(int i = 0; i < t.stringCount; i++) {
        printf("%d ", s.frets[i]);
    }
    printf("\n");
    }

    freeShape(s);
    freeTuning(t);
    return 0;
}