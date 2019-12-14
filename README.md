# `ScaleMap`
is a C++ class which converts note numbers to frequencies, based on a user-definable musical scale.

Add `ScaleMap` to your project with

```cpp
#include "scalemap.h"
```

By default, it uses [A440 12-tone equal temperament](https://en.wikipedia.org/wiki/Equal_temperament).

```cpp
ScaleMap sm;

for (int note=60; note<72; ++note)
  cout << note << " : " << sm.noteToFreq(note) << "\n";
```
```console
60 : 261.626
61 : 277.183
62 : 293.665
63 : 311.127
64 : 329.628
65 : 349.228
66 : 369.994
67 : 391.995
68 : 415.305
69 : 440
70 : 466.164
71 : 493.883
```
To load a new scale, call `fromString(std::string scale)`, with `scale` in the following format:
```
baseNote : baseFreq
freqRatio1
freqRatio2
freqRatio3
.
.
.
freqRatioOctave
```

- `baseNote` is an integer, and sets the note at which the scale begins.
- `baseFreq` is a math expression, and sets the frequency of `baseNote`.
- `freqRatioN` is a math expression, and sets the frequency ratio of the Nth scale degree.
- The final `freqRatioN` is used as the octave.
- All math expressions are parsed with [TinyExpr](https://codeplea.com/tinyexpr).
- All non-newline whitespace is ignored.

So for example, to load [A432 Pythagorean tuning](https://en.wikipedia.org/wiki/Pythagorean_tuning):


```cpp
sm.fromString("60:256\n256/243\n9/8\n32/27\n81/64\n4/3\n729/512\n3/2\n128/81\n27/16\n16/9\n243/128\n2");

for (int note=60; note<72; ++note)
  cout << note << " : " << sm.noteToFreq(note) << "\n";
```
```console
60 : 256
61 : 269.695
62 : 288
63 : 303.407
64 : 324
65 : 341.333
66 : 364.5
67 : 384
68 : 404.543
69 : 432
70 : 455.111
71 : 486

```

`fromString` is *thread-safe*. Simultaneously calling `noteToFreq` in the audio thread and `fromString` in the GUI thread will not cause data races.
