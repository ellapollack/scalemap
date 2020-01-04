#include <stdio.h>
#include "scalemap.h"

int main() {

  Tuning* tuning;

  //============================================================

  printf("\nA440 12-tone equal temperament\n");
  tuning = tuningFromString("69:440\n2^(1/12)");

  for (int note=60; note<=72; ++note)
    printf("note %d : %f Hz\n", note, noteToFreq(note, tuning));

  free(tuning);

  //============================================================

  printf("\nA432 Pythagorean tuning\n");
  tuning = tuningFromString("60:256\n"
                            "256/243\n"
                            "9/8\n"
                            "32/27\n"
                            "81/64\n"
                            "4/3\n"
                            "729/512\n"
                            "3/2\n"
                            "128/81\n"
                            "27/16\n"
                            "16/9\n"
                            "243/128\n"
                            "2");

  for (int note=60; note<=72; ++note)
  printf("note %d : %f Hz\n",
         note, noteToFreq(note, tuning));

  free(tuning);

}
