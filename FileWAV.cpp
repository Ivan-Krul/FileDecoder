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
	
	if(typename_ == 1 || typename_ == 2 || typename_ == 4)
		_bitpersampleselect = typename_;
	else 
		_bitpersampleselect = 4;
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
	
	uint32_t buf = 36+ _samplecount * _numchannels * _bitpersampleselect;
	uint16_t buf1;
	fout << "RIFF" <<reinterpret_cast<char *>(&buf)<<"WAVEfmt ";
	buf = 16;
	fout <<reinterpret_cast<char *>(&buf);
	buf = 1;
	fout <<reinterpret_cast<char *>(&buf);
	fout <<reinterpret_cast<char *>(&_numchannels);
	fout <<reinterpret_cast<char *>(&_samplerate);
	buf = _samplerate * _numchannels * _bitpersampleselect;
	fout <<reinterpret_cast<char *>(&buf);
	buf = _numchannels * _bitpersampleselect;
	fout <<reinterpret_cast<char *>(&buf);
	buf1 = _numchannels * _bitpersampleselect;
	fout <<reinterpret_cast<char *>(&buf1);
	fout <<reinterpret_cast<char *>(&_bitpersampleselect);
	buf1 = 0;
	fout <<reinterpret_cast<char *>(&buf1);
	fout<<"data";
	buf = _samplecount * _numchannels * _bitpersampleselect;
	fout <<reinterpret_cast<char *>(&buf);
	for(int i = 0; i < _samplecount; i++)
		if(_bitpersampleselect == 1)
			fout <<reinterpret_cast<char *>(&_ptr._8BSample[i]);
		else if(_bitpersampleselect == 2)
			fout <<reinterpret_cast<char *>(&_ptr._16BSample[i]);
		else
			fout <<reinterpret_cast<char *>(&_ptr._32BSample[i]);
	fout.close();
}

void FileWAV::destroy()
{
	if(_bitpersampleselect == 1)
		delete[] _ptr._8BSample;
	else if(_bitpersampleselect == 2)
		delete[] _ptr._16BSample;
	else
		delete[] _ptr._32BSample;
}
