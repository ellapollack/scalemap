# `scalemap`

*a string format for musical scales*, consisting of a sequence of newline-separated math expressions corresponding to the frequency interval of each scale degree (ending with the octave).

### Examples:

#### 12-tone equal temperament:
```
2^(1/12)
```

#### 5-limit JI:
```
9/8
5/4
4/3
3/2
5/3
15/8
2
```

---

## C API

### `typedef struct tuning`

- `int baseNote`, the note number of the *tonic*.
- `double baseFreq`, the frequency of the *tonic*.
- `size_t scaleSize`, the number of degrees in `scale` (at least `1`).
- `double* scale`, an array containing the frequency ratio of each *scale degree*, ending with the *octave*.

### `tuning newTuning(const char* baseNoteExpr, const char* baseFreqExpr, const char* scaleExpr)`
- **Returns** a `tuning` specified by:
  - `baseNoteExpr`, a math expression for `baseNote` (rounded to nearest integer).
  - `baseFreqExpr`, a math expression for `baseFreq`.
  - `scaleExpr`, math expressions for each `scale` degree, separated by `\n`.
- Math expressions are parsed by [TinyExpr](https://codeplea.com/tinyexpr).
- Be sure to call `free(tuning.scale)` when you're done with it to prevent a memory leak.

### `double noteToFreq(int note, tuning tuning)`
- **Returns** the frequency of a `note` according to a `tuning`.

```c
#include "scalemap.h"

int main() {
  tuning t = newTuning("69","440","2^(1/12)");
  noteToFreq(60, t); // returns 261.626
  free(t.scale);
}
```

---

## C++ API

Defines all the same functions and types as in **C**, plus the `Tuning` convenience class:

### `class Tuning`
- `Tuning(std::string baseNoteExpr, std::string baseFreqExpr, std::string scaleExpr)`
- `int baseNote`
- `double baseFreq`
- `std::vector<double> scale`
- `noteToFreq(int note)`

```cpp
#include "scalemap.h"

int main() {
  Tuning t ("69","440","2^(1/12)");
  t.noteToFreq(60); // returns 261.626
}
```

---

## JavaScript API

Ported to WebAssembly with [Emscripten](https://emscripten.org)

### `parseExpr(mathExpr)`
- **Returns** the Number result of parsing the String `mathExpr` using [TinyExpr](https://codeplea.com/tinyexpr)
- If the math expression is invalid, **returns** `0`

### `class Tuning`
- `Tuning(baseNoteExpr, baseFreqExpr, scaleExpr)` (Object)
- `baseNote` (Number)
- `baseFreq` (Number)
- `scale` (Array of Numbers)
- `noteToFreq(note)` (Number)

```html
<script src="scalemap.js"></script>
<script>
  Module.onRuntimeInitialized = function() { // wait for WebAssembly to initialize
    var t  = new Tuning("69","440","2^(1/12)");
    t.noteToFreq(60); // returns 261.626
  }
</script>
```
