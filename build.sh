#!/usr/bin/env bash

clang -std=c99 \
	-Wall -Wextra -Werror -Werror=declaration-after-statement -pedantic-errors \
	-target wasm32 -O3 -fno-builtin -nostdlib \
	-Wl,--no-entry -Wl,--allow-undefined -Wl,--strip-all \
	-Wl,--export=frame_buffer \
	-Wl,--export=frameSize \
	-Wl,--export=frameWidth \
	-Wl,--export=frameHeight \
	-Wl,--export=update \
	src/mod.c -o static/mod.wasm
