#include "alterchord.h"
#include <stdio.h>

int main() {
    Tuning t = createTuning(6, "FACGCE");

    for(int i = 0; i < t.stringCount; i++) {
        printf("%s ", toneToStr(t.strings[i]));
    }
    printf("\n");

    Chord cmaj7 = createChord("Abaug");
    char buff[TONES_COUNT];
    printf("%s\n", chordToStr(cmaj7, buff));
    freeTuning(t);
    return 0;
}