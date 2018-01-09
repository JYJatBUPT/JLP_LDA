#ifndef LDA_STD_EXTENSION_H_
#define LDA_STD_EXTENSION_H_

#include <ostream>
#include <vector>
#include <unordered_set>

namespace std {

	template<typename T>
	inline ostream& operator<< (ostream& out, const std::unordered_set<T>& StringSet)
	{
		if (StringSet.empty()) {
			return out << "{}";
		}
		size_t max_display_num = 100;
		auto iter = StringSet.cbegin();
		out << "{" << *iter;
		while ((++iter) != StringSet.cend()&&(--max_display_num)) {
			out << ",\n" << *iter;
		}
		out << "}";
		return out;
	}

	inline ostream& operator << (ostream& os, const vector<string>& v) {
		if (v.empty()) {
			return os << "[]";
		}
		os << "[\"" << v[0];
		for (size_t i = 1; i < v.size(); i++) {
			os << "\",\n \"" << v[i];
		}
		os << "\"]";
		return os;
	}
	template<typename T>
	inline ostream& operator<< (ostream& out, const std::vector<T>& vec)
	{
		if (vec.empty()) {
			return out << "[]";
		}
		size_t max_display_num = 100;
		auto iter = vec.cbegin();
		out << "[" << *iter;
		while ((++iter) != vec.cend() && (--max_display_num)) {
			out << ",\n" << *iter;
		}
		out << "]";
		return out;
	}
	//template <typename T>			// TODO:complete the out format of matrix
	//inline ostream& operator<< (ostream& out, const std::vector<std::vector<T>>& mat)
	//{
	//}

}

#endif


