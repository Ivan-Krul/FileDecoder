/*
Disassembly format WAV
4 ChunkID -> "RIFF"
4 ChunkSize -> 36+SubChunk2Size
4 Format -> "WAVE"

4 Subchunk1ID -> "fmt "
4 Subchunk1Size -> 16
2 AudioFormat -> 1
2 NumChannels -> 1(mono)/2(stereo)
4 SampleRate -> 8000, 44100
4 ByteRate -> SampleRate * NumChannels * BitsPerSample / 8
2 BlockAlign -> NumChannels * BitsPerSample / 8
2 BitsPerSample -> 8,16,32(bits per one sample)
2 ExtraParamSize -> 0

4 Subchunk2ID -> "data"
4 SubChunk2Size -> (count of samples) * NumChannels * BitsPerSample / 8
X (just data)
*/
#pragma once
#include <fstream>
namespace Filewav
{
	union SamplePointer
	{
		char *_8BSample;
		short *_16BSample;
		float *_32BSample;
	};
};
class FileWAV
{
	uint8_t 				_bitpersampleselect;
	uint32_t				_samplecount;
	Filewav::SamplePointer	_ptr;
	uint32_t				_samplerate = 44100;
	uint16_t				_numchannels;
public:
	FileWAV() = default;
	FileWAV(char typename_, uint32_t samplecount_, uint16_t channels_) { create(typename_,samplecount_,channels_); }
	void create(char typename_, uint32_t samplecount_, uint16_t channels_);
	void setsamplerate(uint32_t samplerate_);
	uint32_t size();
	char &sample8(uint32_t index_);
	short &sample16(uint32_t index_);
	float &sample32(uint32_t index_);
	void save(std::string dir_);
	void destroy();
	~FileWAV() { destroy(); }
}
#include "FileWAV.cpp"