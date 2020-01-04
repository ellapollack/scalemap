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

Tuning* tuningFromString(const char* str) {

  Tuning* tuning = NULL;
  size_t scaleSize = 1;

  char* strCopy = str ? strdup(str) : NULL;
  char* line;

  if (strCopy &&
      (line = strtok(strCopy, ":")) &&
      !isnan(te_interp(line, 0)) &&
      (line = strtok(NULL, "\n")) &&
      !isnan(te_interp(line, 0)) &&
      (line = strtok(NULL, "\n")) &&
      !isnan(te_interp(line, 0)))
  {
    while ((line = strtok(NULL, "\n")) &&
           !isnan(te_interp(line, 0)))
      scaleSize++;

    tuning = malloc(sizeof(Tuning) - 1 + sizeof(double) * scaleSize);

    if (tuning)
    {
      strcpy(strCopy, str);
      tuning->baseNote = te_interp(strtok(strCopy, ":"), 0);
      tuning->baseFreq = te_interp(strtok(NULL, "\n"), 0);
      tuning->scaleSize = scaleSize;
      for (int degree=0; degree<scaleSize; ++degree)
        tuning->scale[degree] = te_interp(strtok(NULL, "\n"), 0);
    }
  }
  free(strCopy);
  return tuning;
}
