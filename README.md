# `scalemap`
is a small **C** library
for mapping **`int` notes** to **`double` frequencies** using **`double[]` musical scales**.

### It defines just 2 functions:

#### `double noteToFreq(int note, double* scale, int scaleLength, int baseNote, double baseFreq)`
**returns** the frequency of a `note`, according to a musical `scale` containing `scaleLength` frequency ratios (the last of which is the octave), beginning at `baseNote` with a frequency of `baseFreq`.

#### `int setScaleFromString(double** scalePtr, char* string)`
[reallocates](https://en.cppreference.com/w/c/memory/realloc) a new `double[]` at `*scalePtr` containing the values
specified by a `string` of newline-separated math expressions (parsed by [TinyExpr](https://codeplea.com/tinyexpr)), and **returns** its length.

---

`demo.c`:
```c
#include <stdio.h>
#include "scalemap.h"

int main() {
  //===========================================================================
  printf("\nA440 12-tone equal temperament\n");
  int baseNote = 69;
  double baseFreq = 440.;
  double* scale = NULL;
  int scaleLength = setScaleFromString(&scale, "2^(1/12)");

  for (int note=60; note<=72; ++note)
  printf("note %d : %f Hz\n",
         note, noteToFreq(note, scale, scaleLength, baseNote, baseFreq));
  //===========================================================================    
  printf("\nA432 Pythagorean tuning\n");
  baseNote = 60;
  baseFreq = 256.;
  scaleLength = setScaleFromString(&scale,
  "256/243\n9/8\n32/27\n81/64\n4/3\n729/512\n3/2\n128/81\n27/16\n16/9\n243/128\n2");

  for (int note=60; note<=72; ++note)
  printf("note %d : %f Hz\n",
         note, noteToFreq(note, scale, scaleLength, baseNote, baseFreq));
  //===========================================================================  
  free(scale);
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
