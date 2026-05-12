# qjs-glfw Reference

GLFW bindings for QuickJS. Wraps GLFW 3 for OpenGL window/context creation and input.

Import: `import { poll, Window, ... } from 'glfw';`

## Quick Start

```js
import {
  poll, Window,
  CONTEXT_VERSION_MAJOR, CONTEXT_VERSION_MINOR,
  OPENGL_PROFILE, OPENGL_CORE_PROFILE,
  OPENGL_FORWARD_COMPAT,
  RESIZABLE, SAMPLES,
} from 'glfw';

// Set window hints before creating the window
Window.hint(CONTEXT_VERSION_MAJOR, 3);
Window.hint(CONTEXT_VERSION_MINOR, 2);
Window.hint(OPENGL_PROFILE, OPENGL_CORE_PROFILE);
Window.hint(OPENGL_FORWARD_COMPAT, true);
Window.hint(RESIZABLE, false);
Window.hint(SAMPLES, 4);

const win = new Window(800, 600, 'My App');
win.makeContextCurrent();

while (!win.shouldClose) {
  // ... draw here ...
  win.swapBuffers();
  poll();
}
```

## `Window` class

### Static methods

```js
Window.hint(hint, value)   // set window/context hints before construction
```

### Constructor

```js
const win = new Window(width, height, title[, monitor, share]);
```

### Instance properties

```js
win.shouldClose          // boolean — true when user closed the window
win.size                 // { width, height }
win.position             // { x, y }
win.framebufferSize      // { width, height } — pixel size (HiDPI aware)
```

### Instance methods

```js
win.makeContextCurrent()           // make this window's GL context active
win.swapBuffers()                  // swap front/back buffers
win.setTitle(title)                // change window title
win.setShouldClose(bool)           // programmatically signal close
win.getKey(key)                    // → PRESS or RELEASE
win.getMouseButton(button)         // → PRESS or RELEASE
win.getCursorPos()                 // → { x, y }
win.setInputMode(mode, value)
win.setKeyCallback(fn)             // fn(win, key, scancode, action, mods)
win.setMouseButtonCallback(fn)     // fn(win, button, action, mods)
win.setCursorPosCallback(fn)       // fn(win, x, y)
win.setScrollCallback(fn)          // fn(win, xoffset, yoffset)
win.setFramebufferSizeCallback(fn) // fn(win, w, h)
win.setCharCallback(fn)            // fn(win, codepoint)
win.destroy()
```

## Free functions

```js
poll()                   // process pending events (non-blocking)
waitEvents()             // block until at least one event arrives
waitEventsTimeout(secs)  // block up to secs seconds
postEmptyEvent()         // wake waitEvents() from another thread
getTime()                // → seconds since init (float)
setTime(t)
getMonitors()            // → array of monitor handles
getPrimaryMonitor()      // → primary monitor handle
```

## Common constants

### Window hints

| Constant | Typical value |
|----------|--------------|
| `CONTEXT_VERSION_MAJOR` | 3 |
| `CONTEXT_VERSION_MINOR` | 2 |
| `OPENGL_PROFILE` | use with `OPENGL_CORE_PROFILE` or `OPENGL_COMPAT_PROFILE` |
| `OPENGL_CORE_PROFILE` | — |
| `OPENGL_COMPAT_PROFILE` | — |
| `OPENGL_FORWARD_COMPAT` | `true` (required on macOS) |
| `RESIZABLE` | `true` / `false` |
| `SAMPLES` | 4 (MSAA) |
| `VISIBLE` | `true` / `false` |
| `DECORATED` | `true` / `false` |
| `DOUBLEBUFFER` | `true` (default) |

### Key / action constants

`KEY_ESCAPE`, `KEY_ENTER`, `KEY_SPACE`, `KEY_LEFT`, `KEY_RIGHT`, `KEY_UP`, `KEY_DOWN`, `KEY_A`…`KEY_Z`, `KEY_0`…`KEY_9`, `KEY_F1`…`KEY_F12`, etc.

`PRESS`, `RELEASE`, `REPEAT`

### Mouse buttons

`MOUSE_BUTTON_LEFT`, `MOUSE_BUTTON_RIGHT`, `MOUSE_BUTTON_MIDDLE`

### Modifier keys (in callbacks)

`MOD_SHIFT`, `MOD_CONTROL`, `MOD_ALT`, `MOD_SUPER`
