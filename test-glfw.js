import { poll, context } from 'glfw';
import { Window } from './js/gui.js';
import { glewInit, GL_BLEND, glBlendFunc, glHint, GL_LINE_SMOOTH, GL_LINE_SMOOTH_HINT, GL_NICEST, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, glLineWidth, glTranslatef, glColor3ub, glColor3f, glFlush, glBegin, glBindTexture, glClear, glClearColor, glEnable, glEnd, glTexCoord2f, glVertex2f, glVertex3f, glViewport, GL_COLOR_BUFFER_BIT, GL_QUADS, GL_TEXTURE_2D, glDisable, glLoadIdentity, glMatrixMode, glOrtho, glPushMatrix, glPopMatrix, GL_LIGHTING, GL_MODELVIEW, GL_PROJECTION, GL_LINE_LOOP, GL_DEPTH_BUFFER_BIT } from './js/glew.js';

function shuffle(arr, rnd = Math.random) {
  arr.sort((a, b) => 0.5 - rnd());
  return arr;
}
function DrawCircle(cx, cy, r, num_segments) {
  glBegin(GL_LINE_LOOP);
  for(let ii = 0; ii < num_segments; ii++) {
    let theta = (2.0 * Math.PI * ii) / num_segments; //get the current angle
    let x = cx + r * Math.cos(theta); //calculate the x component
    let y = cy + r * Math.sin(theta); //calculate the y component
    console.log(`ii: ${ii} x: ${x} y: ${y}`);
    glVertex2f(x, y); //output vertex
  }
  glEnd();
}

function main(...args) {
  const window = new Window(800, 600, 'OpenGL');

  //console.log('gladLoadGL() =', gladLoadGL());
  console.log('glewInit() =', glewInit());

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
  const interpolate = (x, y, sigma) => (Array.isArray(x) ? x.map((xx, i) => interpolate(xx, y[i], sigma)) : x * (1.0 - sigma) + y * sigma);

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
    //

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

    //glClear( GL_DEPTH_BUFFER_BIT);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3.0);

    glLoadIdentity();
    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
    glPushMatrix();

    glTranslatef(0, 0, -10);

    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);
    glVertex3f(100, 100, 0);
    glVertex3f(100, 0, 0);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);

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
