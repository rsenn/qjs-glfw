# `gamma_ramp.c` — `GammaRamp` class

Wraps a `GLFWgammaramp`: three equal-length 16-bit lookup tables for the red, green and blue
channels. Returned by `Monitor.gamma`.

```js
import { GammaRamp } from 'glfw';
```

## Construction

**Cannot be constructed directly** — `new GammaRamp()` throws
(`"glfw.GammaRamp can not be constructed directly"`). Obtain an instance from a
[`Monitor`](monitor.md):

```js
const ramp = monitor.gamma;        // a GammaRamp
```

## Instance properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `red` | get | `Uint16Array` | View over the red channel ramp (`size` elements). |
| `green` | get | `Uint16Array` | View over the green channel ramp. |
| `blue` | get | `Uint16Array` | View over the blue channel ramp. |
| `size` | get | int | Number of entries per channel (enumerable). |

The channel arrays are views over the wrapped struct's memory and keep the `GammaRamp` alive while
referenced. To apply a ramp, assign it back to a monitor:

```js
const ramp = monitor.gamma;
ramp.red.set(/* ... */);
monitor.gamma = ramp;              // glfwSetGammaRamp
```

`Object.prototype.toString` tag: `GLFWgammaramp`.
