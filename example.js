import { context } from 'glfw';
import { CONTEXT_VERSION_MAJOR } from 'glfw';
import { CONTEXT_VERSION_MINOR } from 'glfw';
import { OPENGL_CORE_PROFILE } from 'glfw';
import { OPENGL_FORWARD_COMPAT } from 'glfw';
import { OPENGL_PROFILE } from 'glfw';
import { RESIZABLE } from 'glfw';
import { SAMPLES } from 'glfw';
import { wait } from 'glfw';
import { Window } from 'glfw';
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