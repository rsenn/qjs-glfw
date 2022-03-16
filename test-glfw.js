import { poll, context, CONTEXT_VERSION_MAJOR, CONTEXT_VERSION_MINOR, OPENGL_PROFILE, OPENGL_CORE_PROFILE, OPENGL_FORWARD_COMPAT, RESIZABLE, SAMPLES } from 'glfw';
import { Screen, Window } from './js/gui.js';
import { glFlush, glBegin, glBindTexture, glClear, glClearColor, glEnable, glEnd, glGenTextures, glTexCoord2f, glTexParameterf, glTexImage2D, glVertex3f, glViewport, GL_COLOR_BUFFER_BIT, GL_LINEAR, GL_QUADS, GL_REPEAT, GL_RGB, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_UNSIGNED_BYTE, glDisable, glLoadIdentity, glMatrixMode, glOrtho, glPushMatrix, glPopMatrix, GL_LIGHTING, GL_MODELVIEW, GL_PROJECTION } from './js/gl.js';
//import { HSLA } from './lib/color.js';
//import { imread } from 'opencv';

function shuffle(arr, rnd = Math.random) {
  arr.sort((a, b) => 0.5 - rnd());
  return arr;
}
 

function main(...args) {
  const window = new Window(800, 600, 'OpenGL');
  //context.current = window;

  const { position, size } = window;
  const { width, height } = size;
  const { x, y } = position;
  let textures = [];

  console.log(`width: ${width}, height: ${height}, x: ${x}, y: ${y}`);

  const hues = [
    [255, 0, 0, 255],
    [255, 98, 0, 255],
    [255, 191, 0, 255],
    [221, 255, 0, 255],
    [128, 255, 0, 255],
    [30, 255, 0, 255],
    [0, 255, 64, 255],
    [0, 255, 162, 255],
    [0, 255, 255, 255],
    [0, 157, 255, 255],
    [0, 64, 255, 255],
    [34, 0, 255, 255],
    [128, 0, 255, 255],
    [225, 0, 255, 255],
    [255, 0, 191, 255],
    [255, 0, 93, 255]
  ];

  const clamp = (n, min, max) => Math.min(Math.max(min, n), max);
  const interpolate = (x, y, sigma) =>
    Array.isArray(x) ? x.map((xx, i) => interpolate(xx, y[i], sigma)) : x * (1.0 - sigma) + y * sigma;

  while(!window.shouldClose) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();
    glDisable(GL_LIGHTING);

    let time = +new Date() / 1000;
    let index = Math.floor((time * 360) / 300);
    let color = hues[index % hues.length];
    let sine = Math.sin(time * 2 * Math.PI);
    color = interpolate(color, sine >= 0 ? [255, 255, 255, 255] : [0, 0, 0, 255], Math.abs(sine) * 0.3).map(Math.round);
    //console.log("color", ...color);

    glClearColor(...color.map(n => n / 255));
    glClear(GL_COLOR_BUFFER_BIT); //clears the window to the color you want.
    // console.log('textures[0]', textures[0]);

    /* glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

     glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 100, 0);
    glTexCoord2f(1, 1);
    glVertex3f(100, 100, 0);
    glTexCoord2f(1, 0);
    glVertex3f(100, 0, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);*/

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    glFlush();

    window.update();
    poll();
  }
}

const runMain = () => {
  try {
    main(scriptArgs.slice(1));
    std.exit(0);
  } catch(error) {
    console.log('ERROR:', error);
  }
};
import('console') .catch(runMain) .then(({ Console }) => ((globalThis.console = new Console({ inspectOptions: {} })), runMain()));
