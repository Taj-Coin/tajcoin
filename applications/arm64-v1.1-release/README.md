# Tajcoin v1.1 — builds ARM64 (aarch64)

Paquet préparé pour contribution à [Taj-Coin/tajcoin](https://github.com/Taj-Coin/tajcoin) — release **v1.1**.

## Fichiers prêts à soumettre

| Fichier | Contenu | Statut |
|---------|---------|--------|
| `tajcoind-arm64-v1.1.zip` | `tajcoind` daemon, aarch64, stripped (~3,2 Mo) | **Prêt** |
| `tajcoin-qt_1.1.0.0-1_arm64.deb` | Wallet Qt ARM64, stripped (~14 Mo) | **Prêt** |
| `tajcoin-qt-arm64-v1.1.zip` | `tajcoin-qt` extrait du .deb (aarch64) | **Prêt** |
| `tajcoind-arm64-v1.1-unstripped.zip` | Archive debug (~84 Mo) — **ne pas publier upstream** | Référence build |

Checksums : voir `SHA256SUMS`.

## ⚠️ Fichier à ne pas soumettre

`../tajcoin-qt-arm64.zip` (dossier parent) contient un binaire **x86_64**, pas ARM64 — utiliser uniquement `tajcoin-qt-arm64-v1.1.zip` de ce dossier.

## Build `tajcoind` (strip sur ARM)

Effectué sur Raspberry Pi **aarch64** (`192.168.1.31`) :

```bash
strip tajcoind   # 84 Mo → 3,2 Mo
zip tajcoind-arm64-v1.1.zip tajcoind   # ~1,3 Mo
```

## Cibles testées

- **Architecture** : `aarch64` (ARM64)
- **tajcoin-qt .deb** : Debian/Ubuntu récents (deps Boost 1.83, Qt5 — voir `dpkg-deb -I`)
- **tajcoind** : ELF dynamique, `ld-linux-aarch64.so.1`

## Prochaine étape upstream

1. Ouvrir l’issue : texte dans `ISSUE-UPSTREAM.md`
2. Contacter **dev@tajcoin.tech**
3. Proposer les assets pour [Release v1.1](https://github.com/Taj-Coin/tajcoin/releases/tag/v1.1) ou **v1.1.1**
4. (Optionnel) PR avec script `contrib/build-arm64.sh` — build reproductible depuis le tag `v1.1`

## Vérification locale

```bash
file tajcoind tajcoin-qt   # doit afficher ARM aarch64
sha256sum -c SHA256SUMS
```
