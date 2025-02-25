#!/bin/bash
set -e

# Default behavior is to build and install
BUILD_ENABLED=true
INSTALL_ENABLED=true

# Check for parameters
for arg in "$@"; do
    case $arg in
        --no-build)
            BUILD_ENABLED=false
            shift
            ;;
        --no-install)
            INSTALL_ENABLED=false
            shift
            ;;
        *)
            echo "Usage: $0 [--no-build] [--no-install]"
            exit 1
            ;;
    esac
done

# Configuration
BUILD_DIR="$(pwd)/ffmpeg-build"
NASM_VERSION="2.16.01"
FFMPEG_VERSION=6.1.1

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Install NASM
if $BUILD_ENABLED; then
    echo "Installing NASM..."
    curl -L -o nasm.tar.xz "https://www.nasm.us/pub/nasm/releasebuilds/${NASM_VERSION}/nasm-${NASM_VERSION}.tar.xz"
    tar xf nasm.tar.xz
    rm nasm.tar.xz

    cd "nasm-${NASM_VERSION}"
    ./configure --prefix=/usr
    make -j$(nproc)
fi

if $INSTALL_ENABLED; then
    echo "Installing NASM..."
    cd "$BUILD_DIR"/nasm-${NASM_VERSION}
    sudo make install
fi
cd "$BUILD_DIR"

# Build FFmpeg
if $BUILD_ENABLED; then
    echo "Building FFmpeg $FFMPEG_VERSION from source..."
    if [ ! -d "FFmpeg-n${FFMPEG_VERSION}" ]; then
        curl -L -o ffmpeg.tar.gz "https://github.com/FFmpeg/FFmpeg/archive/refs/tags/n${FFMPEG_VERSION}.tar.gz"
        tar -xzf ffmpeg.tar.gz
        rm ffmpeg.tar.gz
    fi

    cd "FFmpeg-n${FFMPEG_VERSION}"
    ./configure --prefix=/usr/local \
        --disable-shared \
        --enable-gpl \
        --enable-version3 \
        --disable-nonfree \
        --disable-doc \
        --disable-programs \
        --enable-pic \
        --enable-static
    make -j$(nproc)
fi

if $INSTALL_ENABLED; then
    echo "Installing FFmpeg $FFMPEG_VERSION..."
    cd "$BUILD_DIR"/FFmpeg-n${FFMPEG_VERSION}
    sudo make install
    sudo ldconfig
fi
cd "$BUILD_DIR"

echo "FFMPEG have been processed successfully"
