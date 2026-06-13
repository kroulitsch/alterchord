#include "alterchord.h"
#include <stdio.h>

int main() {
    Tuning t = createTuning(6, "FACGCE");

    for(int i = 0; i < t.stringCount; i++) {
        printf("%s ", toneToStr(t.strings[i].tuning));
    }
    printf("\n");

    Chord cmaj7 = createChord("Cmaj");
    char buff[TONES_COUNT];
    printf("%s\n", chordToStr(cmaj7, buff));
    freeTuning(t);
    return 0;
}