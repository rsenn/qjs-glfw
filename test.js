import { Screen, Window } from './js/gui.js';
import * as std from 'std';

function main(...args) {
  let size = Screen.size(0);

  console.log('screen size:', size);

  let win = new Window('Main Window');

  console.log('win:', win);

  let { imageRect } = win;
  console.log('imageRect:', imageRect);
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
