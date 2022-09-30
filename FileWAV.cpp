#include "FileWAV.h"

void FileWAV::create(char typename_, uint32_t samplecount_, uint16_t channels_)
{
	_samplecount = samplecount_;
	_numchannels = channels_;
	if(typename_ == 1)
		_ptr._8BSample = new char[_samplecount * _numchannels];
	else if(typename_ == 2)
		_ptr._16BSample = new short[_samplecount * _numchannels];
	else
		_ptr._32BSample = new float[_samplecount * _numchannels];
	_bitpersampleselect = typename_;
}

void FileWAV::setsamplerate(uint32_t samplerate_)
{
	_samplerate = samplerate_;
}

uint32_t FileWAV::size()
{
	return _samplecount;
}

char &FileWAV::sample8(uint32_t index_)
{
	if(!(index_ < _samplecount))
		abort();
	return _ptr._8BSample[index_];
}

short &FileWAV::sample16(uint32_t index_)
{
	if(!(index_ < _samplecount))
		abort();
	return _ptr._16BSample[index_];
}

float &FileWAV::sample32(uint32_t index_)
{
	if(!(index_ < _samplecount))
		abort();
	return _ptr._32BSample[index_];
}

void FileWAV::save(std::string dir_)
{
	std::ofstream fout;
	fout.open(dir_,std::ios::out | std::ios::binary);
	
	
	
	fout.close();
}

void FileWAV::destroy()
{
	if(typename_ == 1)
		delete[] _ptr._8BSample;
	else if(typename_ == 2)
		delete[] _ptr._16BSample;
	else
		delete[] _ptr._16BSample;
}
