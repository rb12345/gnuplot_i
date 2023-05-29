#include <stdio.h>
#include <stdlib.h>
#include "gnuplot_i.h"

int main(int argc, char *argv[]) {
  gnuplot_ctrl *handle;
  double phase;

  printf("*** example of gnuplot control through C ***\n");
  handle = gnuplot_init();

  for (phase = 0.1; phase < 10; phase += 0.1) {
    gnuplot_resetplot(handle);
    gnuplot_cmd(handle, "plot sin(x+%g)", phase);
  }

  for (phase = 10; phase> = 0.1; phase -= 0.1) {
    gnuplot_resetplot(handle);
    gnuplot_cmd(handle, "plot sin(x+%g)", phase);
  }

  gnuplot_close(handle);
  return 0;
}
