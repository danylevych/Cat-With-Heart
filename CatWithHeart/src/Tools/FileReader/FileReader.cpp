#include "FileReader.h"

#include <string>
#include <iostream>
#include <iterator>
#include <locale>
#include <codecvt>


FileReader::FileReader(const std::string& path)
	: path(path)
	, file(path)
{	}

FileReader::~FileReader()
{
	Close();
}

void FileReader::Open(const std::string & path)
{
	this->path = path;
	file.open(path);
}

void FileReader::Close()
{
	if (file.is_open())
	{
		file.close();
	}
}

void FileReader::Reset()
{
	Close();
	
	if (!path.empty()) // Reopen the file.
	{
		file.open(path);
	}
}

bool FileReader::IsOpen() const
{
	return file.is_open();
}

bool FileReader::IsEnd() const
{
	return file.eof();
}

std::string FileReader::ReadLine()
{
	std::string line;
	std::getline(file, line);
	return line;
}

std::string FileReader::ReadLine(size_t index)
{
	return operator[](index);
}

size_t FileReader::GetCountOfLines()
{
	size_t count = std::count(std::istreambuf_iterator<char>(file),
							  std::istreambuf_iterator<char>(), '\n');

	Reset(); // Set the position of cursor to begin of the file.

	return count;
}

std::string FileReader::operator[](size_t index)
{
	for (size_t i = 0; !file.eof(); i++)
	{
		if (i == index) // We find the line.
		{
			return ReadLine();
		}

		ReadLine();
	}

	return std::string(); // If there is no line with the index.
}
