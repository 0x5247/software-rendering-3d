# software-rendering-3d
<<<<<<< HEAD
A demo for rendering wireframe of 3d models without GPU.

Inspired by [formula](https://github.com/tsoding/formula).

[3d model](https://www.cgtrader.com/free-3d-models/character/human-anatomy/skull-in-low-poly) of the skull was by [anisura](https://www.cgtrader.com/designers/anisura).
=======
A demo for rendering wireframe of 3d models with CPU.

Inspired by [formula](https://github.com/tsoding/formula).

3d model of the [skull](https://www.cgtrader.com/free-3d-models/character/human-anatomy/skull-in-low-poly) was by [anisura](https://www.cgtrader.com/designers/anisura).
>>>>>>> b1e1c65 (did something)

# build
Make sure that you have lld (llvm linker) before trying to build it.
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
<<<<<<< HEAD
Host the `static/` directory to see the demo with your prefered tech. If you have go, just run the following command.
=======
Host the `static/` directory to see the demo with your prefered tech. If you have `go` installed, just run the following command.
>>>>>>> b1e1c65 (did something)
```
go run server.go
```
