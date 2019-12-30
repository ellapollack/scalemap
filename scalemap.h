/*

███████  ██████  █████  ██      ███████ ███    ███  █████  ██████
██      ██      ██   ██ ██      ██      ████  ████ ██   ██ ██   ██
███████ ██      ███████ ██      █████   ██ ████ ██ ███████ ██████
     ██ ██      ██   ██ ██      ██      ██  ██  ██ ██   ██ ██
███████  ██████ ██   ██ ███████ ███████ ██      ██ ██   ██ ██

 note-to-frequency mapping in any musical scale.

By Max Pollack
maxis.cool

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "tinyexpr.h"

double noteToFreq(int note, double* scale, int scaleLength, int baseNote, double baseFreq) {

  note -= 1 + baseNote;

  if (scale == NULL || scaleLength <= 0) return 1.;

  int degree = note % scaleLength;
  if (degree<0) degree += scaleLength; // true modulo

  return scale[degree] * baseFreq *
    pow(scale[scaleLength-1], (note-degree) / scaleLength);
}

int setScaleFromString(double** scalePtr, char* string) {
  static int degree = 0;
  static int scaleLength;
  char* stringCopy = string ? strdup(string) : NULL;
  char* line;
  double freqRatio;

  if ((line = strtok(stringCopy, "\n")) &&
      !isnan(freqRatio = te_interp(line, 0))) {
    degree++;
    setScaleFromString(scalePtr, NULL);
    if (*scalePtr) (*scalePtr)[--degree] = freqRatio;
  }
  else {
    double* tmp = degree==0 ? NULL : realloc(*scalePtr, degree * sizeof(double));
    if (tmp) *scalePtr = tmp;
    else { free(*scalePtr); *scalePtr = NULL; }
    free(stringCopy);
    scaleLength = degree;
  }
  return scaleLength;
}
