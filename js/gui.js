import * as glfw from 'glfw';

export class Screen {
  static size(index = 0) {
    let monitor = glfw.Monitor.monitors[index];
    return monitor.physicalSize;
  }
}

export class Window {
  #handle = null;

  constructor(...args) {
    const size =
      typeof args[0] == 'number' && typeof args[1] == 'number'
        ? new glfw.Size(...args.splice(0, 2))
        : Screen.size(args[1]);
    const [name, screenIndex = 0] = args;
    console.log('size', size);
    console.log('name', name);
    console.log('screenIndex', screenIndex);

    this.name = name;
    this.screen = screenIndex;

    glfw.Window.hint(glfw.CONTEXT_VERSION_MAJOR, 3);
    glfw.Window.hint(glfw.CONTEXT_VERSION_MINOR, 2);
    glfw.Window.hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE);
    glfw.Window.hint(glfw.OPENGL_FORWARD_COMPAT, true);
    glfw.Window.hint(glfw.RESIZABLE, false);
    glfw.Window.hint(glfw.SAMPLES, 4);

    this.#handle = glfw.context.current = new glfw.Window(size.width, size.height, name);
  }

  move(...args) {
    this.#handle.position = new glfw.Position(...args);
  }

  resize(...args) {
    this.#handle.size = new glfw.Size(...args);
  }

  get size() {
    return this.#handle.size;
  }
  get position() {
    return this.#handle.position;
  }

  align(n = 0) {
    let s = Screen.size(this.screen);
    let rect = this.imageRect;
    let dim = new glfw.Size(rect);
    let { x, y } = dim.align(s, n);
    console.log('pos', { x, y });
    return this.move(x, y);
  }

  get imageRect() {
    let { x, y } = this.#handle.position;
    let { width, height } = this.#handle.framebufferSize;
    return { x, y, width, height };
  }

  get(propId) {}
  set(propId, value) {}

  setTitle(title) {
    this.#handle.title = this.title = title;
  }

  setMouseCallback(fn) {
    console.log('Window.setMouseCallback', fn);
    this.#handle.handlePos = fn;
    this.#handle.handleMouseButton = fn;
  }

  update() {
    this.#handle.swapBuffers();
  }

  show(mat) {
    this.mat = mat;
    imshow(this.name, mat);
  }

  valueOf() {
    return this.name;
  }
}
