#pragma once

#include <fstream>

/////////////////////////////////////////////////
// \brief 
//	Class that helps us to read lines from file.
// 
/////////////////////////////////////////////////
class FileReader
{
private:
	std::string path;
	std::ifstream file;

public:
	FileReader() = default;

	FileReader(const std::string& path);

	~FileReader();

public:
	/////////////////////////////////////////////////
	// \brief
	//			Open the file stream.
	// 
	/////////////////////////////////////////////////
	void Open(const std::string& path);

	/////////////////////////////////////////////////
	// \brief
	//			Close the file stream.
	// 
	/////////////////////////////////////////////////
	void Close();

	/////////////////////////////////////////////////
	// \brief
	//			Reset the file stream.
	// 
	/////////////////////////////////////////////////
	void Reset();

	/////////////////////////////////////////////////
	// \brief
	//	  Return true if the file stream is open
	//    otherwise - false.
	// 
	/////////////////////////////////////////////////
	bool IsOpen() const;

	/////////////////////////////////////////////////
	// \brief
	//	  Return true if we came to the end of 
	//    the file otherwise - false.
	// 
	/////////////////////////////////////////////////
	bool IsEnd() const;

	/////////////////////////////////////////////////
	// \brief
	//		Reads the line from the stream and
	//		returns it.
	// 
	/////////////////////////////////////////////////
	std::string ReadLine();

	/////////////////////////////////////////////////
	// \brief
	//		Reads the line under the index from
	//      the stream and returns it.
	// 
	/////////////////////////////////////////////////
	std::string ReadLine(size_t index);

	/////////////////////////////////////////////////
	// \brief
	//	  Retun the number of lines in the file.
	// 
	/////////////////////////////////////////////////
	size_t GetCountOfLines();

public:
	/////////////////////////////////////////////////
	// \brief
	//		Reads the line under the index from
	//      the stream and returns it.
	// 
	/////////////////////////////////////////////////
	std::string operator[](size_t index);
};
