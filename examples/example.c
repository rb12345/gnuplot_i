/*
 * Examples of gnuplot_i.c usage
 * Compilation: gcc -Wall -g example.c gnuplot_i.c -o example
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "gnuplot_i.h"

#define SECONDS 1
#define NPOINTS 50

int main(int argc, char *argv[]) {
  gnuplot_ctrl *h1, *h2, *h3, *h4;
  double x[NPOINTS], y[NPOINTS];
  int i;

  /** Initialize the gnuplot handle */

  printf("*** Example of gnuplot control through C ***\n");
  h1 = gnuplot_init();
  gnuplot_setterm(h1, "wxt", 900, 400);

  /** Slopes */

  gnuplot_setstyle(h1, "lines");
  printf("*** plotting slopes\n");
  printf("y = x\n");
  gnuplot_plot_slope(h1, 1.0, 0.0, "unity slope");
  sleep(SECONDS);
  printf("y = 2*x\n");
  gnuplot_plot_slope(h1, 2.0, 0.0, "y=2x");
  sleep(SECONDS);
  printf("y = -x\n");
  gnuplot_plot_slope(h1, -1.0, 0.0, "y=-x");
  sleep(SECONDS);

  /** Equations */

  gnuplot_resetplot(h1);
  printf("\n*** various equations\n");
  printf("y = sin(x)\n");
  gnuplot_plot_equation(h1, "sin(x)", "sine");
  sleep(SECONDS);
  printf("y = log(x)\n");
  gnuplot_plot_equation(h1, "log(x)", "logarithm");
  sleep(SECONDS);
  printf("y = sin(x)*cos(2*x)\n");
  gnuplot_plot_equation(h1, "sin(x)*cos(2*x)", "sine product");
  sleep(SECONDS);

  /** Styles */

  gnuplot_resetplot(h1);
  printf("\n*** showing styles\n");
  printf("sine in points\n");
  gnuplot_setstyle(h1, "points");
  gnuplot_plot_equation(h1, "sin(x)", "sine");
  sleep(SECONDS);
  printf("sine in impulses\n");
  gnuplot_setstyle(h1, "impulses");
  gnuplot_plot_equation(h1, "sin(x)", "sine");
  sleep(SECONDS);
  printf("arctangens in steps\n");
  gnuplot_setstyle(h1, "steps");
  gnuplot_plot_equation(h1, "atan(x)", "arctangens");
  sleep(SECONDS);

  /** User defined 1d and 2d point sets */

  gnuplot_resetplot(h1);
  gnuplot_setstyle(h1, "impulses");
  gnuplot_set_axislabel(h1, "X", "x");
  gnuplot_set_axislabel(h1, "quadratic", "y");
  printf("\n*** user-defined lists of doubles\n");
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
