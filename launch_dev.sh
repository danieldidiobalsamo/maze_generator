#!/usr/bin/env bash

srcDir="backend"
buildDir="${srcDir}/build"

mkdir ${buildDir}
cmake .. -DEMCC=ON -B "${buildDir}/" -S "${srcDir}/"
make -C "${buildDir}/"

frontendDestDir="frontend/src/assets/wasm/"
mkdir ${frontendDestDir}

cp "${buildDir}/mazeGenerator.wasm" ${frontendDestDir}
cp "${buildDir}/mazeGenerator.js" ${frontendDestDir}

npm run dev --prefix frontend/
