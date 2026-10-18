#include <iostream>
#include <span>
#include <string_view>
#include <vector>

#include <ETAst/KeyPair.h>
#include <ETAst/Signer.h>
#include <ETAst/Encoder.h>


using namespace ETAst;

int main(int argc, char **argv) {
	constexpr std::string_view kSessionId = "--session-id=";
	constexpr std::string_view kNonce = "--nonce=";
	constexpr std::string_view kPrivKey = "--private-key=";

	std::span<char*> args(argv, argc);
	std::string sessionId;
	std::string nonce;
	std::vector<unsigned char> privateKey;

	for (size_t i = 1; i < args.size(); ++i) {
		std::string_view arg(args[i]);
		if (arg.starts_with(kSessionId)) {
			sessionId = std::string(arg.substr(kSessionId.size()));
		}
		else if (arg.starts_with(kNonce)) {
			nonce = std::string(arg.substr(kNonce.size()));
		}
		else if (arg.starts_with(kPrivKey)) {
			std::string_view keyStr = arg.substr(kPrivKey.size());
			privateKey = std::vector<unsigned char>(keyStr.begin(), keyStr.end());
		}
	}

	if (sessionId.empty()) {
		std::cerr << "Error: --session-id argument is required" << std::endl;
		return -1;
	}
	else if (nonce.empty()) {
		std::cerr << "Error: --nonce argument is required" << std::endl;
		return -1;
	}

	if (privateKey.empty()) {
		KeyGenOutput generatedKeys = KeyPair::generateEd25519KeyPair();
		if (generatedKeys.code != 0) {
			std::cerr << "Error generating key pair: " << generatedKeys.message << std::endl;
			return generatedKeys.code;
		}
		privateKey = generatedKeys.keys.privateKey;
	}

	SignatureResult signedNonce = Signer::signMessage(privateKey, Signer::deleteSessionMessage(sessionId, nonce));
	if (signedNonce.code != 0) {
		std::cerr << "Error signing nonce: " << signedNonce.message << std::endl;
		return signedNonce.code;
	}

	std::string encodedSignature = Encoder::encodeBase64(signedNonce.signature);
	if (encodedSignature.empty()) {
		std::cerr << "Error encoding signature" << std::endl;
		return -1;
	}

    std::cout << encodedSignature << std::endl;
    return 0;
}
