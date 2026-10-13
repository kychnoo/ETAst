#pragma once

#include <iostream>
#include <vector>

namespace ETAst
{
	class Encoder
	{
	public:
		static std::string encodeBase64(const std::vector<unsigned char>& data);
	};
}
