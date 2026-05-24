# `workarea.c` — `WorkArea` class

Wraps a monitor work area: a [`Position`](position.md) plus a [`Size`](size.md). Returned by
`Monitor.workarea`.

```js
import { WorkArea } from 'glfw';
```

## Constructor

```js
new WorkArea(x, y, width, height)   // four numbers
new WorkArea(position, size)        // Position + Size instances
```

The position and size parts may each be given independently as numbers or as a `Position`/`Size`
instance (e.g. `new WorkArea(position, width, height)` also works).

## Instance properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `position` | get/set | [`Position`](position.md) | Enumerable. |
| `size` | get/set | [`Size`](size.md) | Enumerable. |

## Iteration

`WorkArea` is iterable, yielding `[x, y, width, height]`:

```js
const wa = monitor.workarea;
const [x, y, w, h] = wa;
console.log([...wa]);          // [x, y, width, height]
```

`Object.prototype.toString` tag: `GLFWworkarea`.
