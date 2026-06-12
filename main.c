#include "alterchord.h"

int main() {
    Tone tones[6] = {F, A, G, C, G, E};
    Tuning *t = createTuning(6, tones);

    freeTuning(t);
    return 0;
}