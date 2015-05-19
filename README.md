# glsl-colormap

A collection of GLSL fragment shaders to draw color map like this:

![rainbow](sample/rainbow.png).

# usage

Each `*.frag` shader sources provides a `colormap` function, which takes an `float` argument `x` (`x` should be: `0.0 <= x <= 1.0`). The `colormap` function returns a `vec4` value which represents an RGBA color.

```
vec4 colormap(float x);

void main() {
    gl_FragColor = colormap(gl_TexCoord[0].x);
}

/* include "shaders/rainbow.frag" here, for example. */
```

# special case

## gnuplot.frag

This shader emulates `gnuplot`'s `rgbformulae`, and the signature of `colormap` is:
```
vec4 colormap(float x, int red_type, int green_type, int blue_type);
```

It takes additional 3 arguments, with same meanings to `rgbformulae`'s 3 argument respectively.

# samples

|name                      |sample                                 |
|--------------------------|---------------------------------------|
|rainbow                   |![](sample/rainbow.png)                |
|apricot                   |![](sample/apricot.png)                |
|carnation                 |![](sample/carnation.png)              |
|ether                     |![](sample/ether.png)                  |
|grayscale\_banded         |![](sample/grayscale_banded.png)       |
|hot\_metal                |![](sample/hot_metal.png)              |
|lava_waves                |![](sample/lava_waves.png)             |
|malachite                 |![](sample/malachite.png)              |
|seismic                   |![](sample/seismic.png)                |
|space                     |![](sample/space.png)                  |
|morning\_glory            |![](sample/morning_glory.png)          |
|peanut\_butter\_and\_jerry|![](sample/peanut_butter_and_jerry.png)|
|purple_haze               |![](sample/purple_haze.png)            |
|rose                      |![](sample/rose.png)                   |
|saturn                    |![](sample/saturn.png)                 |
|supernova                 |![](sample/supernova.png)              |
|gnuplot (7, 5, 15)        |![](sample/gnuplot_7_5_15.png)         |
|gnuplot (3, 11, 6)        |![](sample/gnuplot_3_11_6.png)         |
|gnuplot (23, 28, 3)       |![](sample/gnuplot_23_28_3.png)        |
|gnuplot (21, 22, 23)      |![](sample/gnuplot_21_22_23.png)       |
|gnuplot (30, 31, 32)      |![](sample/gnuplot_30_31_32.png)       |
|gnuplot (33, 13, 10)      |![](sample/gnuplot_33_13_10.png)       |
|gnuplot (34, 35, 36)      |![](sample/gnuplot_34_35_36.png)       |

# license

The MIT License.
