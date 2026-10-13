#pragma once

#include <memory>
#include <openssl/evp.h>

namespace ETAst {

    struct EvpPKeyFree {
        void operator()(EVP_PKEY* p) const { EVP_PKEY_free(p); }
    };

    struct EvpPKeyCtxFree {
        void operator()(EVP_PKEY_CTX* p) const { EVP_PKEY_CTX_free(p); }
    };

    struct UniqueMdCtxFree {
        void operator()(EVP_MD_CTX* p) const { EVP_MD_CTX_free(p); }
    };

    using UniquePKey = std::unique_ptr<EVP_PKEY, EvpPKeyFree>;
    using UniquePKeyCtx = std::unique_ptr<EVP_PKEY_CTX, EvpPKeyCtxFree>;
    using UniqueMdCtx = std::unique_ptr<EVP_MD_CTX, UniqueMdCtxFree>;
}