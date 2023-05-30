gnuplot C interface library
===========================

Overview
--------

This is a modification of the `gnuplot_i` interface library by Nicolas Devillard, which enables developers to create [gnuplots](http://www.gnuplot.info/) from their C programs.


Enhancements
------------

It features the following enhancements:

* 3D plots, using `gnuplot_splot(handle, x, y, z, n, "title")`.
* Setting z-axis labels with `gnuplot_set_zlabel(handle, "z-axis label")`.
* Production of colour PostScript files with `gnuplot_hardcopy_colour(handle, "graph.ps")`.
* Windows support.
* On OS X, if DISPLAY environment variable is not set, or USE_AQUA=1, then aqua is used instead of x11.
* Plotting of complex structures through the use of callbacks, see `gnuplot_plot_obj_xy` and `gnuplot_splot_obj`.
* Contour plotting with `gnuplot_setstyle(handle, "lines")` and `gnuplot_contour_plot(handle, x, y, z, nx, ny, "title")`.

If you have any questions or comments, these can be sent to robert.bradley@merton.oxon.org, or via my website (http://www.robert-bradley.co.uk).


Changelog
---------

29 May 2023 - Refactoring, stylistic improvements

02 Apr 2006 - Added gnuplot_splot_grid for plotting 2D arrays of data, and restored the lost contour plotting code.

13 Mar 2006 - Fixed "bus error" under OS X when not using X11 and USE_AQUA environment variable is not set.

23 Nov 2005 - gnuplot_contour_plot added (plots contours, use gnuplot_setstyle to set the contour style)

15 Sep 2005 - Added possible OS X support, plus the gnuplot_plot_obj_xy and gnuplot_splot_obj functions.

11 Sep 2005 - Windows support added

14 Aug 2005 - Included fixes from the official version 2.10

02 Nov 2004 - Initial version uploaded (based on gnuplot_i v2.6)


Documentation
-------------

Documentation of macros, includes, functions and prototypes can be straightforwardly generated using [doxygen](https://www.doxygen.nl) and/or the [doxywizard](https://www.doxygen.nl/manual/doxywizard_usage.html).
