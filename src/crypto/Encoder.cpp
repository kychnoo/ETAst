#include "ETAst/Encoder.h"
#include "openssl_utils.h"

namespace ETAst
{
	std::string Encoder::encodeBase64(const std::vector<unsigned char>& data) {
		if (data.empty()) {
			return "";
		}

		// Let for output buffer size calculation: 4 * ((n + 2) / 3).
		int encodedLen = 4 * ((data.size() + 2) / 3);
		std::string encodedStr(encodedLen, '\0'); // Output buffer for base64 encoded string.

		int actualLen = EVP_EncodeBlock(reinterpret_cast<unsigned char*>(&encodedStr[0]), data.data(), data.size());
		if (actualLen < 0) {
			return "";
		}
		return encodedStr.substr(0, actualLen);
	}
}