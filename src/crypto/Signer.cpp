#include "ETAst/Signer.h"
#include "openssl_utils.h"

#include <format>

namespace ETAst {
	SignatureResult Signer::signNonce(const std::vector<unsigned char>& privateKey, const std::string& nonce) {
		// Create a new EVP_PKEY object from the raw private key.
		UniquePKey pkey(EVP_PKEY_new_raw_private_key(EVP_PKEY_ED25519, nullptr, privateKey.data(), privateKey.size()));

		// Check if the EVP_PKEY object was created successfully.
		if (!pkey) {
			return { -1, "Failed to load private key" };
		}

		// Create a new EVP_MD_CTX object for signing and verification.
		UniqueMdCtx ctx(EVP_MD_CTX_new());
		if (!ctx) {
			return { -2, "Failed to create EVP_MD_CTX" };
		}

		// Initialize the signing operation with the private key.
		if (EVP_DigestSignInit(ctx.get(), nullptr, nullptr, nullptr, pkey.get()) <= 0) {
			return { -3, "DigestSignInit failed" };
		}

		// Determine the size of the signature.
		// First call to EVP_DigestSign with nullptr to get the required signature length.
		size_t sigLen = 0;
		if (EVP_DigestSign(ctx.get(), nullptr, 
			&sigLen, reinterpret_cast<const unsigned char*>(nonce.data()), 
			nonce.size()) <= 0
		) {
			return { -4, "DigestSign (size query) failed" };
		}
		
		// Allocate a buffer for the signature and perform the signing operation.
		std::vector<unsigned char> signature(sigLen);
		if (EVP_DigestSign(ctx.get(), signature.data(), &sigLen, reinterpret_cast<const unsigned char*>(nonce.data()), nonce.size()) <= 0) {
			return { -5, "DigestSign failed" };
		}

		// Resize the signature vector to the actual size of the signature and return it.
		signature.resize(sigLen);
		return { 0, "Signature generated successfully", std::move(signature) };
	}

	SignatureResult Signer::signDeleteSessionMessage(const std::vector<unsigned char>& privateKey,const std::string& sessionId, const std::string& nonce) {
		// Concatenate the session ID and nonce to create the message to be signed.
		const std::string messageToSign = std::format("delete-session:{}:{}", sessionId, nonce);
		// Retrieve the private key from a secure source (e.g., environment variable, secure storage).
		if (privateKey.empty()) {
			return { -1, "Failed to retrieve private key" };
		}
		// Sign the concatenated message using the signNonce method.
		return signNonce(privateKey, messageToSign);
	}
}