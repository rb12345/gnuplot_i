/*
 * Examples of gnuplot_i.c usage
 * Compilation: gcc -Wall -g sinepng.c gnuplot_i.c -o sinepng
 *
 * This program produces a file sine.png in the same location as the executable
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../gnuplot_i.h"

int main(int argc, char * argv[]) {
  gnuplot_ctrl *handle = gnuplot_init();
  gnuplot_cmd(handle, "set terminal png");
  gnuplot_cmd(handle, "set output \"sine.png\"");
  gnuplot_plot_equation(handle, "sin(x)", "Sine wave");
  gnuplot_close(handle);

  return 0 ;
}
