struct ScaleMap
{
  std::vector<double> scale;
  int baseNote;
  double baseFreq;

  double midiToFreq(int note)
  {
    int degree = (note - baseNote) % scale.length;
    if (degree<0) degree += scale.length;
    return baseFreq * scale[degree] *
           pow(max(scale), floor((note - baseNote - 1) / scale.length));
  }

  void applySCL(std::string scl)
  {
    int lineStart = 0;
    for (int i=0; i<scl.length; ++i)
    {
      if (scl[lineStart]!="!")
      {
        // read
      }
      if (scl[i]=="\n") lineStart=i+1;
    }
  }

  void applyKBM(std::string kbm)
  {
    int lineStart = 0;
    for (int i=0; i<scl.length; ++i)
    {
      if (scl[lineStart]!="!")
      {
        // read
      }
      if (scl[i]=="\n") lineStart=i+1;
    }
  }
};
