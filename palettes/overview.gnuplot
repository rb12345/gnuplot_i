#!/usr/bin/gnuplot
#
# Create overview of all palettes
#
# AUTHOR: Hagen Wierstorf
# gnuplot 5.0 patchlevel 3

reset
set loadpath '../'

# terminal type wxt
#set terminal wxt size 1024,1943 enhanced font 'Arial,10' persist
# terminal type png
set terminal pngcairo size 1024,1443 enhanced font 'Verdana,10'
set output 'overview.png'

unset key
unset border
unset key
unset tics
unset colorbox

# function for filigraines
f(x,i) = cos(x - 1.0 + i/10.0)

set xrange [0:pi]

# change multiplot layout upon every addition / removal of a palette
set multiplot layout 5,4

# palettes with 8 colors
do for [pal in "\
    moreland bentcoolwarm \
    blues greens lapislazuli oranges purples reds \
    "] {
    filename = pal . '.palette'
    load filename
    # plot colorbar
    set lmargin 4
    set rmargin 0
    plot 'overview.txt' matrix w image
    # plot lines
    set label 1 pal at -1,0 left front
    set lmargin 1
    set rmargin 1
    plot for [ii=1:8] f(x,ii) ls ii lw 2
    unset label
}

# palettes with 9 colors
do for [pal in "magma"] {
    filename = pal . '.palette'
    load filename
    # plot colorbar
    set lmargin 4
    set rmargin 0
    plot 'overview.txt' matrix w image
    # plot lines
    set label 1 pal at -1,0 left front
    set lmargin 1
    set rmargin 1
    plot for [ii=1:9] f(x,ii) ls ii lw 2
    unset label
}

# palettes with 5 colors
do for [pal in "greys"] {
    filename = pal . '.palette'
    load filename
    # plot colorbar
    set lmargin 4
    set rmargin 0
    plot 'overview.txt' matrix w image
    # plot lines
    set label 1 pal at -1,0 left front
    set lmargin 1
    set rmargin 1
    plot for [ii=1:5] f(x,ii) ls ii lw 2
    unset label
}

unset multiplot
