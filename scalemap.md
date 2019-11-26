## Currently under development

```cpp
#include <scalemap.cpp>

ScaleMap sm; // 12-tone equal temperament by default
sm.midiToFreq(69) == 440.; // true

sm.applySCL("meanquar.scl"); // load Scala SCL scale file
sm.applyKBM("example.kbm"); // load Scala KBM keyboard map file
sm.midiToFreq(69) == 440.; // false
```
