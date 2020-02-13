/*

 ███████  ██████  █████  ██      ███████ ███    ███  █████  ██████
 ██      ██      ██   ██ ██      ██      ████  ████ ██   ██ ██   ██
 ███████ ██      ███████ ██      █████   ██ ████ ██ ███████ ██████
      ██ ██      ██   ██ ██      ██      ██  ██  ██ ██   ██ ██
 ███████  ██████ ██   ██ ███████ ███████ ██      ██ ██   ██ ██

  note-to-frequency mapping in any musical scale.

by Max Pollack
maxis.cool

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "tinyexpr.h"

typedef struct {
  int baseNote;
  double baseFreq;
  size_t scaleSize;
  double scale[1];
} Tuning;

double noteToFreq(int note, const Tuning* tuning) {

  note -= 1 + tuning->baseNote;
  int scaleSize = (int) tuning->scaleSize;

  int degree = note % scaleSize;
  if (degree<0) degree += scaleSize; // true modulo

  return tuning->scale[degree] * tuning->baseFreq *
           pow(tuning->scale[scaleSize-1],
         (note-degree) / scaleSize);
}

Tuning* newTuning(const char* baseNoteString,
                  const char* baseFreqString,
                  const char* scaleString) {

  size_t scaleSize = 1;
  for (const char* ch = scaleString; *ch; ++ch) if (*ch=='\n') scaleSize++;

  Tuning* tuning = (Tuning*) malloc(sizeof(Tuning) - 1 + sizeof(double) * scaleSize);

  if (tuning) {
    double baseNote = te_interp(baseNoteString, 0);
    double baseFreq = te_interp(baseFreqString, 0);

    tuning->baseNote = isnan(baseNote) ? 0 : round(baseNote);
    tuning->baseFreq = isnan(baseFreq) ? 0. : baseFreq;
    tuning->scaleSize = scaleSize;

    if (scaleString) {
      char* ssCopy = strdup(scaleString);
      char* line = ssCopy;
      char* newLine;

      for (int degree=0; degree<scaleSize; ++degree) {
        if ((newLine = strchr(line,'\n'))) {
          *newLine = '\0';
          tuning->scale[degree] = te_interp(line, 0);
          if (isnan(tuning->scale[degree])) tuning->scale[degree] = 0.;
          line = newLine + 1;
        } else {
          tuning->scale[degree] = te_interp(line, 0);
          if (isnan(tuning->scale[degree])) tuning->scale[degree] = 0.;
        }
      }

      free(ssCopy);
    } else tuning->scale[0] = 0.;
  }

  return tuning;

}
