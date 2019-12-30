#include <stdio.h>
#include "scalemap.h"

int main() {
  //===========================================================================
  printf("A440 12-tone equal temperament\n");
  int baseNote = 69;
  double baseFreq = 440.;
  double* scale = NULL;
  int scaleLength = setScaleFromString(&scale, "2^(1/12)");

  for (int note=60; note<=72; ++note)
  printf("note %d : %f Hz\n",
         note, noteToFreq(note, scale, scaleLength, baseNote, baseFreq));
  //===========================================================================
  printf("\nA432 Pythagorean tuning\n");
  baseNote = 60;
  baseFreq = 256.;
  scaleLength = setScaleFromString(&scale,
  "256/243\n9/8\n32/27\n81/64\n4/3\n729/512\n3/2\n128/81\n27/16\n16/9\n243/128\n2");

  for (int note=60; note<=72; ++note)
  printf("note %d : %f Hz\n",
         note, noteToFreq(note, scale, scaleLength, baseNote, baseFreq));
  //===========================================================================
  free(scale);
}
