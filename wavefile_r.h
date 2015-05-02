#ifndef WAVEFILER_H
#define WAVEFILER_H
#include <string>
// Copyright (c) 2015, Tony Kirke. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
class wavefile_r {
public:
  int bits_per_sample;
	int sample_rate;
  std::string fname;
  FILE *fid;			
  long num_samples;
  bool is_open;
	bool is_float;
  wavefile_r() {
		sample_rate = 0;
		is_open = false;
  }
  ~wavefile_r() {
		if (is_open) close();
  }
  int open(std::string fname);
	int read_sample(float& left);
	int read_samples(float& left, int samples);
  void close() { is_open = fclose(fid); }
};

#endif
