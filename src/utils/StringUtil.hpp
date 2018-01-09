#ifndef LDA_STRING_UTIL_H_
#define LDA_STRING_UTIL_H_

#include <vector>
#include <string>
#include <algorithm>

#include <functional>
#include <cctype>

class StringUtil
{
public:
	static std::string& toUpper(std::string& src) {
		std::transform(src.begin(), src.end(), src.begin(), std::toupper);
		return src;
	}

	static std::string& toLower(std::string& src) {
		std::transform(src.begin(), src.end(), src.begin(), std::tolower);
		return src;
	}

	template <typename CONT>
	static void batchToUpper(CONT& container) {
		// No need to test that if the vector is empty 
		auto iter = container.begin();
		for (; iter != container.end(); ++iter) {
			toUpper(*iter);
		}
		return;
	}

	template <typename CONT>
	static void batchToLower(CONT& container) {
		// No need to test that if the vector is empty 
		auto iter = container.begin();
		for (; iter != container.end(); ++iter) {
			toLower(*iter);
		}
		return;
	}

	static void split(const std::string& src,
		std::vector<std::string>& tokens,
		const std::string& pattern = " ",
		size_t maxsplit = std::string::npos)
	{
		//tokens.clear();
		size_t Start = 0;
		size_t end = 0;
		std::string sub;
		while (Start < src.size()) {
			end = src.find_first_of(pattern, Start);
			if (std::string::npos == end || tokens.size() >= maxsplit) {
				sub = src.substr(Start);
				tokens.push_back(sub);
				return;
			}
			sub = src.substr(Start, end - Start);
			tokens.push_back(sub);
			Start = end + 1;
		}
		return;
	}

	static std::vector<std::string>
		split(const std::string& src,
			const std::string& pattern = " ",
			size_t maxsplit = std::string::npos)
	{
		std::vector<std::string> tokens;
		split(src, tokens, pattern, maxsplit);
		return tokens;
	}

	static void tokenizeAndLowerCase(std::string& src,
																	 std::vector<std::string>& res,
																   const std::string& pattern = " ") {
		split(Trim(src), res);
		batchToLower(res);
	}

	static bool IsSpace(unsigned c) {
		// when passing large int as the argument of isspace, it core dump, so here need a type cast.
		return c > 0xff ? false : std::isspace(c & 0xff);
	}

	static std::string& LTrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<unsigned, bool>(IsSpace))));
		return s;
	}

	static std::string& RTrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<unsigned, bool>(IsSpace))).base(), s.end());
		return s;
	}

	static std::string& Trim(std::string &s) {
		return LTrim(RTrim(s));
	}

	static std::string& LTrim(std::string & s, char x) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::bind2nd(std::equal_to<char>(), x))));
		return s;
	}

	static std::string& RTrim(std::string & s, char x) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::bind2nd(std::equal_to<char>(), x))).base(), s.end());
		return s;
	}

	static std::string& Trim(std::string &s, char x) {
		return LTrim(RTrim(s, x), x);
	}


};


#endif
