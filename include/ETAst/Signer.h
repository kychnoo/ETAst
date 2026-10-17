#pragma once

#include <iostream>

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
		static SignatureResult signNonce(const std::vector<unsigned char>& privateKey, const std::string& nonce);
		static SignatureResult signDeleteSessionMessage(const std::vector<unsigned char>& privateKey, const std::string& sessionId, const std::string& nonce);
	};
}
