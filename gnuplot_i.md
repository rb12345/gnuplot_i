gnuplot_i tutorial
==================

gnuplot_i (formerly known as gnuplot_pipes) is a programmer-friendly set of C routines to use `gnuplot` as a data displayer from a C program.

Gnuplot must be installed to use this library.

The procedure to display graphics in a gnuplot session is as follows:

1. Open a new gnuplot session, referenced by a handle of type (pointer to) `gnuplot_ctrl`. This is done by calling `gnuplot_init()`:

    gnuplot_ctrl * h;
    h = gnuplot_init();

  The variable h will be used as the handle to the gnuplot session which was just opened, by all further functions.


2. Send display configuration options. The following functions to set these options are available:

    gnuplot_setstyle (handle, style)
        sets the plotting style of the next plots

    gnuplot_set_axislabel (handle, label, axis)
        sets the label for the axis identified by variable `axis` (x, y or z)

  Examples:

    gnuplot_setstyle (h, "impulses");
    gnuplot_set_axislabel (h, "my X label", 'x');
    gnuplot_set_axislabel (h, "my Y label", 'y');

  The critical routine is `gnuplot_cmd()`, which sends character strings to gnuplot as though they were typed in by a user. This routine works in a printf fashion, accepting the same kind of format string and variable number of arguments.

  The prototype is:

    gnuplot_cmd(handle, command, ...)

  Example:

    char myfile[] = "/data/file_in.dat";
    
    gnuplot_cmd(handle, "plot '%s'", myfile);
    for (int i = 0; i < 10; i++) {
        gnuplot_cmd (handle, "plot y=%d*x", i);
    }

  The following commands request the output to be done to a Postscript file named 'curve.ps':

    gnuplot_cmd(h, "set terminal postscript");
    gnuplot_cmd(h, "set output \"curve.ps\"");

  With gnuplot_cmd() it should be easy to add up some more configuration related functions where needed.


3. Send some display orders: either functions or doubles, or double points. The following functions are available:

    void gnuplot_plot_x (gnuplot_ctrl *handle, double *x, int n, char *title);

  Plots a 2d graph from a list of doubles. The x-coordinate is the index of the double in the list, the y coordinate is the double in the list.

    void gnuplot_plot_xy (gnuplot_ctrl *handle, double *x, double *y, int n, char *title);

  Plots a 2d graph from a list of points. Provide points through a list of x and a list of y coordinates. Both arrays are assumed to contain the same number of values.

    void gnuplot_splot (gnuplot_ctrl *handle, double *x, double *y, double *z, int n, char *title);

  Plots a 3d graph from a list of points, passed as arrays x, y and z. All arrays are assumed to contain the same number of values.

    void gnuplot_splot_grid (gnuplot_ctrl *handle, double *points, int rows, int cols, char *title);

  Plots a 3d graph from a grid of points, passed in the form of an array [x,y].

    void gnuplot_contour_plot (gnuplot_ctrl *handle, double *x, double *y, double *z, int nx, int ny, char *title);

  Plots a contour plot from a list of points, passed as arrays x, y and z.

    void gnuplot_splot_obj (gnuplot_ctrl *handle, void *obj, void (*getPoint)(void *, gnuplot_point *, int, int), int n, char *title);

  Plots a 3d graph using callback functions to return the points.

    void gnuplot_plot_obj_xy (gnuplot_ctrl *handle, void *obj, void (*getPoint)(void *, gnuplot_point *, int, int), int n, char *title);

  Plots a 2d graph using a callback function to return points.

    void gnuplot_plot_once (char *title, char *style, char *label_x, char *label_y, double *x, double *y, int n);

  Opens a new gnuplot session, plots the provided signal as an X or XY signal depending on a provided y, waits for a carriage return on stdin and closes the session.

    void gnuplot_plot_equation (gnuplot_ctrl *handle, char *equation, char *title);

  Plots a given equation. The general form of the equation is y=f(x), by providing the f(x) side of the equation only.

    void gnuplot_hardcopy (gnuplot_ctrl *handle, char *filename, char *color);

  Sets the terminal to Postscript, replots the graph and then resets the terminal back to x11. The use of this function supposes that it will be used in combination with one of the plotting functions.

    gnuplot_resetplot(gnuplot_ctrl *handle)

  Clears the current gnuplot display before the next plot is inserted into the same gnuplot window.


4. Close the gnuplot handle, which also removes all temporary gnuplot files from `/tmp` and `/var/tmp`.

    gnuplot_close(h);


See examples of `gnuplot_i` usage in the file 'example.c'.


Some more points before you start using gnuplot_i
-------------------------------------------------

Note that it is possible to open several gnuplot sessions from the same program. Just be careful as to which session you are talking to when using functions. Example:

    h1 = gnuplot_init();
    h2 = gnuplot_init();

    gnuplot_plot_equation(h1, "sin(x)", "sine on first session");
    gnuplot_plot_equation(h2, "log(x)", "log on second session");
    sleep(3);
    gnuplot_close(h1);
    gnuplot_close(h2);

Do not forget to close opened sessions. Not closing a session would pollute your system with temporary files. Normally your temporary directories should be cleaned automatically so every now and then, but best is to close all windows prior to closing the session.

User interactions are not part of gnuplot_i. Feel free to use your own.

No timing mechanisms are provided to leave the outputs on screen until e.g. a key is pressed. I leave it up to gnuplot_i users to provide that kind of functionality in their own application, depending on the kind of interaction they need.

gnuplot_i is completely free software. Use it for whatever you want to do with it without any fee, and do not hesitate to send feedback to me:

    <nDevil@eso.org>

If you can, I would appreciate a mention somewhere that you are using `gnuplot_i` in your application. Something like:

    "This software uses the gnuplot_i library written by N.Devillard <nDevil@eso.org>."

If you are using gnuplot_i for a web-based application, you can also add a link to the gnuplot home page:

    http://ndevilla.free.fr/

If you are so happy about this piece of code that you would like to fund more stuff like that, do not hesitate to send me cash :-)


* Nicolas Devillard - April 2000
* longradix - July 2023
