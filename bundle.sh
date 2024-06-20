#!/bin/sh

w4 bundle --windows rubido-windows.exe  --title Rubido build/cart.wasm
w4 bundle --mac rubido-mac  --title Rubido build/cart.wasm
w4 bundle --linux rubido-linux  --title Rubido build/cart.wasm
w4 bundle --html index.html  --title Rubido build/cart.wasm
cp build/cart.wasm rubido.wasm
chmod +x ./rubido-mac
chmod +x ./rubido-linux
chmod +x ./rubido-windows.exe
tar -czvf ./rubido-windows.tar.gz ./rubido-windows.exe
tar -czvf ./rubido-mac.tar.gz ./rubido-mac
tar -czvf ./rubido-linux.tar.gz ./rubido-linux
tar -czvf ./rubido-html.tar.gz ./index.html
tar -czvf ./rubido-cart.tar.gz ./rubido.wasm
rm -f ./rubido-windows.exe
rm -f ./rubido-mac
rm -f ./rubido-linux
