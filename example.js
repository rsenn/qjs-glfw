import { context, CONTEXT_VERSION_MAJOR, CONTEXT_VERSION_MINOR, OPENGL_CORE_PROFILE, OPENGL_FORWARD_COMPAT, OPENGL_PROFILE, poll, wait, RESIZABLE, SAMPLES, Window } from 'glfw';

Window.hint(CONTEXT_VERSION_MAJOR, 3);
Window.hint(CONTEXT_VERSION_MINOR, 2);
Window.hint(OPENGL_PROFILE, OPENGL_CORE_PROFILE);
Window.hint(OPENGL_FORWARD_COMPAT, true);
Window.hint(RESIZABLE, false);
Window.hint(SAMPLES, 4);

const window = new Window(800, 600, 'OpenGL');
console.log(`id: ${window.id}`);
context.current = window;

const { position, size } = window;

const { width, height } = size;
const { x, y } = position;

console.log(`width: ${width}, height: ${height}, x: ${x}, y: ${y}`);

while(!window.shouldClose) {
  window.swapBuffers();
  wait();
}
