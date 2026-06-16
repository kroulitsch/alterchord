# Alterchord
Alterchord is a guitar chords shapes generator library for alternative tunings written in C.

It allows users to generate chord shapes based on given guitar specifications, such as a number of strings and their tuning (supports alternative tunings), capo position and maximum usable fret.

The library also provides a backwards chord shape analyzer, which analyzes a given shape in a given tuning and outputs all possible chords this shape could represent.

## Implementation details
The entire library is implemented in pure C, with no external overhead, although integration with a mobile app is planned in the [future](#future-works).

## Working with the library
The file with the `main()` function should be the `main.c` file (otherwise you would need to modify the `Makefile`).

The library can be built using:
```bash
make
```

To run the project using this library, use:
```bash
make run
```

To profile the binary and check for memory leaks using valgrind, use:
```bash
make v
```

To clean compiled binaries and object artifacts, use:
```bash
make clean
```

### Quick Start Example
```c
#include "alterchord.h"

int main() {
    Tuning myTuning = createTuning(6, "FACGCG", 24);
    Chord myChord = createChord("Gadd4");

    // Generate the first shape (span = 4, capo = 0, maxFret = 12)
    Shape s = getShape(myChord, myTuning, 4, 0, 12);
    
    // Iterate to the next available shape
    Shape *next = getNextShape(&s, 4, 0, 12);

    // Memory cleanup
    freeShapesList(&s);
    freeTuning(myTuning);
    return 0;
}
```

## Future works
Planned future updates include:

* **Mobile app development:** The goal is to create a user-friendly frontend interface based on this programmer-friendly backend library.
* **Chord shape ranking:** Currently the shape generator returns shapes in the basic first-found order. In the new approach, the chord shapes would be ordered based on the difficulty with which one would achieve this shape in real life.
* **Shape transition optimization:** When playing a chord shape, it is often useful to transition into a different shape with minimum movement across the fretboard. This update would generate the upcoming chord shape based on the previous one to ensure the optimal transition.
* **Shape recognition via microphone:** This feature would basically work as *Shazam* for chords; the user would play a chord and the program would digitally process the frequencies and output the chord options.
* **Next chord possibilities:** This feature would help musicians create chord progressions, providing the next chord possibilities based on music theory.

## Author
* Jan Kroulík - Main Developer
    * Github: [kroulitch](https://github.com/kroulitsch)
    * Contact: [xkroulj00@vutbr.cz](mailto:xkroulj00@vutbr.cz)