# `image.c` — `Image` class

Wraps a `GLFWimage` (RGBA, 4 bytes per pixel). Used for window icons and custom cursors.

```js
import { Image } from 'glfw';
```

## Constructor

```js
new Image(width, height)   // two numbers
new Image(size)            // a Size instance
```

Allocates a zero-filled `width × height` RGBA pixel buffer.

## Instance properties

| Property | Access | Type | Notes |
|----------|--------|------|-------|
| `pixels` | get | `Uint32Array` | A view over the pixel buffer (`width × height` elements, one packed RGBA value each). Writes go straight to the underlying memory. |
| `width` | get | int | Enumerable. |
| `height` | get | int | Enumerable. |

```js
const img = new Image(16, 16);
img.pixels.fill(0xff0000ff);   // fill red (RGBA byte order)
win.setIcon(img);
```

`Object.prototype.toString` tag: `GLFWimage`.

> The pixel buffer is reference-counted against the `Image`: the `Uint32Array` keeps the image
> alive for as long as the typed array is reachable.
