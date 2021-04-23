# 1.9 GDPS Android Modifications

## Requirements

* APKTool in path
* android-ndk-r17 or below (must support gnustl)

## External patches

The following external patches have been applied:

### Within libcocos2dcpp.so

* Object Bypass (look for references to EditorUI::showMaxError)
* Editor Song Length bypass `0x23C790` -> `0x09`
* URLs
  * Tools page
  * Twitter
  * YouTube
  * Facebook
* Comment Ban Message

### Within smali

com.kyurime.geometryjump.GeometryJump.smali: in main

```smali
const-string v0, "aurav2"
invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```
