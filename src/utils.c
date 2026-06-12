#include "utils.h"
#include <stdlib.h>

/**
 * @brief This function is used to create a `String` with a given `id` and `tone`
 * @param id ID of the string
 * @param tone Tuning of the string
 * @returns Pointer to a created string
 */
String *createString(int id, Tone tone) {
    String *s = malloc(sizeof(String));
    s->id = id;
    s->tuning = tone;

    return s;
}

/**
 * @brief This function correctly frees the string
 * @param s String to be freed
 */
void freeString(String *s) {
    free(s);
}

/**
 * @brief This function is used to create a `Tuning` with a given `stringCount` and `tuning`
 * @param stringCount number of strings to use
 * @param tuning Tuning of each string
 * @returns Pointer to a created string
 */
Tuning *createTuning(int stringCount, Tone *tuning) {
    Tuning *t = malloc(sizeof(Tuning));
    t->stringCount = stringCount;
    t->strings = malloc(stringCount * sizeof(String *));

    for(int i = 0; i < stringCount; i++) {
        t->strings[i] = createString(i, tuning[i]);
    }

    return t;
}

/**
 * @brief This function correctly frees the tuning
 * @param s Tuning to be freed
 */
void freeTuning(Tuning *t) {
    for(int i = 0; i < t->stringCount; i++) {
        freeString(t->strings[i]);
    }
    free(t->strings);

    free(t);
}