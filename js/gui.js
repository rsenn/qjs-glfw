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

  set onkey(handler) {
    this.#handle.handleKey = (keycode, code, action, mods) => {
      const key =
        keycode > 0xff
          ? [
              'Escape',
              'Enter',
              'Tab',
              'Backspace',
              'Insert',
              'Delete',
              'Right',
              'Left',
              'Down',
              'Up',
              'PageUp',
              'PageDown',
              'Home',
              'End',
              ,
              ,
              ,
              ,
              ,
              ,
              ,
              ,
              ,
              ,
              'CapsLock',
              'ScrollLock',
              'NumLock',
              'PrintScreen',
              'Pause',
              ,
              ,
              ,
              ,
              ,
              'F1',
              'F2',
              'F3',
              'F4',
              'F5',
              'F6',
              'F7',
              'F8',
              'F9',
              'F10',
              'F11',
              'F12',
              'F13',
              'F14',
              'F15',
              'F16',
              'F17',
              'F18',
              'F19',
              'F20',
              'F21',
              'F22',
              'F23',
              'F24',
              'F25',
              ,
              ,
              ,
              ,
              ,
              'Numpad0',
              'Numpad1',
              'Numpad2',
              'Numpad3',
              'Numpad4',
              'Numpad5',
              'Numpad6',
              'Numpad7',
              'Numpad8',
              'Numpad9',
              'NumpadDecimal',
              'NumpadDivide',
              'NumpadMultiply',
              'NumpadSubtract',
              'NumpadAdd',
              'NumpadEnter',
              'NumpadEqual',
              ,
              ,
              ,
              'ShiftLeft',
              'ControlLeft',
              'AltLeft',
              'SuperLeft',
              'ShiftRight',
              'ControlRight',
              'AltRight',
              'SuperRight',
              'Menu'
            ][keycode - 0x100]
          : String.fromCharCode(keycode);
      const ev = {
        type: action ? 'keydown' : 'keyup',
        repeat: action > 1,
        key,
        keycode,
        code,
        altKey: !!(mods & 4),
        shiftKey: !!(mods & 1),
        ctrlKey: !!(mods & 2)
      };
      if(mods > 7) ev.mods = mods;
      if(keycode < 0x100 && !ev.shiftKey) ev.key = ev.key.toLowerCase();
      handler(ev);
    };
  }
  /*
  set onchar(handler) {
    this.#handle.handleChar = handler;
  }
  set oncharmods(handler) {
    this.#handle.handleCharMods = handler;
  }*/
}
