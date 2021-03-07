#!/usr/bin/env bash

valgrind --tool=callgrind --callgrind-out-file=callgrindFile.out ./mazeGenerator
kcachegrind callgrindFile.out