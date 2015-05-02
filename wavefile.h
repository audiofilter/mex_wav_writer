#ifndef WAVEFILE_H
#define WAVEFILE_H
#include <string>
// Copyright (c) 2015, Tony Kirke. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
class wavefile {
public:
  const int bits_per_sample;
	int sample_rate;
  std::string fname;
  FILE *fid;			
  long num_samples;
  bool is_open;
  wavefile() : bits_per_sample(32) {
		sample_rate = 0;
		is_open = false;
  }
  ~wavefile() {
		if (is_open) close();
  }
  int open(std::string fname, long sample_r);
	void write(float s);
	void write(const float *a, int s);
  int close();
};

#endif
