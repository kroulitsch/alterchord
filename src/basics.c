#include "basics.h"

ChordType basics_arr[CHORD_KIND_SIZE];

void generateBasics() {
    basics_arr[NO_CHORD_KIND] = createChordType(NO_CHORD_KIND, 0, NULL);
    basics_arr[MAJ] = createChordType(MAJ, 3, (int[]){0, 4, 7});
    basics_arr[MIN] = createChordType(MIN, 3, (int[]){0, 3, 7});
    basics_arr[DIM] = createChordType(DIM, 3, (int[]){0, 3, 6});
    basics_arr[AUG] = createChordType(AUG, 3, (int[]){0, 4, 8});
    basics_arr[MAJ7] = createChordType(MAJ7, 4, (int[]){0, 4, 7, 11});
    basics_arr[MIN7] = createChordType(MIN7, 4, (int[]){0, 3, 7, 10});
    basics_arr[SUS2] = createChordType(SUS2, 3, (int[]){0, 2, 7});
    basics_arr[SUS4] = createChordType(SUS4, 3, (int[]){0, 5, 7});
}

ChordType *getBasics() {
    return basics_arr;
}