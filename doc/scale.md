# `scale.c` — `Scale` class

A 2D floating-point scale (`x`, `y`). Returned by `Monitor.contentScale`.

```js
import { Scale } from 'glfw';
```

## Constructor

```js
new Scale(x, y)           // two numbers (coerced to float64)
new Scale(other)          // copy of another Scale
```

## Instance properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `x` | get/set | number | Enumerable. |
| `y` | get/set | number | Enumerable. |

## Iteration

`Scale` is iterable, yielding `[x, y]`:

```js
const s = new Scale(1.5, 1.5);
const [sx, sy] = s;
console.log([...s]);          // [1.5, 1.5]
```

`Object.prototype.toString` tag: `GLFWscale`.
