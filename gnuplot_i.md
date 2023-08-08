gnuplot_i tutorial
==================

Introduction
------------

The C interface library `gnuplot_i` (formerly known as `gnuplot_pipes`) is a programmer-friendly set of C routines to use the plotting program `gnuplot` to display plots directly from a C program.

Gnuplot must be installed to use this library.

This library must be included as follows from the C program:

    #include "gnuplot_i.h"


Tutorial
--------

The procedure to display graphics in gnuplot is then as follows:


### Open a new gnuplot session

  A gnuplot session is referenced by a handle of type (pointer to) `gnuplot_ctrl`. This is done by calling `gnuplot_init()`.

  Example:

    gnuplot_ctrl * h;
    h = gnuplot_init();

  The variable h will be used as the handle to the gnuplot session which was just opened, by all further functions.


### Send display configuration options

  Gnuplot configuration options are settings such as terminal type, plotting style and labels.
  The following functions to set these options are available:

    gnuplot_setterm (gnuplot_ctrl *handle, char *terminal, int width, int height)

  Sets the terminal type for the correct system-dependent display of the plot, such as 'wxt', 'aqua', 'x11', 'png', 'windows'.

    gnuplot_setstyle (handle, style)

  Sets the plotting style of the next plots, such as 'lines', 'dots', 'linespoints'.

    gnuplot_set_axislabel (handle, axis, label)

  Sets the label for the axis identified by variable `axis` (x, y or z).

  Examples:

    gnuplot_setterm (h, "wxt", 600, 400);
    gnuplot_setstyle (h, "impulses");
    gnuplot_set_axislabel (h, 'x', "Time (secs)");
    gnuplot_set_axislabel (h, 'y', "Value");

  The critical routine is `gnuplot_cmd()`, which sends character strings to gnuplot as though they were commands typed in by a user. This routine works in a printf fashion, accepting the same kind of format string and variable number of arguments.

  The prototype is:

    gnuplot_cmd (handle, command, ...)

  Example:

    char myfile[] = "/data/file_in.dat";
    
    gnuplot_cmd (handle, "plot '%s'", myfile);
    for (int i = 0; i < 10; i++) {
        gnuplot_cmd (handle, "plot y=%d*x", i);
    }

  The following commands request the output to be saved as a Postscript file named 'curve.ps':

    gnuplot_cmd (h, "set terminal postscript");
    gnuplot_cmd (h, "set output \"curve.ps\"");

  With `gnuplot_cmd()` additional configuration related functions can be set up where needed.


### Send a display function

  The following display functions are available:

    void gnuplot_plot_x (gnuplot_ctrl *handle, double *x, int n, char *title)

  Plots a 2d graph from a list of doubles. The x-coordinate is the index of the double in the list, the y coordinate is the value in the list.

    void gnuplot_plot_xy (gnuplot_ctrl *handle, double *x, double *y, int n, char *title)

  Plots a 2d graph from a list of points. Provide points through a list of x and a list of y coordinates. Both arrays are assumed to have the same length.

    void gnuplot_splot (gnuplot_ctrl *handle, double *x, double *y, double *z, int n, char *title)

  Plots a 3d graph from a list of points, passed as arrays x, y and z. All arrays are assumed to have the same length.

    void gnuplot_splot_grid (gnuplot_ctrl *handle, double *points, int rows, int cols, char *title)

  Plots a 3d graph from a grid of points, passed in the form of an array [x,y].

    void gnuplot_contour_plot (gnuplot_ctrl *handle, double *x, double *y, double *z, int nx, int ny, char *title)

  Plots a contour plot from a list of points, passed as arrays x, y and z.

    void gnuplot_splot_obj (gnuplot_ctrl *handle, void *obj, void (*getPoint)(void *, gnuplot_point *, int, int), int n, char *title)

  Plots a 3d graph using callback functions to return the points.

    void gnuplot_plot_obj_xy (gnuplot_ctrl *handle, void *obj, void (*getPoint)(void *, gnuplot_point *, int, int), int n, char *title)

  Plots a 2d graph using a callback function to return the points.

    void gnuplot_plot_once (char *title, char *style, char *label_x, char *label_y, double *x, double *y, int n)

  Opens a new gnuplot session, plots the provided signal as an X or XY signal depending on a provided y, waits for a carriage return on stdin and closes the session.

    void gnuplot_plot_equation (gnuplot_ctrl *handle, char *equation, char *title)

  Plots a given equation. The general form of the equation is y=f(x), by providing the f(x) side of the equation only.

    void gnuplot_hardcopy (gnuplot_ctrl *handle, char *filename, char *color)

  Sets the terminal to Postscript, replots the graph and then resets the terminal back to its original setting. The use of this function supposes that it will be used in combination with one of the plotting functions.

    gnuplot_resetplot (gnuplot_ctrl *handle)

  Clears the current gnuplot display before the next plot is inserted into the same gnuplot window.


### Close the gnuplot handle

  Closing a gnuplot handle removes all temporary gnuplot files from `/tmp` and `/var/tmp` as well as frees up memory taken up by the gnuplot_ctrl handle.

  Syntax:

    gnuplot_close(h);


See examples of `gnuplot_i` usage in the directory `examples`.


Color palettes
--------------

Color palettes can be used to color gradients of surface plots, contour plots and heat maps.
They are supported by gnuplot since at least version 4.2.

A simplified enterprise-grade palette is `bentcoolwarm.palette`, developed by [Kenneth Moreland](https://www.kennethmoreland.com/color-maps/). 
This color palette is included to show how palettes can be used within `gnuplot_i`.

More palettes can be found at [ColorBrewer](http://colorbrewer2.org/) and these were
first ported to gnuplot by [Anna Schneider](https://github.com/aschn/gnuplot-colorbrewer).

More [examples](http://www.gnuplotting.org/tag/palette/) of usage of palettes in gnuplot.


Additional remarks
------------------

Note that it is possible to open several gnuplot sessions from the same program. Just be careful as to which session you are talking to when using functions. Example:

    h1 = gnuplot_init();
    h2 = gnuplot_init();

    gnuplot_plot_equation (h1, "sin(x)", "sine on first session");
    gnuplot_plot_equation (h2, "log(x)", "log on second session");
    sleep(3);
    gnuplot_close(h1);
    gnuplot_close(h2);

Do not forget to close an opened session. Not closing a session pollutes your system with temporary files. Normally your temporary directories should be cleaned automatically, for example after a restart, but closing all windows prior to closing the session is recommended.

User interactions are not part of `gnuplot_i`. It is however possible to resize the window or rotate a 3D plot with the mouse for example, as supported by gnuplot itself.

No timing mechanisms are provided to leave the outputs on screen until for example a key is pressed. However, an example of how user interaction could be provided is included in the function `gnuplot_plot_once()`.

gnuplot_i is completely free software. Use it for whatever you want without any fee, and do not hesitate to send feedback to me:

    <nDevil@eso.org>

If you can, I would appreciate a mention somewhere that you are using `gnuplot_i` in your application. Something like:

    This software uses the gnuplot_i library written by N.Devillard <nDevil@eso.org>.

If you are using `gnuplot_i` in a web-based application, you can also add a link to the gnuplot_i home page:

    http://ndevilla.free.fr/

If you are so happy about this piece of code that you would like to fund more stuff like that, do not hesitate to send me cash :-)


* Nicolas Devillard - April 2000
* Robert Bradley - 2006
* longradix - July 2023
