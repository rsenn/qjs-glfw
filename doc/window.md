# `window.c` — `Window` class

Wraps a `GLFWwindow`. Creating a window initializes GLFW lazily on first use.

```js
import { Window } from 'glfw';
```

## Constructor

```js
new Window(width, height [, title, monitor, share])
new Window(size            [, title, monitor, share])   // size is a Size instance
```

- `width`, `height` — numbers, or a single [`Size`](size.md) instance.
- `title` — string. `null`/`undefined` falls back to `"qjs-glfw"`.
- `monitor` — a [`Monitor`](monitor.md) for fullscreen, or `null`/`undefined` for windowed.
- `share` — another `Window` to share the GL context with, or `null`/`undefined`.

Throws on a failed `glfwCreateWindow` (with the GLFW error message when `HAVE_GLFW_GET_ERROR`).

## Static methods

Defined on the `Window` constructor itself:

| Method | Description |
|--------|-------------|
| `Window.hint(hint, value)` | Set a window/context hint before construction. `value` may be a number, a boolean, or a string (string hints require `HAVE_GLFW_WINDOW_HINT_STRING`). |
| `Window.defaultHints()` | Reset all hints to defaults (`glfwDefaultWindowHints`). |

## Instance properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `id` | get | string | The `GLFWwindow*` as a pointer string. |
| `shouldClose` | get/set | boolean | Close flag. |
| `title` | set | string | Write-only; sets the window title. |
| `position` | get/set | [`Position`](position.md) | Window position in screen coordinates. |
| `size` | get/set | [`Size`](size.md) | Window size in screen coordinates. |
| `framebufferSize` | get | [`Size`](size.md) | Pixel size (HiDPI-aware). |
| `opacity` | get/set | number | Get needs `HAVE_GLFW_GET_WINDOW_OPACITY` (else `undefined`); set needs `HAVE_GLFW_SET_WINDOW_OPACITY`. |
| `monitor` | get | [`Monitor`](monitor.md)`\|null` | Fullscreen monitor, or `null` if windowed. |
| `cursorPos` | get/set | object | Get returns `{x, y}` (floats). Set accepts `{x, y}` or `[x, y]`. |

## Instance methods

| Method | Description |
|--------|-------------|
| `makeContextCurrent()` | Make this window's GL context current. |
| `swapBuffers()` | Swap front/back buffers. |
| `setMonitor(monitor [, xpos, ypos, width, height, refreshRate])` | Move to/from fullscreen. `monitor` may be `null`/`undefined`; omitted numerics default to `0` and `refreshRate` to `GLFW_DONT_CARE`. |
| `setSizeLimits(minW, minH, maxW, maxH)` | Constrain resizable window size. |
| `setAspectRatio(numer, denom)` | Lock the aspect ratio. |
| `getFrameSize([target])` | Decoration sizes. Returns `{left, top, right, bottom}`, or fills `target` (object or array) if given. |
| `getContentScale([target])` | DPI scale. Returns `{x, y}`, or fills `target` (object or array) if given. |
| `getAttrib(attrib)` | Read a window attribute (integer). |
| `setAttrib(attrib, value)` | Write a window attribute. |
| `setCursor(cursor)` | Set the cursor from a cursor pointer string (see [`createCursor`](glfw.md)). |
| `setIcon(...images)` | Set the window icon from one or more [`Image`](image.md) instances. |
| `getKey(key)` | Key state (`PRESS`/`RELEASE`) for a key constant. |
| `getMouseButton(button)` | Mouse-button state. |
| `getInputMode(mode)` | Read an input mode. |
| `setInputMode(mode, value)` | Set an input mode (e.g. cursor mode). |
| `getClipboardString()` | Clipboard contents as a string. |
| `setClipboardString(str)` | Set the clipboard. |
| `iconify()` / `restore()` / `maximize()` / `show()` / `hide()` / `focus()` | Window state triggers. |
| `requestAttention()` | Flash the window for attention. *Only present with `HAVE_GLFW_REQUEST_WINDOW_ATTENTION`.* |
| `destroy()` | Destroy the native window and clear the opaque pointer. |

## Event handlers

Each handler is an assignable **property** (not a `setXxxCallback` method). Assign a function to
install the corresponding GLFW callback; assign a non-function to remove it. The getter returns the
currently installed handler. Inside a handler, `this` is the `Window`.

| Property | Callback signature |
|----------|--------------------|
| `handlePos` | `(x, y)` |
| `handleSize` | `(width, height)` |
| `handleClose` | `()` |
| `handleRefresh` | `()` |
| `handleFocus` | `(focused)` — boolean |
| `handleIconify` | `(iconified)` — boolean |
| `handleMaximize` | `(maximized)` — boolean. *Needs `HAVE_GLFW_SET_WINDOW_MAXIMIZE_CALLBACK`.* |
| `handleFramebufferSize` | `(width, height)` |
| `handleContentScale` | `(xscale, yscale)`. *Needs `HAVE_GLFW_SET_WINDOW_CONTENT_SCALE_CALLBACK`.* |
| `handleMouseButton` | `(button, action, mods)` |
| `handleCursorPos` | `(x, y)` — passed as integers |
| `handleCursorEnter` | `(entered)` |
| `handleScroll` | `(xoffset, yoffset)` |
| `handleKey` | `(key, scancode, action, mods)` |
| `handleChar` | `(codepoint)` |
| `handleCharMods` | `(codepoint, mods)` |
| `handleDrop` | `(...paths)` — one string argument per dropped path |

```js
win.handleKey = (key, scancode, action, mods) => {
  if (key === KEY_ESCAPE && action) win.shouldClose = true;
};
```
