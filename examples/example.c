/*
 * Examples of gnuplot_i.c usage
 * Compilation: gcc -Wall -g example.c gnuplot_i.c -o example -lm
 *
 * TODO
 * - need a test for gnuplot_splot_grid(), gnuplot_contour_plot(), gnuplot_splot_obj(), gnuplot_plot_obj_xy(), gnuplot_plot_once()
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gnuplot_i.h"

#define SECONDS 2
#define NPOINTS 50

int main(int argc, char *argv[]) {
  gnuplot_ctrl *h1, *h2, *h3, *h4;
  double x[NPOINTS], y[NPOINTS], z[NPOINTS];
  int i;

  /** Initialize the gnuplot handle */

  printf("*** Example of gnuplot control through C ***\n");
  h1 = gnuplot_init();

  /** Dumb terminal: ASCII-plot */
  /** Simplest usage of gnuplot_cmd function with fewest dependencies */

  printf("\n*** dumb terminal\n");
  gnuplot_setterm(h1, "dumb", 150, 40);
  gnuplot_cmd(h1, "plot sin(x) w lines, cos(x) w lines");
  sleep(SECONDS);

  /** Equations */

  printf("\n*** various equations\n");
  gnuplot_setterm(h1, "wxt", 900, 400);
  gnuplot_resetplot(h1);
  printf("y = sin(x)\n");
  gnuplot_plot_equation(h1, "sin(x)", "sine points");
  sleep(SECONDS);
  printf("y = sin(x)*cos(2*x)\n");
  gnuplot_setstyle(h1, "lines");
  gnuplot_plot_equation(h1, "sin(x)*cos(2*x)", "sines lines");
  sleep(SECONDS);
  printf("y = 2*x-1\n");
  gnuplot_setstyle(h1, "dots");
  gnuplot_plot_equation(h1, "2*x-1", "slope dots");
  sleep(SECONDS);

  /** Styles */

  printf("\n*** showing styles\n");
  gnuplot_resetplot(h1);
  printf("sine in points\n");
  gnuplot_setstyle(h1, "linespoints");
  gnuplot_plot_equation(h1, "sin(x)", "sine linespoints");
  sleep(SECONDS);
  printf("sine in impulses\n");
  gnuplot_setstyle(h1, "impulses");
  gnuplot_plot_equation(h1, "sin(x)", "sine impulses");
  sleep(SECONDS);
  printf("arctangens in steps\n");
  gnuplot_setstyle(h1, "steps");
  gnuplot_plot_equation(h1, "atan(x)", "arctangens steps");
  sleep(SECONDS);

  /** User defined 1d and 2d point sets */

  printf("\n*** user-defined lists of doubles\n");
  gnuplot_resetplot(h1);
  gnuplot_setstyle(h1, "impulses");
  gnuplot_set_axislabel(h1, "x", "X");
  gnuplot_set_axislabel(h1, "y", "quadratic");
  for (i = 0; i < NPOINTS; i++) {
    x[i] = (double)i * i;
  }
  gnuplot_plot_x(h1, x, NPOINTS, "user-defined doubles");
  sleep(SECONDS);
  printf("*** user-defined lists of points\n");
  for (i = 0; i < NPOINTS; i++) {
    x[i] = (double)i;
    y[i] = (double)i * (double)i;
  }
  gnuplot_resetplot(h1);
  gnuplot_setstyle(h1, "points");
  gnuplot_plot_xy(h1, x, y, NPOINTS, "user-defined points");
  sleep(SECONDS);

  /** Splot example */

  printf("\n*** parametric 3D plot\n");
  gnuplot_resetplot(h1);
  gnuplot_setstyle(h1, "lines");
  gnuplot_set_axislabel(h1, "x", "X");
  gnuplot_set_axislabel(h1, "y", "Y");
  gnuplot_set_axislabel(h1, "z", "Z-axis");
  for (int i = 0; i < NPOINTS; i++) {
    x[i] = 2*sin((double)i/3);
    y[i] = 5*sin((double)i/2 + 1);
    z[i] = x[i] + y[i];
  }
  print_gnuplot_handle(h1);  // Showing internal debugging information
  gnuplot_splot(h1, x, y, z, NPOINTS, "Lissajous");
  sleep(SECONDS);

  /** Scatter plot: gnuplot example with data file */

  printf("\n*** scatter plot\n");
  gnuplot_resetplot(h1);
  gnuplot_set_axislabel(h1, "x", "avg(mRS)");
  gnuplot_set_axislabel(h1, "y", "alpha");
  gnuplot_cmd(h1, "plot 'scatter.data' with points pointtype '🞄' linecolor 'blue'");
  sleep(SECONDS);

  /** Multiple output screens */

  printf("\n*** multiple output windows\n");
  gnuplot_resetplot(h1);
  gnuplot_setstyle(h1, "lines");
  h2 = gnuplot_init();
  gnuplot_setstyle(h2, "lines");
  h3 = gnuplot_init();
  gnuplot_setstyle(h3, "lines");
  h4 = gnuplot_init();
  gnuplot_setstyle(h4, "lines");
  printf("window 1: sin(x)\n");
  gnuplot_plot_equation(h1, "sin(x)", "sin(x)");
  sleep(SECONDS);
  printf("window 2: x*sin(x)\n");
  gnuplot_plot_equation(h2, "x*sin(x)", "x*sin(x)");
  sleep(SECONDS);
  printf("window 3: log(x)/x\n");
  gnuplot_plot_equation(h3, "log(x)/x", "log(x)/x");
  sleep(SECONDS);
  printf("window 4: sin(x)/x\n");
  gnuplot_plot_equation(h4, "sin(x)/x", "sin(x)/x");
  sleep(SECONDS);

  /** Close gnuplot handles */

  printf("\n*** closing all gnuplot windows\n");
  gnuplot_close(h1);
  gnuplot_close(h2);
  gnuplot_close(h3);
  gnuplot_close(h4);
  return 0;
}
