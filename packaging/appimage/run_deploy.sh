#!/bin/bash
set -x  # Print commands for debugging
env | grep -E 'QT|QMAKE|QML'  # Display Qt-related environment variables

# Run linuxdeploy with Qt plugin
linuxdeploy-x86_64.AppImage \
  --appdir=AppDir \
  --plugin=qt \
  --executable=AppDir/usr/bin/openterface-wrapper.sh \
  --desktop-file=AppDir/usr/share/applications/openterfaceQT.desktop \
  --icon-file=AppDir/usr/share/icons/hicolor/256x256/apps/openterfaceQT.png \
  --output=appimage
  
EXIT_CODE=$?
echo "linuxdeploy exit code: $EXIT_CODE"

# List all files in current directory for debugging
echo "Files in current directory:"
ls -la

# Exit with the linuxdeploy exit code
exit $EXIT_CODE
