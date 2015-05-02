#include "wav_compare.h"
// Copyright (c) 2015, Tony Kirke. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
void mex_function(const std::string& fileName1, const std::string& fileName2, float& max_diff) {
	max_diff = wav_compare(fileName1,fileName2);
}

#include "mex-it/mex_wrap.cxx"
