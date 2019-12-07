## Currently under development

Will support loading of Scala [SCL](http://www.huygens-fokker.org/scala/scl_format.html) and [KBM](http://www.huygens-fokker.org/scala/help.htm#mappings) files.

```cpp
#include <scalemap.cpp>

ScaleMap sm; // 12-tone equal temperament by default
sm.midiToFreq(69) == 440.; // true

sm.loadSCL("meanquar.scl"); // load Scala SCL scale file
sm.loadKBM("example.kbm"); // load Scala KBM keyboard map file
sm.midiToFreq(69) == 440.; // false
```
