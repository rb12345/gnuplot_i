Color palettes for gnuplot
==========================

Color palettes can be used to color gradients of surface plots, contour plots and heat maps.
They are supported by gnuplot since at least version 4.2.

Single colored palettes ('reds', 'greens' etc) are sequential, where the lightness value increases monotonically through the colormaps.

Dual colored palettes ('bentcoolwarm') are diverging, and are good for emphasizing both extremes of ordered data, such as
maps of temperature deviation from a mean.

A good enterprise-grade palette is `moreland.palette` from
[Kenneth Moreland](https://www.kennethmoreland.com/color-maps/).

The `magma.palette` was copied from an original developed for [Matplotlib](https://matplotlib.org).

All other palettes are from [ColorBrewer](http://colorbrewer2.org/) and were
first ported to gnuplot by [Anna Schneider](https://github.com/aschn/gnuplot-colorbrewer).

![Image](overview.png)

More [examples](http://www.gnuplotting.org/ease-your-plotting-with-config-snippets/) of usage of palettes in gnuplot.
