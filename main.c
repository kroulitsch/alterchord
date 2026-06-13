#include "alterchord.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Tuning t = createTuning(6, "FACGCE");

    for(int i = 0; i < t.stringCount; i++) {
        printf("%s ", toneToStr(t.strings[i].tuning));
    }
    printf("\n");

    Chord cmaj7 = createChord(C, MAJ7);
    freeTuning(t);
    return 0;
}