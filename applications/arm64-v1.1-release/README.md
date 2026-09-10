# Tajcoin v1.1 — ARM64 (aarch64) builds

ARM64 (aarch64) build artifacts for Tajcoin **v1.1**, contributed to [Taj-Coin/tajcoin](https://github.com/Taj-Coin/tajcoin).

## Files

| File | Content | Notes |
|------|---------|-------|
| `tajcoind-arm64-v1.1.zip` | `tajcoind` daemon, aarch64, stripped (~3.2 MB) | Ready |
| `tajcoin-qt_1.1.0.0-1_arm64.deb` | Qt wallet, ARM64, stripped (~14 MB) | Ready |
| `tajcoin-qt-arm64-v1.1.zip` | `tajcoin-qt` extracted from the .deb (aarch64) | Ready |
| `tajcoind-arm64-v1.1-unstripped.zip` | Debug archive (~84 MB) — **do not distribute** | Build reference |

Checksums: see `SHA256SUMS`.

## ⚠️ Do not use

`../tajcoin-qt-arm64.zip` (parent folder) contains an **x86_64** binary, not ARM64 — use only `tajcoin-qt-arm64-v1.1.zip` from this folder.

## Building `tajcoind` (strip on ARM)

Performed on a Raspberry Pi **aarch64**:

```bash
strip tajcoind   # 84 MB → 3.2 MB
zip tajcoind-arm64-v1.1.zip tajcoind   # ~1.3 MB
```

## Tested targets

- **Architecture**: `aarch64` (ARM64)
- **tajcoin-qt .deb**: recent Debian/Ubuntu (Boost 1.83, Qt5 deps — see `dpkg-deb -I`)
- **tajcoind**: dynamic ELF, `ld-linux-aarch64.so.1`

## Local verification

```bash
file tajcoind tajcoin-qt   # must report ARM aarch64
sha256sum -c SHA256SUMS
```
