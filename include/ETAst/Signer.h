#pragma once

#include <iostream>
#include <string_view>

#include "KeyPair.h"

namespace ETAst {
	struct SignatureResult {
		int code = 0;
		std::string message;
		std::vector<unsigned char> signature;
	};

	class Signer
	{
	public:
		static SignatureResult signMessage(const std::vector<unsigned char>& privateKey, const std::string& message);

		static std::string deleteSessionMessage(const std::string_view sessionId, const std::string_view nonce);
		static std::string refreshSessionMessage(const std::string_view nonce);
	};
}
