#include "wavefile_r.h"
#include <math.h>
#include <iostream>

// Copyright (c) 2015, Tony Kirke. License: MIT License (http://www.opensource.org/licenses/mit-license.php)

unsigned long read_uint16(char *c) 
{
	unsigned char *uc = (unsigned char *)c;
	return (((unsigned long) uc[1]) << 8) | uc[0];
}

unsigned long read_uint32(char *c) 
{
	unsigned char *uc = (unsigned char *)c;
	return (((unsigned long) uc[3]) << 24) |
		(((unsigned long) uc[2]) << 16) |
		(((unsigned long) uc[1]) << 8) |
		uc[0];
}

// Opening WAVE files for reading 
int wavefile_r::open(std::string fname) { 
	int N;
	char c[4];
	size_t count;
	
	// open the file
	if((fid = fopen(fname.c_str(), "rb")) == NULL) return(-1);
	else is_open = true;

	// Check Wave header 
	count = fread(c, 1, 4, fid);
	if(strncmp(c, "RIFF", 4)) return(-1);
	count = fread(c, 1, 4, fid);
	count = fread(c, 1, 4, fid);
	if(strncmp(c, "WAVE", 4)) return(-1);
	// format chunk 
	count = fread(c, 1, 4, fid);	
	while(strncmp(c, "fmt ", 4)) {
	  if(fread(c, 1, 4, fid) == 0) return(-1); 
	  N = (int)read_uint32(c);	
	  while(N>0) {					
			if(fread(c, 1, 1, fid) == 0) return(-1);
			N--;
	  }
	  if(fread(c, 1, 4, fid) == 0) return(-1);
	}
	// Parse format chunk 
	count = fread(c, 1, 4, fid);
	N = (int)read_uint32(c);     
	count = fread(c, 1, 2, fid);
	if(read_uint16(c) == 0x0003) {
	  is_float = true;
	} else {
	  is_float = false;
		return (-1);
	}

	count = fread(c, 1, 2, fid);	
	int channels = (int)read_uint16(c);
	if (channels != 1) return(-1);
	count = fread(c, 1, 4, fid);
	sample_rate = (int)read_uint32(c);
	count = fread(c, 1, 4, fid);
	count = fread(c, 1, 2, fid);
	count = fread(c, 1, 2, fid);
	bits_per_sample = (int)read_uint16(c);

	N = N - 16;
	while(N>0) {
	  if(fread(c, 1, 1, fid) == 0) return(-1);
	  N--;
	}
	
	//data chunk 
	count = fread(c, 1, 4, fid);	
	while(strncmp(c, "data", 4)) {	
	  if(fread(c, 1, 4, fid) == 0) return(-1);
	  N = (int)read_uint32(c);	
	  while(N>0) {					// skip over
			if(fread(c, 1, 1, fid) == 0) return(-1);
      N--;
	  }
	  if(fread(c, 1, 4, fid) == 0) return(-1);// next chunkid
	}

	// Data chunk 
	if(fread(c, 1, 4, fid) == 0) return(-1); 
	num_samples = (long)read_uint32(c) / ((bits_per_sample / 8) * channels);

	//std::cout << "Opened WaveFile " << fname.c_str() << " with "  << num_samples << " samples\n";
	return(1);
}
// Reading samples from a WAVE File (to doubles in [-1,1]) 
int wavefile_r::read_sample(float& left) {
  int done=0;
  float cflt;
	if (fread((void*)(&cflt), 1, sizeof(float), fid) == 0) {
		done = 1;
		// we've reached the end of the file 
	} else {
		left = cflt;
  }
	
  return(done);
}

int wavefile_r::read_samples(float& left, int samples) {
  int done=0;
	if (fread((void*)(&left), sizeof(float), samples, fid) == 0) {
		done = 1;
		// we've reached the end of the file 
  }
  return(done);
}

