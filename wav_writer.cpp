#include "wavefile.h"
#include "hash_map.h"
#include <vector>

// Keeps a hash map of "file name" to wavefile pointers
// so that many files can be open at once and it will find the
// correct pointer for writing to .wav file

static SPUC::hash_map<wavefile *> waves;

// If sample_rate < 0, close the .wav file!, otherwise ignore except on opening .wav file

void mex_function(const std::string& fileName, long sample_rate, const std::vector<float>& data) {

	wavefile* wavptr;
	if (waves.contains(fileName)) {
		wavptr = waves.getValue(fileName);
	} else {
		wavptr = new wavefile();
		wavptr->open(fileName,sample_rate);
		waves.add(fileName, wavptr);
	}

	// Write buffer 
	if (data.size() > 0) {
		wavptr->write(&data[0],data.size());
	}

	// Sneaky way to close if you don't want to wait for octave to end
	if (sample_rate < 0) {
		wavptr->close();
	}
}

#include "mex-it/mex_wrap.cxx"
