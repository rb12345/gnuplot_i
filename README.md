Extended GNUPlot wrapper
========================

This is a modification of the `gnuplot_i` library by Nicolas Devillard, which enables the following functionality:

*    3D plots, using gnuplot_splot(handle,x,y,z,n,"title");
*    Setting z-axis labels with gnuplot_set_zlabel(handle,"z-axis label");
*    Production of colour PostScript files with gnuplot_hardcopy_colour(handle,"graph.ps");
*    Windows support - added in September 2005.
*    Plotting of complex structures through the use of callbacks - see gnuplot_plot_obj_xy and gnuplot_splot_obj in gnuplot_i.c.
*    Contour plotting, using gnuplot_setstyle(handle,"lines");gnuplot_contour_plot(handle,x,y,z,nx,ny,"title");

If you have any questions or comments, these can be sent to robert.bradley@merton.oxon.org, or via my website (http://www.robert-bradley.co.uk).

Changelog
---------

2nd April 2006 - Added gnuplot_splot_grid for plotting 2D arrays of data, and restored the lost contour plotting code.

13th March 2006 - Fixed "bus error" under OS X when not using X11 and USE_AQUA environment variable is not set.

23rd November 2005 - gnuplot_contour_plot added (plots contours, use gnuplot_setstyle to set the contour style)

15th September 2005 - Added possible OS X support, plus the gnuplot_plot_obj_xy and gnuplot_splot_obj functions.

11th September 2005 - Windows support added

14th August 2005 - included fixes from the official version 2.10

2nd November 2004 - initial version uploaded (based on gnuplot_i v2.6)
