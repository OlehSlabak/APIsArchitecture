#!/bin/bash
set -e

echo "== Cloning repositories =="
git clone https://github.com/uNetworking/uWebSockets.git
git clone https://github.com/uNetworking/uSockets.git

echo "== Installing Rust toolchain (needed for uSockets) =="
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env

echo "== Building uSockets =="
cd uSockets
make
mv uSockets.a libusockets.a
sudo mkdir /usr/local/include/uSockets/
sudo cp libusockets.a /usr/local/lib/
sudo cp src/*.h /usr/local/include/uSockets/
cd ..

echo "== Installing uWebSockets headers =="
sudo mkdir /usr/local/include/uWebSockets
sudo cp -r uWebSockets/src/* /usr/local/include/uWebSockets

echo "== Installation complete =="
