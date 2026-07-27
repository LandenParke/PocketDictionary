#!/usr/bin/env bash

set -euo pipefail
set -x

POCKETDICT_REPO="https://github.com/LandenParke/PocketDictionary"

echo "Installing packages..."
set +e
sudo apt update
sudo apt install -y \
    git \
    curl \
    sqlite3 \
    libsqlite3-dev \
    kconfig-frontends \
    bison \
    flex \
    gettext \
    texinfo \
    libncurses5-dev \
    libncursesw5-dev \
    xxd \
    gperf \
    automake \
    libtool \
    pkg-config \
    build-essential \
    genromfs \
    libgmp-dev \
    libmpc-dev \
    libmpfr-dev \
    libisl-dev \
    binutils-dev \
    libelf-dev \
    libexpat1-dev \
    gcc-multilib \
    g++-multilib \
    picocom \
    u-boot-tools \
    util-linux \
    tcl
set -e

if [ -d "PocketDictionary" ]; then
    echo "Checking if PocketDictionary is up to date..."
    cd PocketDictionary
    git fetch origin
    LOCAL=$(git rev-parse @)
    REMOTE=$(git rev-parse @{u})
    cd ..
    if [ "$LOCAL" != "$REMOTE" ]; then
        echo "PocketDictionary is out of date, removing and recloning..."
        rm -rf PocketDictionary
        git clone "$POCKETDICT_REPO"
    else
        echo "PocketDictionary is up to date."
    fi
else
    echo "Cloning PocketDictionary..."
    git clone "$POCKETDICT_REPO"
fi

echo "Entering NuttX directory..."
cd PocketDictionary/NUTTXSIM/nuttx

echo "Configuring NuttX..."
tools/configure.sh sim:sqlite

echo "Copying configuration..."
cp ../../GUI/nuttxspace/.config .

echo "Installing dictionary..."
sudo mkdir -p /usr/nuttx_stuff
sudo cp ../../Dictionary_Resources/dict.db /usr/nuttx_stuff/

echo "Building..."
make

echo "Running simulator..."
echo (sleep 1; echo "lvgldemo") | ./nuttx
