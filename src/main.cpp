#include <iostream>
#include <ETAst/KeyPair.h>
#include <ETAst/Signer.h>
#include <ETAst/Encoder.h>

using namespace ETAst;

int main(int argc, char **argv) {
	KeyGenOutput generatedKeys = KeyPair::generateEd25519KeyPair();
	if (generatedKeys.code != 0) {
		std::cerr << "Error generating key pair: " << generatedKeys.message << std::endl;
		return generatedKeys.code;
	}

	SignatureResult signedNonce = Signer::signNonce(generatedKeys.keys.privateKey, "KVqPoroGSO5dlDRsmB1t5Zk9Gv14UBN2");
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
