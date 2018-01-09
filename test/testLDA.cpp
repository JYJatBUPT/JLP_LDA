#include <iostream>
#include <string>

#include <random>

#include "../src/core/model_params.h"
#include "../src/core/lda_model.hpp"

#include "../src/utils/stdExtension.hpp"
#include "../src/dataprocessing/StopWords.h"
#include "../src/dataprocessing/Documents.hpp"


int main() {
	// set file path
	std::string stopWordsPath =	  "D:\\study\\CPlusPlusProjects\\LDA_C++\\LDA_C++\\data\\StopWordDic\\StopWords.dic";
	std::string documentsPath =	  "D:\\study\\CPlusPlusProjects\\LDA_C++\\LDA_C++\\data\\LdaOriginalDocs";
	std::string resPath=				  "D:\\study\\CPlusPlusProjects\\LDA_C++\\LDA_C++\\data\\LdaOutputResults";
	std::string ModelParamsPath = "D:\\study\\CPlusPlusProjects\\LDA_C++\\LDA_C++\\data\\LdaParameter\\LdaParameters.txt";
	// get model params
	ModelParams ldaParams(ModelParamsPath);
	std::cout <<"topic number setting: "<< ldaParams.topicNum << std::endl;
	// process documents
	Documents docs;
	docs.readDocs(documentsPath);		// debug和realease模式速度差好多啊
	std::cout << "\n\nthe dictionary size: " << docs.termToIndexMap.size() << "\n";
	std::cout << ((docs.termToIndexMap.size() < 8000) ? "The size of dictionary is ok!" :
								"The size of dictionary is too big,and the dimension should be reduced!!!") << "\n";
	
	// train LDA Model
	LDAModel model(ldaParams);
	// train stage 1
	std::cout << "1 Initialize the model ...\n";
	model.initModel(docs);
	// train stage 2
	std::cout << "2 Learning the model ...\n";
	model.trainModel(docs);
	// train stage 3
	std::cout << "3 Output the trained model ...\n";
	model.saveIteratedModel(ldaParams.iterations,docs);
	std::cout << "Congrats!!!\n";


	system("Pause");
}