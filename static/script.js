const resizeCanvas = () => {
	if (screen.height < screen.width) {
		canvas.style.width = `${screen.height - 20}px`;
		canvas.style.height = `${screen.height - 20}px`;

		canvas.style.left = `${(screen.width/2) - (screen.height/2) - 10}px`;
		canvas.style.top = `${10}px`;
	} else {
		canvas.style.width = `${screen.width - 20}px`;
		canvas.style.height = `${screen.width - 20}px`;

		canvas.style.left = `${10}px`;
		canvas.style.top = `${(screen.height/2) - (screen.width/2) - 10}px`;
	}
};

window.addEventListener("load", resizeCanvas, { once: true });
window.addEventListener("resize", resizeCanvas);

const runWasm = (wasmModule) => {
	const exports = wasmModule.instance.exports;

	const memory = exports.memory;

	canvas.width = exports.frameWidth();
	canvas.height = exports.frameHeight();

	const ctx = canvas.getContext("2d", { willReadFrequently: false });

	const frame = new ImageData(
		new Uint8ClampedArray(memory.buffer, exports.frame_buffer.valueOf(), exports.frameSize()),
		canvas.width,
		canvas.height
	);

	let pt = 0.0;

	const loop = (t) => {
		const dt = (t - pt) * 0.001;
		pt = t;

		logjs.textContent = `FPS: ${Math.floor(1/dt)}`;

		exports.update(dt);

		ctx.putImageData(frame, 0, 0);
		requestAnimationFrame(loop);
	};

	requestAnimationFrame((t) => {
		pt = t;

		exports.update(0);

		ctx.putImageData(frame, 0, 0);
		requestAnimationFrame(loop);
	});
};

// taken from https://github.com/0x5247/wasm-by-example/blob/master/demo-util/instantiateWasm.js
const wasmBrowserInstantiate = async (wasmModuleUrl, importObject) => {
	let response = undefined;

	if (!importObject) {
		importObject = {
			env: {
				abort: () => console.log("Abort!")
			}
		};
	}

	if (WebAssembly.instantiateStreaming) {
		response = await WebAssembly.instantiateStreaming(
			fetch(wasmModuleUrl),
			importObject
		);
	} else {
		const fetchAndInstantiateTask = async () => {
			const wasmArrayBuffer = await fetch(wasmModuleUrl).then(response =>
				response.arrayBuffer()
			);
			return WebAssembly.instantiate(wasmArrayBuffer, importObject);
		};
		response = await fetchAndInstantiateTask();
	}

	return response;
};

const log = (n, idx) => {
	switch (idx) {
	case 0:
		log0.textContent = n;
		break;
	case 1:
		log1.textContent = n;
		break;
	case 2:
		log2.textContent = n;
		break;
	case 3:
		log3.textContent = n;
		break;
	}
};

wasmBrowserInstantiate("/mod.wasm", {
	env: {
		abort: () => console.log("Abort!"),
		sin: Math.sin,
		cos: Math.cos,
		print_u16: log,
		print_i32: log,
		print_f32: log,
	},
}).then(runWasm);
