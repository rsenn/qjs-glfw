//import { GammaRamp, Monitor, Position, Scale, Size, VideoMode, Window, WorkArea } from 'glfw';
import * as glfw from 'glfw';

export class Screen {
  static size(index = 0) {
    let monitor = glfw.Monitor.monitors[index];
    return monitor.physicalSize;
  }
}

export class Window {
  #handle = null;

  constructor(name, screenIndex = 0) {
    this.name = name;
    this.screen = screenIndex;

    const size = Screen.size(screenIndex);

    glfw.Window.hint(glfw.CONTEXT_VERSION_MAJOR, 3);
    glfw.Window.hint(glfw.CONTEXT_VERSION_MINOR, 2);
    glfw.Window.hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE);
    glfw.Window.hint(glfw.OPENGL_FORWARD_COMPAT, true);
    glfw.Window.hint(glfw.RESIZABLE, false);
    glfw.Window.hint(glfw.SAMPLES, 4);

    this.#handle = new glfw.Window(size.width, size.height, name);
  }

  move(...args) {
    this.#handle.position = new glfw.Position(...args);
  }

  resize(...args) {
    this.#handle.size = new glfw.Size(...args);
  }

  align(n = 0) {
    let s = Screen.size(this.screen);
    let rect = this.imageRect;
    let dim = new Size(rect);
    let { x, y } = dim.align(s, n);
    console.log('pos', { x, y });
    return this.move(x, y);
  }

  /* prettier-ignore */ get imageRect() {
    let {position,framebufferSize}= this.#handle;
    return {...position, ...framebufferSize};
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

  show(mat) {
    this.mat = mat;
    imshow(this.name, mat);
  }

  valueOf() {
    return this.name;
  }

  selectROI(mat, showCrosshair = true, fromCenter = false) {
    return selectROI(this.name, mat ?? this.mat, showCrosshair, fromCenter);
  }
}

export function TextStyle(fontFace = FONT_HERSHEY_PLAIN, fontScale = 1.0, thickness = -1) {
  Object.assign(this, { fontFace, fontScale, thickness });
}

Object.assign(TextStyle.prototype, {
  size(text, fn = y => {}) {
    const { fontFace, fontScale, thickness } = this;
    let baseY;
    let size = new Size(...Draw.textSize(text, fontFace, fontScale, thickness, y => (baseY = y)));

    fn(baseY);

    size.y = baseY;
    return size;
  },

  draw(mat, text, pos, color = [255, 255, 255, 255], lineThickness = FILLED, lineType = LINE_AA) {
    const { fontFace, fontScale, thickness } = this;
    Draw.text(mat, text, pos, fontFace, fontScale, color, lineThickness, lineType);
  }
});

const palette16 = [
  0x000000, 0xa00000, 0x00a000, 0xa0a000, 0x0000a0, 0xa000a0, 0x00a0a0, 0xc0c0c0, 0xa0a0a0, 0xff0000, 0x00ff00,
  0xffff00, 0x0000ff, 0xff00ff, 0x00ffff, 0xffffff
];

export function DrawText(dst, text, color, fontFace, fontSize = 13) {
  let c = color;
  let font =
    typeof fontFace == 'object' && fontFace != null && fontFace instanceof TextStyle
      ? fontFace
      : new TextStyle(fontFace, fontSize, -1);
  let lines = [...text.matchAll(/(\x1b[^a-z]*[a-z]|\n|[^\x1b\n]*)/g)].map(m => m[0]);
  let baseY;
  let size = font.size('yP', y => (baseY = y));
  let start = new Point(size.width / text.length, baseY - 3);
  let pos = new Point(start);
  let incY = (baseY || 2) + size.height + 3;

  for(let line of lines) {
    if(line == '\n') {
      pos.y += incY;
      pos.x = start.x;
      continue;
    } else if(line.startsWith('\x1b')) {
      let ansi = [...line.matchAll(/([0-9]+|[a-z])/g)].map(m => (isNaN(+m[0]) ? m[0] : +m[0]));
      if(ansi[ansi.length - 1] == 'm') {
        let n;
        for(let code of ansi.slice(0, -1)) {
          if(code == 0) continue;
          if(code == 1) n = (n | 0) + 8;
          else if(code >= 30) n = n | 0 | (code - 30);
        }
        if(n === undefined) c = color;
        else c = palette16[n];
      }
      continue;
    }
    size = font.size(line);
    font.draw(dst, line, pos, c, -1, LINE_AA);
    pos.x += size.width;
  }
}
