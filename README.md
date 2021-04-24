# Geometry Dash Android Icon Kit Storage

A Geometry Dash 2.11 Android hack that adds RobTop-like icon kit storage to the game.

## Screenshots

![Selecting kit](/docs/screenshot_kitselect.png?raw=true)
![Saving icon on garage](/docs/screenshot_garagesave.png?raw=true)
![Saving icon kit on profile](/docs/screenshot_profilesave.png?raw=true)
![Missing unlocks for set dialog](/docs/screenshot_missingunlock.png?raw=true)

## Building

Due to the copyrighted nature of Geometry Dash, the program will be provided as a shared library release only. If you wish to modify this application, or automate the APK building process, these are the steps to take:

1. Recreate `build-apk.sh` - a version of the script is provided as `build-apk-default.sh` but **does not sign APKs**. The personal build version of the script utilizes [uber-apk-signer](https://github.com/patrickfav/uber-apk-signer) in order to automate the signing process.

2. Place an **unmodified** version of the Geometry Dash 2.11 APK in the root directory and run `setup.sh`. Ensure that `apktool` is in your path, or the script will fail.

3. Setup CMake with Android NDK toolchain file in the newly created `build` directory.

4. Run CMake's install target in order to compile the APK file and copy it to the `out` folder.
