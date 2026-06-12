#ifndef BASICS_H
#define BASICS_H

#include "utils.h"

extern ChordType basics_arr[CHORD_KIND_SIZE];

void generateBasics();
ChordType *getBasics();

#endif