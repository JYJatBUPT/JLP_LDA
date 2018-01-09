#ifndef LDA_STOP_WORDS_H_
#define LDA_STOP_WORDS_H_

#include <fstream> 
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

class StopWords		//TODO:改造成单例模式
{
public:
	static std::unordered_set<std::string> stopWordsSet;
public:
	static bool isContains(std::string& target) {
		return stopWordsSet.find(target) == stopWordsSet.end() ? false : true;
	}
public:
	static std::unordered_set<std::string> readFromFile()
	{
		std::string filePath= "D:\\study\\CPlusPlusProjects\\LDA_C++\\LDA_C++\\data\\StopWordDic\\StopWords.dic";
		std::ifstream reader(filePath);
		if (!reader){
			std::cout << __DATE__ << " " << __TIME__<<" "
				 			<< __FILE__ << " " << __LINE__
							<<": stopWordsDic read error" << std::endl;
			exit(-1);
		}

		std::unordered_set<std::string> stopWordsSet;
		std::string aLine;
		while (getline(reader, aLine))
		{
			stopWordsSet.insert(aLine);
		}
		reader.close();
		return stopWordsSet;
	}
};

std::unordered_set<std::string> StopWords::stopWordsSet= readFromFile();

#endif

