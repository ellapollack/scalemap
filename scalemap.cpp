#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <deque>

#include "tinyexpr.h"

using namespace std;

struct ScaleMap {
  atomic<int> baseNote;
  atomic<double> baseFreq;
  atomic<int> scaleSize;
  deque< atomic<double> > scale;

  ScaleMap(string str = "60:440*2^-0.75\n2^(1/12)\n2^(1/6)\n2^(1/4)\n2^(1/3)\n2^(5/12)\n2^(1/2)\n2^(7/12)\n2^(2/3)\n2^(3/4)\n2^(5/6)\n2^(11/12)\n2",
           int maxScaleSize=128)
  {
    scale.resize(maxScaleSize);
    fromString(str);
  }

  double noteToFreq(int note) {

    // atomic access
    int baseNoteNow = baseNote.load();
    double baseFreqNow = baseFreq.load();
    int scaleSizeNow = scaleSize.load();

    if (scaleSizeNow <= 0) return baseFreqNow;

    int degree = (note-baseNoteNow-1) % scaleSizeNow;
    if (degree<0) degree += scaleSizeNow; // true modulo
    return baseFreqNow *
           scale[degree].load() *
           pow(scale[scaleSizeNow-1],
               (note-baseNoteNow-1-degree) / scaleSizeNow);
  }

  int fromString(string str) {
    int baseNoteTmp;
    double baseFreqTmp;
    int scaleSizeTmp = 0;

    istringstream iss(str);
    string line;
    size_t colon;

    if (getline(iss, line) &&
        (colon = line.find(':')) > 0 &&
        colon < line.length() - 1 &&
        !isnan(baseFreqTmp = te_interp(&line[colon+1], 0))
       )
    {
      try {baseNoteTmp = stoi(line);} catch (...) { return 1; }

      baseNote.store(baseNoteTmp);
      baseFreq.store(baseFreqTmp);

      double freqRatio;
      while (getline(iss, line) &&
             scaleSizeTmp < scale.size() &&
             !isnan(freqRatio = te_interp(&line[0], 0)))
      {
        scale[scaleSizeTmp].store(freqRatio);
        scaleSizeTmp++;
      }

      scaleSize.store(scaleSizeTmp);

      return 0;
    }
    else return 1;
  }
};

int main() {
  ScaleMap sm;
  sm.fromString("60:256\n256/243\n9/8\n32/27\n81/64\n4/3\n"
                "729/512\n3/2\n128/81\n27/16\n16/9\n243/128\n2");
  for (int note=60; note<73; ++note) {
    cout << note << ' ';
    cout << sm.noteToFreq(note) << '\n';
  }
}
