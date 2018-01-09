#ifndef LDA_MODELPARAMS_H_
#define LDA_MODELPARAMS_H_

#include <vector>
#include <string>
#include <unordered_map> 

#include "../utils/FileUtil.hpp"
#include "../utils/StringUtil.hpp"

class ModelParams {
public:
	double alpha;	// �Ƽ�ֵ 50/topicNum
	double beta;		// �Ƽ�ֵ 0.1f
	size_t topicNum;
	size_t iterations;
	size_t saveGapStep;
	size_t startSaveIteration;
public:
	explicit ModelParams(const std::string& ModelParamspath) {
		// TODO:���ģ�Ͳ����ļ��Ľ���
		// ModelParamspath = "D:\\study\\CPlusPlusProjects\\LDA_C++\\LDA_C++\\data\\LdaParameter\\LdaParameters";
		//	std::vector<std::string> Lines;
		// FileUtil::readLines(ModelParamspath, Lines);
		
		// ��ʱ���������ģ�͵ĳ�����
		this->alpha = 0.5;
		this->beta = 0.1;
		this->topicNum = 9;
		this->iterations = 500;
		this->saveGapStep = 100;
		this->startSaveIteration = 200;
	}
};


#endif
