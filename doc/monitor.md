# `monitor.c` — `Monitor` class

Wraps a `GLFWmonitor`. Monitor objects are not owned (no finalizer); they reference monitors
managed by GLFW.

```js
import { Monitor } from 'glfw';
```

## Constructor

```js
new Monitor()
```

Returns a `Monitor` wrapping the **primary** monitor (`glfwGetPrimaryMonitor`), or `undefined`
if there is none. There are no constructor arguments.

## Static properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `Monitor.monitors` | get | `Monitor[]` | All connected monitors (`glfwGetMonitors`). |

## Instance properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `name` | get | string | Human-readable monitor name (enumerable). |
| `position` | get | [`Position`](position.md) | Virtual-screen position of the monitor. |
| `workarea` | get | [`WorkArea`](workarea.md) | Usable area (excludes taskbars etc.). Needs `HAVE_GLFW_GET_MONITOR_WORKAREA`. |
| `physicalSize` | get | [`Size`](size.md) | Physical size in millimetres. |
| `contentScale` | get | [`Scale`](scale.md) | DPI scale factors. Needs `HAVE_GLFW_GET_MONITOR_CONTENT_SCALE`. |
| `currentVideoMode` | get | [`VideoMode`](video_mode.md) | The current video mode. |
| `videoModes` | get | [`VideoMode`](video_mode.md)`[]` | All supported video modes. |
| `gamma` | get/set | [`GammaRamp`](gamma_ramp.md) / number | Get returns the current gamma ramp. Set accepts either a numeric gamma exponent (`glfwSetGamma`) or a `GammaRamp` (`glfwSetGammaRamp`). |
| `userPointer` | get/set | string | The monitor user pointer, as a pointer string. |

```js
import { Monitor } from 'glfw';

const primary = new Monitor();
console.log(primary.name, [...primary.physicalSize]);

for (const m of Monitor.monitors)
  console.log(m.name, m.currentVideoMode.width, m.currentVideoMode.height);
```
