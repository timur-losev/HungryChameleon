#include "pch.h"
#include "Utils.h"

namespace Utils
{
	void ReplaceString(std::string& str, const std::string& toReplace, const std::string& replaceWith)
	{
		std::string::size_type pos = 0;

		while ((pos = str.find(toReplace)) != std::string::npos)
		{
			str.replace(pos, toReplace.size( ), replaceWith);
			pos += replaceWith.size( );
		}
	}

	void SplitString(const std::string &in, const std::string &delim, std::vector<std::string> &out) 
	{
		
		std::string::size_type beg = 0;
		std::string::size_type end = in.find(delim);

		if (end == std::string::npos)
		{
			out.push_back(in);
			return;
		}

		while (end > beg)
		{
			size_t count = end - beg;
			out.push_back(in.substr(beg, count));
			end += delim.size();
			beg = end;

			end = in.find(delim, beg);
			if (end == std::string::npos)
			{
				end = in.length();
			}
		}
	}
} // Utils
