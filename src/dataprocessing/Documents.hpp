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
	std::vector<int> docWords; //���汾ƪ�ĵ�����Чword(i.e. ��ȥ��ͣ�ôʺ�)������termToIndexMap�е�ID
public:
	explicit Document(std::string& docName,
										Map& termToIndexMap,
										std::vector<std::string>& indexToTermMap,
										Map& termCountMap) 
	{
		this->docName = docName;
		// read file and initialize word index array
		std::vector<std::string> docLines;				// �½�docLines
		FileUtil::readLines(docName, docLines);
		
		//!!! ����5�д���������ƿ����---�ر��� !!! 
		std::vector<std::string> words;			// �½�words
		//words.reserve(10000);  //��ǰ�����ڴ� ò�ƻ�������????
		for (auto& aLine : docLines) {
			StringUtil::tokenizeAndLowerCase(aLine, words);
		}

		std::cout << "before text normalization: the words size:"<<words.size() << std::endl;
		// delete stopWords and noiseWords  ���ʾ��Ǹ�filter����
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

				docWords.resize(i + 1);   // vector������λ���ϲ�����֮ǰ����ȷ����λ�����Ѿ����뵽�ڴ沢�����˶���
				this->docWords[i] = newId;
			}
			else{
				docWords.resize(i + 1); // vector������λ���ϲ�����֮ǰ����ȷ����λ�����Ѿ����뵽�ڴ沢�����˶���
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
	explicit Documents() //!!!��ctr�в������ʼ������
	{
		std::cout << "\n!!!\nthe class Documents initializing...\n!!!\n" << std::endl;
	}

public:
	void readDocs(std::string docsPath) 
	{
		int i = 0;
		std::vector<std::string> docFileNames;
		getAllFiles(docsPath, docFileNames); //�õ��ɸ�·��ָ�����ļ����µ������ļ����ľ���·��,��������docFileNames

		for (auto fileName : docFileNames) {
			Document doc(fileName, termToIndexMap, indexToTermMap, termCountMap);
			docs.push_back(std::make_shared<Document>(doc));
			++i; 
			std::cout << "this is " << i << "th document";	
			//�ʵ�ά�Ȳ���̫�� 8000(��������ͨ�����ʵ����ȷ��)���º��� (ά�ȸ��˾���ɾ��һЩ����������)
		}

	}

	// ֻ��ȡĳ����·���µ������ļ���(��������ǰĿ¼����Ŀ¼���ļ�)
	void getAllFiles(std::string path, std::vector<std::string>& files) 
	{
		long hFile = 0; // �ļ����
		struct _finddata_t fileinfo; // �ļ���Ϣ
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
