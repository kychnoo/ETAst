# ETAst

**ETAst** is a lightweight, high-performance C++20 cryptographic SDK designed for cross-platform client applications (Desktop and Android). It acts as a clean, self-contained client-side library (similar in concept to TDLib) built specifically to power authentication and secure communication for **EncrypTex**.

The library wraps low-level OpenSSL primitives into modern, memory-safe C++ abstractions (RAII) and provides a dead-simple API, sparing developers from manual memory management, error-code checking, and complex cross-compilation overhead.

---

## Features

- **Ed25519 Operations:** Out-of-the-box key generation, nonce signing (`signNonce`), and data encoding.
- **Memory Safety (RAII):** OpenSSL contexts (`EVP_PKEY`, `EVP_MD_CTX`) are wrapped in custom smart pointers to prevent leaks and eliminate manual cleanup boilerplate.
- **Cross-Platform:** First-class support for Desktop (Windows, Linux, macOS) and Android (`arm64-v8a`, `armeabi-v7a`).
- **Seamless Build System:** Powered entirely by **xmake** for instant dependency fetching (OpenSSL) and hassle-free cross-compilation.

---

## Build System
ETAst uses [xmake](https://xmake.io/) for dependency management and compilation. OpenSSL is pulled automatically under the hood.

## Building

### Desktop (Release):
```bash
xmake f -m release
xmake
```

### Android (e.g., arm64-v8a)
```bash
xmake f -m release -p android -a arm64-v8a --ndk="$ANDROID_NDK_HOME"
```