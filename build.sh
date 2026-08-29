#!/bin/bash
set -euo pipefail
PROJECT_DIR="$(
    cd "$(dirname "${BASH_SOURCE[0]}")"
    pwd
)"
SOURCE_DIR="$PROJECT_DIR/source/ZellnoGlobalChat"
BUILD_ROOT="$PROJECT_DIR/build"
BUILD_MOD="$BUILD_ROOT/@ZellnoGlobalChat"
BUILD_ADDONS="$BUILD_MOD/addons"
BUILD_KEYS="$BUILD_MOD/keys"
DAYZ_TOOLS="$HOME/.local/share/Steam/steamapps/common/DayZ Tools/Bin"
FILEBANK="$DAYZ_TOOLS/PboUtils/FileBank.exe"
BANKREV="$DAYZ_TOOLS/PboUtils/BankRev.exe"
DSSIGNFILE="$DAYZ_TOOLS/DsUtils/DSSignFile.exe"
DSCHECK="$DAYZ_TOOLS/DsUtils/DSCheckSignatures.exe"
PRIVATE_KEY="$HOME/dayz/modding/keys/Zellno/Zellno.biprivatekey"
PUBLIC_KEY="$HOME/dayz/modding/keys/Zellno/Zellno.bikey"
EXPECTED_BUILD_MOD="$PROJECT_DIR/build/@ZellnoGlobalChat"
if [ "$BUILD_MOD" != "$EXPECTED_BUILD_MOD" ]; then
    echo "Destino de build inesperado: $BUILD_MOD" >&2
    exit 1
fi
for required in \
    "$SOURCE_DIR/config.cpp" \
    "$SOURCE_DIR/inputs.xml" \
    "$SOURCE_DIR/gui/layouts/zgc_channel_indicator.layout" \
    "$SOURCE_DIR/scripts/3_Game/zgc_constants.c" \
    "$SOURCE_DIR/scripts/3_Game/zgc_settings.c" \
    "$SOURCE_DIR/scripts/5_Mission/zgc_clientstate.c" \
    "$SOURCE_DIR/scripts/5_Mission/zgc_chatinputmenu.c" \
    "$SOURCE_DIR/scripts/5_Mission/zgc_missiongameplay.c" \
    "$SOURCE_DIR/scripts/5_Mission/zgc_missionserver.c" \
    "$PROJECT_DIR/mod.cpp" \
    "$PROJECT_DIR/meta.cpp" \
    "$PROJECT_DIR/README.md" \
    "$PROJECT_DIR/TESTING.md" \
    "$PROJECT_DIR/LICENSE" \
    "$FILEBANK" \
    "$BANKREV" \
    "$DSSIGNFILE" \
    "$DSCHECK" \
    "$PRIVATE_KEY" \
    "$PUBLIC_KEY"
do
    if [ ! -f "$required" ]; then
        echo "Arquivo obrigatório não encontrado:" >&2
        echo "$required" >&2
        exit 1
    fi
done
rm -rf -- "$BUILD_MOD"
mkdir -p "$BUILD_ADDONS" "$BUILD_KEYS"
wine "$FILEBANK" \
    -property prefix=ZellnoGlobalChat \
    -dst "$(winepath -w "$BUILD_ADDONS")" \
    "$(winepath -w "$SOURCE_DIR")"
PBO="$BUILD_ADDONS/ZellnoGlobalChat.pbo"
SIGNATURE="$PBO.Zellno.bisign"
if [ ! -f "$PBO" ]; then
    echo "O FileBank não criou o PBO esperado:" >&2
    echo "$PBO" >&2
    exit 1
fi
wine "$DSSIGNFILE" \
    "$(winepath -w "$PRIVATE_KEY")" \
    "$(winepath -w "$PBO")"
if [ ! -f "$SIGNATURE" ]; then
    echo "A assinatura esperada não foi criada:" >&2
    echo "$SIGNATURE" >&2
    exit 1
fi
cp "$PUBLIC_KEY" "$BUILD_KEYS/Zellno.bikey"
cp "$PROJECT_DIR/mod.cpp" "$BUILD_MOD/mod.cpp"
cp "$PROJECT_DIR/meta.cpp" "$BUILD_MOD/meta.cpp"
cp "$PROJECT_DIR/README.md" "$BUILD_MOD/README.md"
cp "$PROJECT_DIR/TESTING.md" "$BUILD_MOD/TESTING.md"
cp "$PROJECT_DIR/LICENSE" "$BUILD_MOD/LICENSE"
VERIFY_OUTPUT="$(
    wine "$DSCHECK" \
        "$(winepath -w "$BUILD_ADDONS")" \
        "$(winepath -w "$(dirname "$PUBLIC_KEY")")" \
        2>&1
)"
echo "$VERIFY_OUTPUT"
if ! grep -q 'is OK' <<< "$VERIFY_OUTPUT"; then
    echo "Falha na validação da assinatura." >&2
    exit 1
fi
echo
echo "Propriedades do PBO:"
wine "$BANKREV" \
    -properties \
    "$(winepath -w "$PBO")"
echo
echo "Arquivos produzidos:"
find "$BUILD_MOD" \
    -type f \
    -printf '%P\n' \
    | sort
echo
echo "Hashes:"
sha256sum "$PBO" "$SIGNATURE"
echo
echo "Build validado:"
echo "$BUILD_MOD"
echo
echo "Nenhuma instalação foi realizada."
