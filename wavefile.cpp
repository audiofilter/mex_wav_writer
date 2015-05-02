#include "wavefile.h"
#include <math.h>
#include <iostream>
// Copyright (c) 2015, Tony Kirke. License: MIT License (http://www.opensource.org/licenses/mit-license.php)

void write4u(unsigned long x, char *c)
{
	unsigned char *uc = (unsigned char *)c;
	uc[3] = (unsigned char) ((x >> 24) & 0xffUL);
	uc[2] = (unsigned char) ((x >> 16) & 0xffUL);
	uc[1] = (unsigned char) ((x >> 8) & 0xffUL);
	uc[0] = (unsigned char) (x & 0xffUL);
}
// Opening WAVE files for writing  
int wavefile::open(std::string fnme, long sample_r)  { 
	char c[4];
	fname = fnme;
	num_samples = 0;
	sample_rate = sample_r;
	// open the file 
	if((fid = fopen(fname.c_str(), "wb")) == NULL) return(-1);
	else is_open = true;
  uint32_t data_len = 44; // update later
  long byte_rate = sample_rate * 16.0 * 2/8;
  uint32_t hdrSize = 44;
  char *hdr = new char[hdrSize];
  hdr[0] = 'R';
  hdr[1] = 'I';
  hdr[2] = 'F';
  hdr[3] = 'F';
  hdr[4] = (char) (data_len & 0xff);
  hdr[5] = (char) ((data_len >> 8) & 0xff);
  hdr[6] = (char) ((data_len >> 16) & 0xff);
  hdr[7] = (char) ((data_len >> 24) & 0xff);
  hdr[8] = 'W';
  hdr[9] = 'A';
  hdr[10] = 'V';
  hdr[11] = 'E';
  hdr[12] = 'f';
  hdr[13] = 'm';
  hdr[14] = 't';
  hdr[15] = ' ';
  hdr[16] = 16;
  hdr[17] = 0;
  hdr[18] = 0;
  hdr[19] = 0;
  hdr[20] = 3; // 3 == float
  hdr[21] = 0;
  hdr[22] = (char) 1; // single channel
  hdr[23] = 0;
  hdr[24] = (char) (sample_rate & 0xff);
  hdr[25] = (char) ((sample_rate >> 8) & 0xff);
  hdr[26] = (char) ((sample_rate >> 16) & 0xff);
  hdr[27] = (char) ((sample_rate >> 24) & 0xff);
  hdr[28] = (char) (byte_rate & 0xff);
  hdr[29] = (char) ((byte_rate >> 8) & 0xff);
  hdr[30] = (char) ((byte_rate >> 16) & 0xff);
  hdr[31] = (char) ((byte_rate >> 24) & 0xff);
  hdr[32] = (char) (2 * 8 / 8);  // align
  hdr[33] = 0;
  hdr[34] = bits_per_sample;
  hdr[35] = 0;
  hdr[36] = 'd';
  hdr[37] = 'a';
  hdr[38] = 't';
  hdr[39] = 'a';
  hdr[40] = 0;
  hdr[41] = 0;
  hdr[42] = 0;
  hdr[43] = 0;
  fwrite((char *)hdr, 1, hdrSize, fid);
  delete[] hdr;
	return(0);
}

// Closing a wave file (updates the header)
int wavefile::close() {
  fclose(fid);
	
  long len = num_samples * (bits_per_sample / 8);

  if((fid = fopen(fname.c_str(), "r+b"))==NULL) 
		return(-1);				// failed to re-open that file for update

  fseek(fid, 4, SEEK_SET);

	// Now write actual len and re-close
  char c[4];
  write4u((unsigned long)len + 0x24, c);	fwrite(c, 1, 4, fid);					
  fseek(fid, 40, SEEK_SET);
  write4u((unsigned long)len, c );  fwrite(c, 1, 4, fid);	
  is_open = fclose(fid);
	return(0);
}

void wavefile::write(float audio) {
	std::cout << "Sample = " << audio << "\n";
	fwrite(&audio, sizeof(float), 1, fid);
  num_samples++;
}
void wavefile::write(const float *audio, int samples) { 
	fwrite(&audio[0], sizeof(float), samples, fid);
	num_samples += samples;
}
