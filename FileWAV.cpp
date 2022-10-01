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
	
	char *buffer;
	uint32_t buf = 36+ _samplecount * _numchannels * _bitpersampleselect;
	fout << "RIFF";
	buffer = (char *)&buf;
	for(int i = 0;i< 4;i++)
		fout << buffer[i];
	fout <<"WAVEfmt ";
	buf = 16;
	for(int i = 0;i< 4;i++)
		fout << buffer[i];
	buf = 1;
	for(int i = 0;i< 2;i++)
		fout << buffer[i];
	buffer = (char *)&_numchannels;
	for(int i = 0;i< 2;i++)
		fout << buffer[i];
	buffer = (char *)&_samplerate;
	for(int i = 0;i< 4;i++)
		fout << buffer[i];
	buf = _samplerate * _numchannels * _bitpersampleselect;
	buffer = (char *)&buf;
	for(int i = 0;i< 4;i++)
		fout << buffer[i];
	buf = _numchannels * _bitpersampleselect;
	for(int i = 0;i< 2;i++)
		fout << buffer[i];
	buf = _numchannels * _bitpersampleselect;
	for(int i = 0;i< 2;i++)
		fout << buffer[i];
	buffer = (char *)&_bitpersampleselect;
	for(int i = 0;i< 2;i++)
		fout << buffer[i];
	buf = 0;
	buffer = (char *)&buf;
	for(int i = 0;i< 2;i++)
		fout << buffer[i];
	fout<<"data";
	buf = _samplecount * _numchannels * _bitpersampleselect;
	for(int i = 0;i< 4;i++)
		fout << buffer[i];
	if(_bitpersampleselect == 1)
		buffer = (char *)_ptr._8BSample;
	else if(_bitpersampleselect == 2)
		buffer = (char *)_ptr._16BSample;
	else
		buffer = (char *)_ptr._32BSample;
	
	for(int i = 0; i < _samplecount*2; i++)
	{
		std::cout<<i<<' '<<short(buffer[i])<<'\n';
		fout << buffer[i];
	}

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
