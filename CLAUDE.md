# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A **native C module for QuickJS** that wraps GLFW 3. It builds to a shared object named
`glfw.so` (note: `PREFIX ""`, so no `lib` prefix) which is installed into QuickJS's C-module
directory and loaded from JS with `import { ... } from 'glfw'`. The module exposes GLFW window/
context/input/monitor functionality; it does **not** provide OpenGL — see "OpenGL in examples" below.

## Build

Out-of-tree CMake builds, one directory per target triple under `build/` (e.g.
`build/x86_64-linux-gnu`, plus `-debug` / `-profile` variants). `cmake/UseMultiArch.cmake` derives
the arch-specific libdir from `cc -dumpmachine`.

```sh
cmake -B build/$(cc -dumpmachine) -S .
cmake --build build/$(cc -dumpmachine)
# or, in an already-configured dir:  make -C build/x86_64-linux-gnu
```

Key requirement: **QuickJS must already be installed** (the build resolves `qjs`, `qjsc`,
`libquickjs`, and headers, defaulting to `/usr/local` via `cmake/FindQuickJS.cmake`). GLFW and a GL
loader (GLEW by default) must also be present. `install` copies `glfw.so` into the QuickJS C-module
dir so plain `import ... from 'glfw'` resolves.

CMake options:
- `BUILD_GLFW` — build the vendored `glfw/` submodule from source instead of using system GLFW.
  When set, the full `HAVE_GLFW_*` feature set is assumed; otherwise each is probed individually
  with `check_function_exists` (see below).
- `USE_GL3W` — use the gl3w loader instead of GLEW; downloads `glcorearb.h` / `khrplatform.h` from
  khronos.org at configure time and generates `gl3w.c`.

Submodules (`.gitmodules`): `glfw/` and `gl3w/`. Run `git submodule update --init` before a source build.

## Run / test

There is no test harness — `test.js`, `test-glfw.js`, and `example.js` are runnable demos that open
a window and require a display:

```sh
qjs example.js        # uses bare `import ... from 'glfw'` (needs glfw.so installed)
qjs test.js           # uses ./js/gui.js high-level wrapper
```

## Architecture

**One C file per bound GLFW type.** Each of `position`, `size`, `scale`, `video_mode`, `gamma_ramp`,
`image`, `monitor`, `workarea`, `window` has a `.c`/`.h` pair following an identical QuickJS
class-binding pattern (see `position.c` as the canonical small example):

- module-global `glfw_<type>_class_id`, `glfw_<type>_proto`, `glfw_<type>_class`
- `*_constructor`, `*_finalizer`, a proto func list (`JS_CGETSET_*` / `JS_CFUNC_*`), and a
  `JSClassDef`
- `glfw_<type>_init(ctx, m)` — creates the class, sets proto + constructor, and calls
  `JS_SetModuleExport` (runs inside the module init callback)
- `glfw_<type>_export(ctx, m)` — calls `JS_AddModuleExport` (runs at module *creation*, before init)
- `glfw_<type>_wrap(ctx, ptr)` — wraps a native pointer into a JS object with the right prototype

**`glfw.c` is the module entry point.** `js_init_module` → `JS_NewCModule(..., glfw_init)`.
`glfw_init` (init callback) and `glfw_export` (creation) each call every type's `*_init` / `*_export`
in turn, plus register the free functions and constants in `glfw_exports[]`. GLFW is initialized
lazily via `glfw_initialize` (one global `glfwInit()`).

**Adding a new bound type:** create the `.c`/`.h` pair using the pattern above, add both files to
`QJS_GLFW_SOURCES` in `CMakeLists.txt`, and add `glfw_<type>_init(...)` + `glfw_<type>_export(...)`
calls to `glfw_init` / `glfw_export` in `glfw.c`.

**Conventions worth knowing:**
- The `HAVE_GLFW_*` macros gate functions that may be absent in older GLFW. Wrap any binding to a
  newer GLFW API in the matching `#ifdef`, and add the probe in `CMakeLists.txt` (the
  `if(NOT BUILD_GLFW)` block) so system-GLFW builds detect it.
- Opaque native pointers without their own class (cursors, GL proc addresses) cross the JS boundary
  as **hex strings** via `js_newptr` / `js_getptr` (`glfw.h`).
- Window event callbacks are **assignable getset properties**, not `setXxxCallback` methods:
  `win.handleKey`, `win.handleCursorPos`, `win.handleMouseButton`, `win.handleScroll`,
  `win.handleFramebufferSize`, `win.handleChar`, etc. (full list in `window.c`
  `glfw_window_proto_handlers[]`).
- Window hints and context are static/namespaced: `Window.hint(hint, value)`, and the current GL
  context is set with `context.current = win` (or `win.makeContextCurrent()`). Event pumping is
  `poll()` and `wait([timeoutSeconds])`.

**`README.md` is partly aspirational and drifts from the source** (e.g. it lists `setKeyCallback`,
`waitEvents`, `getCursorPos`). When the docs and the C exports disagree, the truth is the
`JSCFunctionListEntry` tables in `glfw.c` and `window.c`. `TODO.md` lists window APIs not yet bound.

## OpenGL in examples (`js/`)

The native module gives you a window + GL context only. The demos draw using **separate JS-side
FFI bindings** that `import { ... } from 'ffi'` and `dlopen` the GL library at runtime:
- `js/gl.js`, `js/glew.js`, `js/glad.js` — alternative OpenGL FFI binding layers
- `js/gui.js` — high-level convenience wrapper (`Screen`, `Window`) built on top of the `glfw` module

These depend on a QuickJS `ffi` module being available and are independent of `glfw.so`.
