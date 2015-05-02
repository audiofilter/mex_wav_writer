#include "wav_compare.h"
#include "wavefile_r.h"
#include <cmath>
// Copyright (c) 2015, Tony Kirke. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
float wav_compare(const std::string& fileName1, const std::string& fileName2) {
	float max_diff=0;
	wavefile_r wav1;
	wavefile_r wav2;
	bool ok1 = wav1.open(fileName1);
	bool ok2 = wav2.open(fileName2);

	if (!ok1 || !ok2) max_diff = -1.0; // not a floating point wavefile!
	else {
		float s1,s2;
		max_diff = 0;
		int done = 0;
		do {
			int done1 = wav1.read_sample(s1);
			int done2 = wav2.read_sample(s2);
			float diff = fabs(s1 - s2);
			if (diff > max_diff) max_diff = diff;
			done = done1 || done2;
		} while (!done);
	}
	
	wav1.close();
	wav2.close();
	return max_diff;
}
