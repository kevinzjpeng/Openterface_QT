#!/bin/bash

# Get the directory where this script is located
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

# Set environment variables for configuration paths
export QT_QPA_PLATFORM=xcb
export LD_LIBRARY_PATH="$SCRIPT_DIR/../lib:$LD_LIBRARY_PATH"
export QT_PLUGIN_PATH="$SCRIPT_DIR/../lib/qt6/plugins"
export QML_IMPORT_PATH="$SCRIPT_DIR/../lib/qt6/qml"
export CONFIG_DIR="$SCRIPT_DIR/../share/openterfaceQT/config"

# Debug information
echo "Running openterfaceQT wrapper"
echo "SCRIPT_DIR: $SCRIPT_DIR"
echo "CONFIG_DIR: $CONFIG_DIR"
echo "QT_PLUGIN_PATH: $QT_PLUGIN_PATH"

# Launch the actual binary with the environment set
exec "$SCRIPT_DIR/openterfaceQT" "$@"
