# software-rendering-3d
A demo for rendering wireframe of 3d models only with out the help of GPU.

Inspired by [formula](https://github.com/tsoding/formula).

3d model of the [skull](https://www.cgtrader.com/free-3d-models/character/human-anatomy/skull-in-low-poly) was by [anisura](https://www.cgtrader.com/designers/anisura).

# build
Make sure that you have `lld` (llvm linker) installed before trying to build it.
```
clang -std=c99 \
    -Wall -Wextra -Werror -Werror=declaration-after-statement -pedantic-errors \
    -target wasm32 -O3 -fno-builtin -nostdlib \
    -Wl,--no-entry -Wl,--allow-undefined \
    -Wl,--export=frame_buffer \
    -Wl,--export=frameSize \
    -Wl,--export=frameWidth \
    -Wl,--export=frameHeight \
    -Wl,--export=update \
    src/mod.c -o static/mod.wasm
```

# Run the demo
Host the `static/` directory with your prefered tech to see the demo. If you have `go` installed, just run the following command.
```
go run server.go
```
