//#include <iostream>
//#include <string>
//#include <unordered_set>
//#include <ctime>	
//
//#include "../src/utils/stdExtension.hpp"
//#include "../src/dataprocessing/StopWords.h"
//#include "../src/dataprocessing/Documents.hpp"
//#include "../src/utils/StringUtil.hpp"
//
//#define random(K) int(std::rand()%K)  
//int main() {
//	std::string stopWordsFilePath="D:\\study\\CPlusPlusProjects\\LDA_C++\\LDA_C++\\data\\StopWordDic\\StopWords.dic";
//	std::cout << StopWords::stopWordsSet << std::endl;
//	std::string exampleOfStopWord{ "least" };
//	auto booool= StopWords::stopWordsSet.find(exampleOfStopWord) == StopWords::stopWordsSet.end() ? 0 : 1;
//	std::cout<<"\nfind the word \""<<exampleOfStopWord<<"\" in stopWordsSet? " << (booool?"Yes!":"No!!!") << "\n";
//
//
//	Documents docs;
//	std::string documentsPath="D:\\study\\CPlusPlusProjects\\LDA_C++\\LDA_C++\\data\\LdaOriginalDocs";
//	std::vector<std::string> fileNames;
//	docs.getAllFiles(documentsPath, fileNames);
//	std::cout << fileNames << std::endl;
//
//	docs.readDocs(documentsPath);		// debug和realease模式速度差好多啊
//
//
//	system("Pause");
////
//std::vector<std::vector<int>> randVec;
//randVec.resize(5);
//srand((unsigned)time(NULL));
//for (size_t i{}; i < 5; i++) {
//	randVec.at(i).resize(6);
//	for (size_t j{}; j < 6; ++j) {
//		randVec[i][j] = random(10);
//	}
//}
//std::cout << randVec << "\n";
//	//std::string srcString = " Apple Banana JD Baidu ";
//	//auto trimRes = StringUtil::Trim(srcString);
//	//std::cout<<trimRes<< std::endl;
//	//auto splitRes = StringUtil::split(trimRes);
//	//std::cout << splitRes << std::endl;
//	//StringUtil::batchToLower(splitRes);
//	//std::cout << splitRes << std::endl;
//	//StringUtil::batchToUpper(splitRes);
//	//std::cout << splitRes << std::endl;
//
//	//std::string srcString2 = "  We are using LDA in CPlusPlus! ";
//	//std::vector<std::string> splitRes2;
//	//StringUtil::tokenizeAndLowerCase(srcString2,splitRes2);
//	//std::cout << splitRes2 << std::endl;
//
//	//std::string srcString3 = "  THE TEST FOR　TRIM AND ToLOwer! ";
//	//StringUtil::Trim(StringUtil::toLower(srcString3));
//	//std::cout << srcString3 << std::endl;
//
//
//	//size_t count = 0;
//	//std::vector<int> intVec{ 1,2,3,4,5,6,7,8,9,10 };
//	//std::copy_if(intVec.begin(), intVec.end(), intVec.begin(),
//	//					   [&](int num)->bool {	return (num % 2==0?(++count,1):(0)); });
//	//intVec.resize(count); // 确保下次循环前初始化为0 
//	//std::cout << intVec << std::endl;
//
//	//std::vector<int> vvv;
//	//vvv.resize(11);
//	//vvv[10] = 10; // vector在任意位置上插入数之前必须确保该位置上已经申请到内存并构造了对象
//	//std::cout << vvv << std::endl;
//
//
//
//
//}