f = 0.0025;
sample_rate = 48000;
len = sample_rate; % i.e 1 second

data = 0.35*sin(2*pi*f*(1:len/2));
dataf = single(data);

% Write 1/2 second of ~ 100 Hz tone
wav_writer('t1.wav', sample_rate, dataf);

% Write 1/2 second of 0
data = 0.0*sin(2*pi*f*(1:len/2));
dataf = single(data);

wav_writer('t1.wav', sample_rate, dataf);
wav_writer('t2.wav', sample_rate, dataf);

% Write 1/2 second of ~ 100 Hz tone
data = 0.35*sin(2*pi*f*(1:len/2));
dataf = single(data);

wav_writer('t2.wav', sample_rate, dataf);

% diff should be .35
diff = wav_compare('t1.wav','t2.wav')
