#ifndef LDA_DOCUMENTS_H_
#define LDA_DOCUMENTS_H_

#include <vector>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <io.h>			//help accessing all filenames under the specific dictionary
#include <fstream>

#include "../dataprocessing/StopWords.h"
#include "../src/utils/FileUtil.hpp"
#include "../src/utils/StringUtil.hpp"

class Document{
public:
	typedef std::unordered_map<std::string, int> Map; // int long??? 
	typedef std::unordered_set<std::string> StringSet;
public:
	std::string docName;	     //save the absolute path of this document
	std::vector<int> docWords; //保存本篇文档的有效word(i.e. 在去除停用词后)本身在termToIndexMap中的ID
public:
	explicit Document(std::string& docName,
										Map& termToIndexMap,
										std::vector<std::string>& indexToTermMap,
										Map& termCountMap) 
	{
		this->docName = docName;
		// read file and initialize word index array
		std::vector<std::string> docLines;				// 新建docLines
		FileUtil::readLines(docName, docLines);
		
		//!!! 以下5行代码是性能瓶颈段---特别慢 !!! 
		std::vector<std::string> words;			// 新建words
		//words.reserve(10000);  //提前分配内存 貌似还变慢了????
		for (auto& aLine : docLines) {
			StringUtil::tokenizeAndLowerCase(aLine, words);
		}

		std::cout << "before text normalization: the words size:"<<words.size() << std::endl;
		// delete stopWords and noiseWords  本质就是个filter操作
		size_t count = 0;
		std::copy_if(words.begin(),
								 words.end(),
								 words.begin(),
								 [&](std::string& str)->bool
								 {
										if (str.length() <= 1								// delete single character
											  || StopWords::isContains(str)		// delete stopWords
										  	|| isNoiseWord(str))
										{										  	
										  	return false;
										}
										else
										{
											++count;
											return true;
										}
								 }
		);
		words.resize(count);
		std::cout << "after text normalization: the words size:" << words.size() << std::endl;

		this->docWords.reserve(words.size());
		for (size_t i{}; i < words.size(); ++i) {
			std::string word = words.at(i);
			if (termToIndexMap.find(word) == termToIndexMap.end()) {
				size_t newId = termToIndexMap.size();
				termToIndexMap[word] = newId;
				indexToTermMap.push_back(word);
				termCountMap[word] = 1;

				docWords.resize(i + 1);   // vector在任意位置上插入数之前必须确保该位置上已经申请到内存并构造了对象
				this->docWords[i] = newId;
			}
			else{
				docWords.resize(i + 1); // vector在任意位置上插入数之前必须确保该位置上已经申请到内存并构造了对象
				docWords[i] = termToIndexMap.at(word);
				// update word counts
				termCountMap[word]= termCountMap.at(word) + 1;
			}
		}
	

		words.clear();
	}

	bool isNoiseWord( std::string& word) {
		StringUtil::Trim(StringUtil::toLower(word));
		/* TODO */
		return false;
	}

};


class Documents
{
public:
	typedef std::unordered_map<std::string,int> Map; // int long 
	typedef std::unordered_set<std::string> StringSet;
public:
	std::vector<std::shared_ptr<Document> > docs; // 
	Map termToIndexMap;
	std::vector<std::string> indexToTermMap;
	Map termCountMap;
public:
	explicit Documents() //!!!在ctr中不允许初始化常量
	{
		std::cout << "\n!!!\nthe class Documents initializing...\n!!!\n" << std::endl;
	}

public:
	void readDocs(std::string docsPath) 
	{
		int i = 0;
		std::vector<std::string> docFileNames;
		getAllFiles(docsPath, docFileNames); //得到由该路径指定的文件夹下的所有文件名的绝对路径,存入容器docFileNames

		for (auto fileName : docFileNames) {
			Document doc(fileName, termToIndexMap, indexToTermMap, termCountMap);
			docs.push_back(std::make_shared<Document>(doc));
			++i; 
			std::cout << "this is " << i << "th document";	
			//词典维度不能太高 8000(具体数字通过多次实验来确定)以下合适 (维度高了就再删除一些垃圾特征词)
		}

	}

	// 只读取某给定路径下的所有文件名(即包含当前目录及子目录的文件)
	void getAllFiles(std::string path, std::vector<std::string>& files) 
	{
		long hFile = 0; // 文件句柄
		struct _finddata_t fileinfo; // 文件信息
		std::string p;
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		{
		   do{
					if ((fileinfo.attrib & _A_SUBDIR)) {
							if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						    //files.push_back(p.assign(path).append("\\").append(fileinfo.name));
								getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
							}
					}
					else {
							files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}


};


#endif
