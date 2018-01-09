#ifndef JYJ_RANDOM_UTIL_H_
#define JYJ_RANDOM_UTIL_H_
/*
*  random modul which includes something about generating random numbers
*  author:Yingjie Jia
*  time:2017-11
*/

//建议参考那2个机器学习工具的随机数模块的实现


//std::cout << "以下5次毫秒级loop均生成不同的[0,9]的随机整数\n";
//for (size_t j{}; j < 5; ++j) {
//	// 将以下7行封装成函数 这样连续短时间间隔的调用仍然得到不同的随机序列
//	std::uniform_int_distribution<unsigned> u(0, 9);
//	std::mt19937 rng1;
//	rng1.seed(std::random_device{}());
//	for (size_t i{}; i < 10; ++i) {
//		std::cout << u(rng1) << std::endl;
//	}
//	std::cout << "u_min: " << u.min() << " u_max: " << u.max() << "\n";
//}

//std::cout << "\n\n以下5次毫秒级loop均生成不同的[0,1]的随机实数\n";
//for (size_t j{}; j < 5; ++j) {
//	// 将以下7行封装成函数 这样连续短时间间隔的调用仍然得到不同的随机序列
//	std::uniform_real_distribution<double> u2(0, 1);
//	std::mt19937 rng;
//	rng.seed(std::random_device{}());
//	for (size_t i{}; i < 10; ++i) {
//		std::cout << u2(rng) << std::endl;
//	}
//	std::cout << "u2_min: " << u2.min() << " u2_max: " << u2.max() << "\n";
//}

#endif
