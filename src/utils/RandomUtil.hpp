#ifndef JYJ_RANDOM_UTIL_H_
#define JYJ_RANDOM_UTIL_H_
/*
*  random modul which includes something about generating random numbers
*  author:Yingjie Jia
*  time:2017-11
*/

//����ο���2������ѧϰ���ߵ������ģ���ʵ��


//std::cout << "����5�κ��뼶loop�����ɲ�ͬ��[0,9]���������\n";
//for (size_t j{}; j < 5; ++j) {
//	// ������7�з�װ�ɺ��� ����������ʱ�����ĵ�����Ȼ�õ���ͬ���������
//	std::uniform_int_distribution<unsigned> u(0, 9);
//	std::mt19937 rng1;
//	rng1.seed(std::random_device{}());
//	for (size_t i{}; i < 10; ++i) {
//		std::cout << u(rng1) << std::endl;
//	}
//	std::cout << "u_min: " << u.min() << " u_max: " << u.max() << "\n";
//}

//std::cout << "\n\n����5�κ��뼶loop�����ɲ�ͬ��[0,1]�����ʵ��\n";
//for (size_t j{}; j < 5; ++j) {
//	// ������7�з�װ�ɺ��� ����������ʱ�����ĵ�����Ȼ�õ���ͬ���������
//	std::uniform_real_distribution<double> u2(0, 1);
//	std::mt19937 rng;
//	rng.seed(std::random_device{}());
//	for (size_t i{}; i < 10; ++i) {
//		std::cout << u2(rng) << std::endl;
//	}
//	std::cout << "u2_min: " << u2.min() << " u2_max: " << u2.max() << "\n";
//}

#endif
