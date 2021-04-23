#!/bin/bash

pushd "$(dirname "$(readlink -f "$0")")" > /dev/null

echo "[build] Build apk"

apktool b gd

echo "[build] Sign apk"

echo "No signing function defined - your APK will fail to install. Copying..."
cp ./gd/dist/gd.apk ./out

popd > /dev/null
