# `position.c` — `Position` class

A 2D integer position (`x`, `y`). Returned by `Window.position`, `Monitor.position`, and used
as a `WorkArea` component.

```js
import { Position } from 'glfw';
```

## Constructor

```js
new Position(x, y)        // two numbers
new Position(other)       // copy of another Position
```

Both `x` and `y` are coerced to 32-bit integers.

## Instance properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `x` | get/set | int | Enumerable. |
| `y` | get/set | int | Enumerable. |

## Iteration

`Position` is iterable, yielding `[x, y]`:

```js
const p = new Position(10, 20);
const [x, y] = p;             // 10, 20
console.log([...p]);          // [10, 20]
```

`Object.prototype.toString` tag: `GLFWposition`.
