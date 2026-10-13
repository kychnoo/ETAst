#include "ETAst/KeyPair.h"
#include "openssl_utils.h"

namespace ETAst
{
	KeyGenOutput KeyPair::generateEd25519KeyPair() {
		// Create a new EVP_PKEY_CTX for Ed25519 key generation.
		UniquePKeyCtx ctx(EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, nullptr));

		// Check if the context was created successfully.
		if (!ctx) {
			return { -1, "EVP_PKEY_CTX_new_id failed" };
		}

		// Initialize the key generation operation.
		if (EVP_PKEY_keygen_init(ctx.get()) <= 0) {
			return { -2, "EVP_PKEY_keygen_init failed" };
		}

		// Generate the key pair.
		EVP_PKEY* pkey = nullptr;
		if (EVP_PKEY_keygen(ctx.get(), &pkey) <= 0) {
			return { -3, "EVP_PKEY_keygen failed" };
		}
		UniquePKey key(pkey);

		Ed25519KeyPair pair;

		// Determine the sizes of the raw private and public keys.
		size_t pubKeyLen = 0, privKeyLen = 0;
		if (EVP_PKEY_get_raw_private_key(key.get(), nullptr, &privKeyLen) <= 0) {
			return { -4, "get_raw_private_key size query failed" };
		}
		if (EVP_PKEY_get_raw_public_key(key.get(), nullptr, &pubKeyLen) <= 0) {
			return { -5, "get_raw_public_key size query failed" };
		}

		// Resize the vectors to hold the keys and retrieve the raw keys.
		pair.privateKey.resize(privKeyLen);
		pair.publicKey.resize(pubKeyLen);

		// Retrieve the raw private and public keys.
		if (EVP_PKEY_get_raw_private_key(key.get(), pair.privateKey.data(), &privKeyLen) <= 0) {
			return { -6, "get_raw_private_key failed" };
		}
		if (EVP_PKEY_get_raw_public_key(key.get(), pair.publicKey.data(), &pubKeyLen) <= 0) {
			return { -7, "get_raw_public_key failed" };
		}

		pair.privateKey.resize(privKeyLen);
		pair.publicKey.resize(pubKeyLen);

		// Return the generated key pair.
		return { 0, "Ed25519 key pair generated successfully", std::move(pair) };
	}
}