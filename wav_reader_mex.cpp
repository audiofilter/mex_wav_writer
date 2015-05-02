#include "wavefile_r.h"
#include "hash_map.h"
#include <vector>

// Copyright (c) 2015, Tony Kirke. License: MIT License (http://www.opensource.org/licenses/mit-license.php)

// Keeps a hash map of "file name" to wavefile pointers
// so that many files can be open at once and it will find the
// correct pointer for writing to .wav file

static SPUC::hash_map<wavefile_r *> waves;

// If samples < 0, close the .wav file!, otherwise ignore except on opening .wav file

void mex_function(const std::string& fileName, long samples, std::vector<float>& data) {

	wavefile_r* wavptr;
	if (waves.contains(fileName)) {
		wavptr = waves.getValue(fileName);
	} else {
		wavptr = new wavefile_r();
		wavptr->open(fileName);
		waves.add(fileName, wavptr);
	}

	// Read buffer 
	if (samples > 0) {
		bool done=0;
		for (int i=0;i<samples;i++) {
			if (!done) {
				float d;
				done = wavptr->read_sample(d);
				data.push_back(d);
			}
		}
	}
		
	// Sneaky way to close if you don't want to wait for octave to end
	if (samples < 0) {
		wavptr->close();
	}
}

#include "mex-it/mex_wrap.cxx"
