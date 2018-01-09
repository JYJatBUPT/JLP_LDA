#ifndef LDA_LDAMODEL_H_
#define LDA_LDAMODEL_H_

#include <ctime> /* random(K)*/
#include <vector>
#include <memory>
#include "../dataprocessing/Documents.hpp"

#define random(K) int(std::rand()%K)  

class LDAModel {
public:
	typedef std::vector<std::vector<int> > IntMat;
	typedef std::vector<std::vector<double>> DoubleMat;
	typedef std::vector<int> IntVec;
public:
	double alpha;   	// doc-topic dirichlet prior param
	double beta;      // topic-word dirichlet prior param
	size_t K, V, M;   // topic number,vocabulary size,document number
	IntMat nmk;       // nmk[i][j] the number of times any word from document i has been assigned to topic j.
	IntMat nkt;       // nkt[i][j] the number of times word v has been assigned to topic k in all documents
	IntVec nmkSum;    // 文本i的长度，i.e. 等于 Sum(nmk[i][j]),j=1...K 
	IntVec nktSum;  	// the number of words assigned to topic k , i.e. 等于 Sum(nkt[i][j]),j=1...V
	IntMat doc;       // doc[i][j] represent the identity in vocabulary for j'th word in i'th document.
	IntMat z;         // z[i][j] represent the topic assignment of j-th word in i-th document.

	DoubleMat theta;	// theta[m][k]对应公式(27.37)的第一项 p(topic|doc) 这个与具体的训练文档有关 对理解新文档无帮助
	DoubleMat phi;		//   phi[k][v]对应公式(27.37)的第二项 p(word|topic) 取Gibbs Sampling收敛之后的n个迭代的结果的平均值当做估计参数  
	
	size_t iterations;
	size_t saveGapStep;
	size_t startSaveIteration;
public:
	explicit LDAModel(const ModelParams& ldaParams)
	{
		this->alpha = ldaParams.alpha;
		this->beta = ldaParams.beta;
		this->K = ldaParams.topicNum;
		this->iterations = ldaParams.iterations;
		this->saveGapStep = ldaParams.saveGapStep;
		this->startSaveIteration = ldaParams.startSaveIteration;
	}
public:
	void initModel(const Documents& docSet)
	{
		this->M = docSet.docs.size();
		this->V = docSet.termToIndexMap.size();
		// 共同初始化
		this->nmk.resize(M); this->theta.resize(M);
		for (size_t m{}; m < M; ++m) { nmk.at(m).resize(K); theta.at(m).resize(K); }
		this->nkt.resize(K); this->phi.resize(K);
		for (size_t k{}; k < K; ++k) { nkt.at(k).resize(V); phi.at(k).resize(V); }
		this->nmkSum.resize(M);
		this->nktSum.resize(K);

		// Initialize word-doc matrix, where doc[i][j] represent the integral ID of j-th word in i-th document.
		this->doc.resize(M);
		for (size_t m{}; m < M; ++m)
		{
			size_t N = docSet.docs.at(m)->docWords.size();
			doc.at(m).resize(N);
			for (size_t n{}; n < N; ++n) {
				doc[m][n] = docSet.docs.at(m)->docWords.at(n);
			}
		}
		// Initialize topic-doc matrix,where z[i][j] represent the topic assignment of j-th word in i-th document.
		srand((unsigned)time(NULL));
		this->z.resize(M);
		for (size_t m{}; m < M; ++m)
		{
			size_t N = docSet.docs.at(m)->docWords.size();
			z.at(m).resize(N);
			for (size_t n{}; n < N; ++n) {
				int initTopic = random(K);
				z[m][n] = initTopic;
				++nmk[m][initTopic];
				++nkt[initTopic][doc[m][n]];
				++nktSum[initTopic];
			}
			nmkSum[m] = N;
		}

	}

	void trainModel(const Documents& docSet)
	{
		if (iterations < saveGapStep + startSaveIteration) {
			std::cerr << "Error: the number of total iterations should be larger than" << (saveGapStep + startSaveIteration) << std::endl;
			exit(-1);
		}
		for (size_t i{}; i < iterations; ++i) {
			std::cout << "Iteration " << i << "th Step:\n";
			if ((i >= startSaveIteration) && ((i - startSaveIteration) % saveGapStep == 0)) {
				std::cout << "Saving model at iteration " << i << "-th step ...\n";

				updateEstimatedParams();

				saveIteratedModel(i, docSet);
			}

			// 使用collapsed Gibbs采样更新 z[][]
			for (size_t m{}; m < M; ++m)
			{
				size_t N = docSet.docs.at(m)->docWords.size();
				for (size_t n{}; n < N; ++n) {
					size_t newTopic = sampleTopicZ(m, n);
					z[m][n] = newTopic;
				}
			}

		}
	}
private:
	void updateEstimatedParams() {
		for (size_t m{}; m < M; ++m) {
			for (size_t k{}; k < K; ++k) {
				//theta[m][k]对应公式(27.37)的第一项 p(topic|doc)
				theta[m][k] = (nmk[m][k] + alpha) / (nmkSum[m] + K * alpha);
			}
		}

		for (size_t k{}; k < K; ++k) {
			for (size_t v{}; v < V; ++v) {
				//phi[k][v]对应公式(27.37)的第二项 p(word|topic)
				phi[k][v] = (nkt[k][v] + beta) / (nktSum[k] + V * beta);
			}
		}
	}

	size_t sampleTopicZ(size_t m, size_t n) {
		/* P956 of mlapp
		Given Equation 27.37, we can implement the collapsed Gibbs sampler as follows. 
		step 1: We randomly assign a topic to each word, q_il∈{1,...,K}. 
		step 2: We can then sample a new topic as follows:
			Loop{
				1) for a given word in the corpus, decrement the relevant counts
				   based on the topic assigned to the current word;(i.e.基于当前主题号,减小与之相关的所有计数量); 
				2) Then draw a new topic from Equation 27.37,and update the count matrices; 
			}
		*/

		int oldTopic = z[m][n];
		nmk[m][oldTopic]--;
		nkt[oldTopic][doc[m][n]]--;
		nmkSum[m]--;
		nktSum[oldTopic]--;

		std::vector<double> p;
		p.resize(K);
		for (size_t k{}; k < K; ++k) {
			// ------------------------ 核心公式 --------------------------------
			// 对应公式(27.37) in P956 of mlapp
			p[k]= (nkt[k][doc[m][n]] + beta) / (nktSum[k] + V*beta)*(nmk[m][k] + alpha) / (nmkSum[m] + K*alpha);
		}
		// 计算类散随机变量的分布累加函数
		for (size_t k = 1; k < K; ++k) {
			p[k] += p[k - 1];
		}

		//TODO:优化随机
		//Type of random number distribution
		std::uniform_real_distribution<double> dist(0, p[K-1]);  //(min, max)   
		//Mersenne Twister: Good quality random number generator    
		std::mt19937 rng;
		//Initialize with non-deterministic seeds    
		rng.seed(std::random_device{}());
		double u = dist(rng);
		
		int newTopic;
		for (newTopic = 0; newTopic < K; ++newTopic) {
			if (u < p[newTopic]) {
				break;
			}
		}


		nmk[m][newTopic]++;
		nkt[newTopic][doc[m][n]]++;
		nmkSum[m]++;
		nktSum[newTopic]++;

		return newTopic;
	}
public:
	void saveIteratedModel(const size_t& iteration, const Documents& docSet) {
		
	}

};

#endif // !LDA_LDAMODEL_H_

