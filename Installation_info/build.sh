#!/usr/bin/env bash

set -euo pipefail
set -x

POCKETDICT_REPO="https://github.com/LandenParke/PocketDictionary"

echo "Installing packages..."
set +e
sudo apt update
sudo apt install -y $(<packages.txt)
set -e

echo "Cloning PocketDictionary..."
git clone "$POCKETDICT_REPO"

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
./nuttx
