#pragma once

#include <iostream>
#include <memory>
#include <vector>

namespace ETAst {
	struct Ed25519KeyPair {
		std::vector<unsigned char> publicKey;
		std::vector<unsigned char> privateKey;
	};

	struct KeyGenOutput {
		int code = 0;
		std::string message;
		Ed25519KeyPair keys;
	};
	
	class KeyPair {
	public:
		static KeyGenOutput generateEd25519KeyPair();
	};
}