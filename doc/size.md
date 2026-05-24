# `size.c` — `Size` class

A 2D integer size (`width`, `height`). Returned by `Window.size`,
`Window.framebufferSize`, `Monitor.physicalSize`, and accepted by the `Window` and `Image`
constructors.

```js
import { Size } from 'glfw';
```

## Constructor

```js
new Size(width, height)   // two numbers (coerced to uint32)
new Size(other)           // copy of another Size
```

## Instance properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `width` | get/set | int | Enumerable. |
| `height` | get/set | int | Enumerable. |

## Iteration

`Size` is iterable, yielding `[width, height]`:

```js
const s = new Size(800, 600);
const [w, h] = s;             // 800, 600
console.log([...s]);          // [800, 600]
```

`Object.prototype.toString` tag: `GLFWsize`.
