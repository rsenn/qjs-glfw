# `video_mode.c` — `VideoMode` class

Wraps a `GLFWvidmode`. Describes a monitor video mode.

```js
import { VideoMode } from 'glfw';
```

## Construction

**Cannot be constructed directly** — `new VideoMode()` throws
(`"VideoMode can not be constructed directly"`). Obtain instances from a
[`Monitor`](monitor.md):

```js
const mode  = monitor.currentVideoMode;   // a VideoMode
const modes = monitor.videoModes;         // VideoMode[]
```

## Instance properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `width` | get/set | int | Enumerable. |
| `height` | get/set | int | Enumerable. |
| `redBits` | get/set | int | |
| `greenBits` | get/set | int | |
| `blueBits` | get/set | int | |
| `refreshRate` | get/set | int | Enumerable. |

> Setters mutate the wrapped struct in place; this does not change the monitor's actual mode.

`Object.prototype.toString` tag: `GLFWvidmode`.
