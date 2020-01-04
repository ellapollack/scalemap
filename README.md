# `scalemap`
is a **C** library for loading + using [musical tunings](https://en.wikipedia.org/wiki/Musical_tuning#Tuning_systems).

## Types

- ### `typedef struct Tuning`

  - `int baseNote`, the note number of the *tonic*.
  - `double baseFreq`, the frequency of the *tonic*.
  - `size_t scaleSize`, the number of elements in `scale` (at least `1`).
  - `double scale[]`, a [flexible array member](https://en.wikipedia.org/wiki/Flexible_array_member) containing the frequency ratio of each *scale degree*, the last of which is the *octave*.

## Functions

- ### `double noteToFreq(int note, Tuning* tuning)`
  - **Returns** the frequency of a `note` according to a `tuning`.

- ### `Tuning* tuningFromString(char* string)`
  - Allocates a new `Tuning` specified by a `string` in the following format:

        baseNote : baseFreq
        scale[0]
        .
        .
        .
        scale[scaleSize-1]

  - `baseNote`, `baseFreq`, and `scale[x]` are *math expressions* (parsed by [TinyExpr](https://codeplea.com/tinyexpr)).
  - All non-newline whitespace is ignored.
  - **Returns** a pointer to the new `Tuning`, or `NULL` if `string` is invalid.
  - Be sure to call `free(tuning)` when you're done with it, to prevent a memory leak.

---

`demo.c`:
```c
#include <stdio.h>
#include "scalemap.h"

int main() {

  Tuning* tuning;

  //============================================================

  printf("\nA440 12-tone equal temperament\n");
  tuning = tuningFromString("69:440\n2^(1/12)");

  for (int note=60; note<=72; ++note)
    printf("note %d : %f Hz\n", note, noteToFreq(note, tuning));

  free(tuning);

  //============================================================

  printf("\nA432 Pythagorean tuning\n");
  tuning = tuningFromString("60:256\n"
                            "256/243\n"
                            "9/8\n"
                            "32/27\n"
                            "81/64\n"
                            "4/3\n"
                            "729/512\n"
                            "3/2\n"
                            "128/81\n"
                            "27/16\n"
                            "16/9\n"
                            "243/128\n"
                            "2");

  for (int note=60; note<=72; ++note)
  printf("note %d : %f Hz\n",
         note, noteToFreq(note, tuning));

  free(tuning);

}
```
In Terminal:
```console
$ gcc demo.c tinyexpr.c -o demo
$ ./demo

A440 12-tone equal temperament
note 60 : 261.625565 Hz
note 61 : 277.182631 Hz
note 62 : 293.664768 Hz
note 63 : 311.126984 Hz
note 64 : 329.627557 Hz
note 65 : 349.228231 Hz
note 66 : 369.994423 Hz
note 67 : 391.995436 Hz
note 68 : 415.304698 Hz
note 69 : 440.000000 Hz
note 70 : 466.163762 Hz
note 71 : 493.883301 Hz
note 72 : 523.251131 Hz

A432 Pythagorean tuning
note 60 : 256.000000 Hz
note 61 : 269.695473 Hz
note 62 : 288.000000 Hz
note 63 : 303.407407 Hz
note 64 : 324.000000 Hz
note 65 : 341.333333 Hz
note 66 : 364.500000 Hz
note 67 : 384.000000 Hz
note 68 : 404.543210 Hz
note 69 : 432.000000 Hz
note 70 : 455.111111 Hz
note 71 : 486.000000 Hz
note 72 : 512.000000 Hz
```
