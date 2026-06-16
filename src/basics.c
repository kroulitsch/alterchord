#include "basics.h"

ChordType basics_arr[CHORD_KIND_SIZE];

/**
 * @brief This function generates all basic chord kinds into the basics_arr array
 */
void generateBasics() {
    // (No chord kind)
    basics_arr[NO_CHORD_KIND] = createChordType(NO_CHORD_KIND, 0, NULL);

    // basic
    basics_arr[MAJ]  = createChordType(MAJ,  3, (int[]){0, 4, 7});
    basics_arr[MIN]  = createChordType(MIN,  3, (int[]){0, 3, 7});
    basics_arr[DIM]  = createChordType(DIM,  3, (int[]){0, 3, 6});
    basics_arr[AUG]  = createChordType(AUG,  3, (int[]){0, 4, 8});

    // six-seven
    basics_arr[DOM7]     = createChordType(DOM7,     4, (int[]){0, 4, 7, 10});
    basics_arr[MAJ7]     = createChordType(MAJ7,     4, (int[]){0, 4, 7, 11});
    basics_arr[MIN7]     = createChordType(MIN7,     4, (int[]){0, 3, 7, 10});
    basics_arr[MINMAJ7]  = createChordType(MINMAJ7,  4, (int[]){0, 3, 7, 11});
    basics_arr[M7B5]     = createChordType(M7B5,     4, (int[]){0, 3, 6, 10});
    basics_arr[DIM7]     = createChordType(DIM7,     4, (int[]){0, 3, 6, 9});
    basics_arr[MAJ6]     = createChordType(MAJ6,     4, (int[]){0, 4, 7, 9});
    basics_arr[MIN6]     = createChordType(MIN6,     4, (int[]){0, 3, 7, 9});
    basics_arr[DOM7SUS2] = createChordType(DOM7SUS2, 4, (int[]){0, 2, 7, 10});
    basics_arr[DOM7SUS4] = createChordType(DOM7SUS4, 4, (int[]){0, 5, 7, 10});
    basics_arr[MAJ7SUS2] = createChordType(MAJ7SUS2, 4, (int[]){0, 2, 7, 11});
    basics_arr[MAJ7SUS4] = createChordType(MAJ7SUS4, 4, (int[]){0, 5, 7, 11});
    basics_arr[MIN7SUS4] = createChordType(MIN7SUS4, 4, (int[]){0, 5, 7, 10});

    // nine
    basics_arr[DOM9]         = createChordType(DOM9,         5, (int[]){0, 4, 7, 10, 2});
    basics_arr[MAJ9]         = createChordType(MAJ9,         5, (int[]){0, 4, 7, 11, 2});
    basics_arr[MIN9]         = createChordType(MIN9,         5, (int[]){0, 3, 7, 10, 2});
    basics_arr[MINMAJ9]      = createChordType(MINMAJ9,      5, (int[]){0, 3, 7, 11, 2});
    basics_arr[M7B5B9]       = createChordType(M7B5B9,       5, (int[]){0, 3, 6, 10, 1});
    basics_arr[DIM9]         = createChordType(DIM9,         5, (int[]){0, 3, 6, 9, 2});
    basics_arr[DOM7B9]       = createChordType(DOM7B9,       5, (int[]){0, 4, 7, 10, 1});
    basics_arr[DOM7SHARP9]   = createChordType(DOM7SHARP9,   5, (int[]){0, 4, 7, 10, 3});
    basics_arr[DOM9SUS4]     = createChordType(DOM9SUS4,     5, (int[]){0, 5, 7, 10, 2});
    basics_arr[MAJ9SUS4]     = createChordType(MAJ9SUS4,     5, (int[]){0, 5, 7, 11, 2});
    basics_arr[MIN9SUS4]     = createChordType(MIN9SUS4,     5, (int[]){0, 5, 7, 10, 2});
    basics_arr[DOM7B9SUS4]   = createChordType(DOM7B9SUS4,   5, (int[]){0, 5, 7, 10, 1});

    // eleven
    basics_arr[DOM11]        = createChordType(DOM11,        6, (int[]){0, 4, 7, 10, 2, 5});
    basics_arr[MAJ11]        = createChordType(MAJ11,        6, (int[]){0, 4, 7, 11, 2, 5});
    basics_arr[MIN11]        = createChordType(MIN11,        6, (int[]){0, 3, 7, 10, 2, 5});
    basics_arr[MAJ7_SHARP11] = createChordType(MAJ7_SHARP11, 6, (int[]){0, 4, 7, 11, 2, 6});

    // thirteen
    basics_arr[DOM13]    = createChordType(DOM13,    7, (int[]){0, 4, 7, 10, 2, 5, 9});
    basics_arr[MAJ13]    = createChordType(MAJ13,    7, (int[]){0, 4, 7, 11, 2, 5, 9});
    basics_arr[MIN13]    = createChordType(MIN13,    7, (int[]){0, 3, 7, 10, 2, 5, 9});
    basics_arr[MINMAJ13] = createChordType(MINMAJ13, 7, (int[]){0, 3, 7, 11, 2, 5, 9});

    // add chords
    basics_arr[ADD9]     = createChordType(ADD9,     4, (int[]){0, 4, 7, 2});
    basics_arr[MINADD9]  = createChordType(MINADD9,  4, (int[]){0, 3, 7, 2});
    basics_arr[ADD4] = createChordType(ADD4, 4, (int[]){0, 4, 5, 7});

    // special, power
    basics_arr[SUS2]     = createChordType(SUS2,     3, (int[]){0, 2, 7});
    basics_arr[SUS4]     = createChordType(SUS4,     3, (int[]){0, 5, 7});
    basics_arr[POWER]    = createChordType(POWER,    2, (int[]){0, 7});
}

/**
 * @brief This function returns the already generated basics_arr chords array
 */
ChordType *getBasics() {
    return basics_arr;
}