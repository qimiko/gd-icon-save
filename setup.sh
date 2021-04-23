#!/bin/bash
set -e

pushd "$(dirname "$(readlink -f "$0")")" > /dev/null

cp ./gd/smali/com/robtopx/geometryjump/GeometryJump.smali ./tmp-GeometryJump.smali
rm -rf ./gd

apktool -f d gd.apk

mkdir -p build
mkdir -p out

mv ./tmp-GeometryJump.smali ./gd/smali/com/robtopx/geometryjump/GeometryJump.smali 
rm -rf ./gd/lib/armeabi ./gd/lib/x86

cp ./gd/lib/armeabi-v7a/libcocos2dcpp.so ./code/external/cocos2d/
cp ./gd/lib/armeabi-v7a/libfmod.so ./code/external/fmod/

echo "Setup should be performed now..."
