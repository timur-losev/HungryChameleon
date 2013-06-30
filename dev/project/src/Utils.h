#ifndef _UTILS_H_
#define _UTILS_H_

namespace Utils
{
	// replaces substring toReplace by string replaceWith
	void ReplaceString(std::string& str, const std::string& toReplace, const std::string& replaceWith);
	void SplitString(const std::string &in, const std::string &delim, std::vector<std::string> &out);
} // Utils

#endif // _UTILS_H_