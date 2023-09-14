#!/usr/bin/env bash

DEMCC="ON"

if [[ $* == *--no-wasm* ]]
then
	DEMCC=OFF
fi

srcDir="backend"
buildDir="${srcDir}/build"
mkdir ${buildDir}

cmake .. -DEMCC=${DEMCC} -B "${buildDir}/" -S "${srcDir}/"
make -C "${buildDir}/"


if [ "$DEMCC" == "ON" ]
then
	frontendDestDir="frontend/src/assets/wasm/"
	mkdir ${frontendDestDir}

	cp "${buildDir}/mazeGenerator.wasm" ${frontendDestDir}
	cp "${buildDir}/mazeGenerator.js" ${frontendDestDir}

	npm install --prefix frontend/
	npm run dev --prefix frontend/
else
	ctest --test-dir backend/build --verbose

	if [[ $* == *--clang-tidy* ]]
	then
		clang-tidy --config-file=./.clang-tidy backend/src/*.cpp backend/include/*.hpp -- -Ibackend/include/ -Ibackend/include/maze -Ibackend/include/generators -Ibackend/include/solvers -std=c++20
	fi
fi