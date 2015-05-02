matwav
======

From matlab open and write chunks of 'float' data to single channel floating point .wav files
1st call with a particular file name will open the file and write audio data to it,
subsequent ones will just write audio data,
upon octave/matlab close, the .wav files will be closed
They can also be closed by setting sample rate to a negative number

This requires mex-it library, c++11 compiler, octave and cmake

for example call like this

wav_writer('test.wav', 48000, float_data)

Example in test_wav_writer.m

====
This expects mex-it to be one directory level above this file, if in other location, then
modify CMakeLists.txt MEX_IT_DIR variable