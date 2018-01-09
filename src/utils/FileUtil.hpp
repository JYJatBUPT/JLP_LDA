#ifndef LDA_FILE_UTIL_H_
#define LDA_FILE_UTIL_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class FileUtil {
public:
	static void readLines(const std::string& filePath, std::vector<std::string>& Lines) 
	{
		std::ifstream reader(filePath);
		if (!reader) {
			std::cout << __DATE__ << " " << __TIME__ << " "
				<< __FILE__ << " " << __LINE__
				<< "File read error!!!" << std::endl;
			exit(-1);
		}

		std::string aLine;
		while (getline(reader, aLine))
		{
			Lines.push_back(aLine);
		}
		reader.close();
	}

};


#endif
