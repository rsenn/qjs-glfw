# `glfw.c` — module exports

The module entry point (`js_init_module`). Provides the free functions, the `context`
object, runtime constants, and re-exports every bound class. Import with:

```js
import { poll, Window, getTime /* ... */ } from 'glfw';
import * as glfw from 'glfw';
```

## Free functions

| Function | Description |
|----------|-------------|
| `poll()` | Process pending events without blocking (`glfwPollEvents`). |
| `wait([timeout])` | Block until an event arrives. With a numeric `timeout` (seconds) waits at most that long (`glfwWaitEventsTimeout`), otherwise blocks indefinitely (`glfwWaitEvents`). |
| `postEmptyEvent()` | Wake a blocked `wait()` from another thread. |
| `getProcAddress(name)` | Resolve a GL/GLFW function address. Returns the pointer formatted as a string (`"%p"`). |
| `getTime()` | Seconds since GLFW init, as a float. |
| `setTime(t)` | Set the timer value (seconds). |
| `getTimerValue()` | Raw timer value (integer). |
| `getTimerFrequency()` | Timer frequency in Hz (integer). |
| `getKeyName(key [, scancode])` | Layout-specific name of a key, or `null`. If `scancode` is omitted it is derived via `glfwGetKeyScancode(key)`. |
| `getKeyScancode(key)` | Platform scancode for a key constant. |
| `extensionSupported(name)` | `true` if the named GL extension is available. |
| `terminate()` | `glfwTerminate()`. |
| `getPlatform()` | Current platform constant. *Only present when built against GLFW with `glfwGetPlatform` (`HAVE_GLFW_GET_PLATFORM`).* |
| `platformSupported(platform)` | Whether a platform constant is supported. *Only present with `HAVE_GLFW_PLATFORM_SUPPORTED`.* |

### Cursors

Cursors have no wrapper class; they are passed around as pointer strings.

| Function | Description |
|----------|-------------|
| `createCursor(image, hotX, hotY)` | Create a custom cursor from an [`Image`](image.md). The hotspot may also be given as a single [`Position`](position.md): `createCursor(image, position)`. Returns a cursor pointer string. |
| `createStandardCursor(shape)` | Create a standard cursor from a shape constant. Returns a cursor pointer string. |
| `destroyCursor(cursor)` | Destroy a cursor previously returned by the functions above. |

A cursor pointer string is what [`Window.setCursor()`](window.md) expects.

## `context` object

```js
import { context } from 'glfw';

context.current = win;          // glfwMakeContextCurrent(win)
const win = context.current;    // → Window wrapping glfwGetCurrentContext()
context.swapInterval(1);        // glfwSwapInterval(interval)  (vsync)
```

- `context.current` — getter returns a `Window` for the current context (throws if there is
  none); setter takes a `Window` and makes its context current.
- `context.swapInterval(interval)` — set the buffer swap interval.

## Other exported values

- `version` — `{ major, minor, revision, toString() }`, where `toString()` returns
  `glfwGetVersionString()`.
- `rawMouseMotionSupported` — boolean, captured at module init.

## Constants

Plain integer properties exported on the module:

- **Window hints / attributes:** `FOCUSED`, `ICONIFIED`, `RESIZABLE`, `VISIBLE`, `DECORATED`,
  `AUTO_ICONIFY`, `FLOATING`, `MAXIMIZED`, `RED_BITS`, `GREEN_BITS`, `BLUE_BITS`, `ALPHA_BITS`,
  `DEPTH_BITS`, `STENCIL_BITS`, `ACCUM_RED_BITS`, `ACCUM_GREEN_BITS`, `ACCUM_BLUE_BITS`,
  `ACCUM_ALPHA_BITS`, `AUX_BUFFERS`, `STEREO`, `SAMPLES`, `SRGB_CAPABLE`, `REFRESH_RATE`,
  `DOUBLEBUFFER`, `CLIENT_API`, `CONTEXT_VERSION_MAJOR`, `CONTEXT_VERSION_MINOR`,
  `CONTEXT_REVISION`, `CONTEXT_ROBUSTNESS`, `OPENGL_FORWARD_COMPAT`, `OPENGL_DEBUG_CONTEXT`,
  `OPENGL_PROFILE`, `CONTEXT_RELEASE_BEHAVIOR`, `CONTEXT_NO_ERROR`, `CONTEXT_CREATION_API`,
  `OPENGL_CORE_PROFILE`, `VERSION_MAJOR`, `VERSION_MINOR`, `VERSION_REVISION`.
- **Keys:** `KEY_UNKNOWN`, `KEY_SPACE`, `KEY_APOSTROPHE`, `KEY_COMMA`, `KEY_MINUS`, `KEY_PERIOD`,
  `KEY_SLASH`, `KEY_0`…`KEY_9`, `KEY_A`…`KEY_Z`, punctuation keys, `KEY_ESCAPE`, `KEY_ENTER`,
  `KEY_TAB`, arrows/navigation, `KEY_F1`…`KEY_F25`, the keypad `KEY_KP_*`, the modifier keys
  (`KEY_LEFT_SHIFT` … `KEY_RIGHT_SUPER`), `KEY_MENU`, `KEY_LAST`.
- **Platforms** (each present only if defined by the GLFW headers): `PLATFORM_WAYLAND`,
  `PLATFORM_COCOA`, `PLATFORM_WIN32`, `PLATFORM_X11`, `PLATFORM_NULL`, `ANY_PLATFORM`.

> Note: action/modifier constants (`PRESS`, `RELEASE`, `REPEAT`, `MOD_*`) and mouse-button
> constants are **not** currently exported by the module even though they are mentioned in the
> top-level `README.md`. Their numeric values still come back from callbacks and `getKey` /
> `getMouseButton`.

## Re-exported classes

The module also exports these classes, each documented separately:

[`Window`](window.md) · [`Monitor`](monitor.md) · [`Position`](position.md) ·
[`Size`](size.md) · [`Scale`](scale.md) · [`Image`](image.md) ·
[`VideoMode`](video_mode.md) · [`WorkArea`](workarea.md) · [`GammaRamp`](gamma_ramp.md)
