#ifndef LDA_MODELPARAMS_H_
#define LDA_MODELPARAMS_H_

#include <vector>
#include <string>
#include <unordered_map> 

#include "../utils/FileUtil.hpp"
#include "../utils/StringUtil.hpp"

class ModelParams {
public:
	double alpha;	// 推荐值 50/topicNum
	double beta;		// 推荐值 0.1f
	size_t topicNum;
	size_t iterations;
	size_t saveGapStep;
	size_t startSaveIteration;
public:
	explicit ModelParams(const std::string& ModelParamspath) {
		// TODO:完成模型参数文件的解析
		// ModelParamspath = "D:\\study\\CPlusPlusProjects\\LDA_C++\\LDA_C++\\data\\LdaParameter\\LdaParameters";
		//	std::vector<std::string> Lines;
		// FileUtil::readLines(ModelParamspath, Lines);
		
		// 暂时在这里调整模型的超参数
		this->alpha = 0.5;
		this->beta = 0.1;
		this->topicNum = 9;
		this->iterations = 500;
		this->saveGapStep = 100;
		this->startSaveIteration = 200;
	}
};


#endif
