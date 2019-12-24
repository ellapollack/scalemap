# `ScaleMap`
is a **C** library
for creating `double[]` **musical scales** and using them to map `int` **notes** to `double` **frequencies**.

### It defines just 2 functions:

### 1. `double noteToFreq(int note, double* scale, int scaleLength)`
Returns the frequency of `note` (which is `1.` if `note==0`) according to a `scale` with `scaleLength` degrees.

- `note` is any `int`, with `0` being the start of the scale.
- `scale` points to the first element of a `double[]` **musical scale**, which contains `scaleLength` frequency ratios to be repeated over frequency space every factor of `scale[scaleLength-1]`.

### 2. `int setScaleFromString(double** scalePtr, char* string)`
Parses `string` into a `double[]` **musical scale**, sets `*scalePtr` to point to it, and returns its length.
- `scalePtr` should point to a `double[]` which is either `NULL` or pointing to a previously [allocated](https://en.cppreference.com/w/c/memory) block of memory.
- `string` should contain solely newline-separated [C-style math expressions](https://codeplea.com/tinyexpr).
- Be sure to call `free(*scalePtr)` sometime afterwards to prevent a memory leak.
- Not thread-safe (uses static variables).

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
         note, baseFreq * noteToFreq(note - baseNote, scale, scaleLength));
  //===========================================================================    
  printf("\nA432 Pythagorean tuning\n");
  baseNote = 60;
  baseFreq = 256.;
  scaleLength = setScaleFromString(&scale,
  "256/243\n9/8\n32/27\n81/64\n4/3\n729/512\n3/2\n128/81\n27/16\n16/9\n243/128\n2");

  for (int note=60; note<=72; ++note)
  printf("note %d : %f Hz\n",
         note, baseFreq * noteToFreq(note - baseNote, scale, scaleLength));
  //===========================================================================  
  free(scale);
}
```
when compiled with `gcc demo.c tinyexpr.c` and run, prints:
```console
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

### To use it in your C project:

1. Download `tinyexpr.h` and `tinyexpr.c` from the [TinyExpr](https://codeplea.com/tinyexpr) C library.
2. Download `scalemap.h` from this repository.
3. Place `tinyexpr.h` and `scalemap.h` in your `#include` search path
4. Link `tinyexpr.c` in your build process.
5. Add `#include "scalemap.h"` to your project source.
