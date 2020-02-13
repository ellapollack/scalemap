# `scalemap`
is a **C** library for loading + using [musical tunings](https://en.wikipedia.org/wiki/Musical_tuning#Tuning_systems).

### `typedef struct Tuning`

- `int baseNote`, the note number of the *tonic*.
- `double baseFreq`, the frequency of the *tonic*.
- `size_t scaleSize`, the number of degrees in `scale` (at least `1`).
- `double scale[]`, a [flexible array member](https://en.wikipedia.org/wiki/Flexible_array_member) containing the frequency ratio of each *scale degree*, ending with the *octave*.

### `double noteToFreq(int note, Tuning* tuning)`
- **Returns** the frequency of a `note` according to a `tuning`.

### `Tuning* newTuning(const char* baseNoteString, const char* baseFreqString, const char* scaleString)`
- Allocates a new `Tuning` specified by:
  - `baseNoteString`, a **math expression** for `baseNote` (rounded to nearest integer).
  - `baseFreqString`, a **math expression** for `baseFreq`.
  - `scaleString`, a sequence of newline-separated **math expressions** for each `scale` degree.
- **Math expressions** are parsed by [TinyExpr](https://codeplea.com/tinyexpr).
- All non-newline whitespace is ignored.
- **Returns** a pointer to the new `Tuning`, or `NULL` if allocation was unsuccessful.
- Be sure to call `free(tuning)` when you're done with it to prevent a memory leak.

---

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
