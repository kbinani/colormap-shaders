# glsl-colormap

A collection of GLSL fragment shaders to draw color map like this:

![rainbow](sample/transform_rainbow.png).

# usage

Each `*.frag` shader sources provides a `colormap` function, which takes an `float` argument `x` (`x` should be: `0.0 <= x <= 1.0`). The `colormap` function returns a `vec4` value which represents an RGBA color.

```
vec4 colormap(float x);

void main() {
    gl_FragColor = colormap(gl_TexCoord[0].x);
}

/* include "shaders/rainbow.frag" here, for example. */
```

## special case

### gnuplot.frag

This shader emulates `gnuplot`'s `rgbformulae`, and the signature of `colormap` is:
```
vec4 colormap(float x, int red_type, int green_type, int blue_type);
```

It takes additional 3 arguments, with same meanings to `rgbformulae`'s 3 arguments respectively.

# usage from c++

```c++
#include <colormap/colormap.h>
#include <iostream>

int main()
{
    using namespace colormap;

    // Print RGB table of MATLAB::Jet colormap.
    MATLAB::Jet jet;
    std::cout << "category: " << jet.getCategory() << std::endl;
    std::cout << "title:    " << jet.getTitle() << std::endl;
    int const size = 256;
    for (int i = 0; i < size; ++i) {
        float const x = i / (float)size;
        Color c = jet.getColor(x);
        std::cout << x << "\t" << c.r << "\t" << c.g << "\t" << c.b << std::endl;
    }

    // Dump category and title of all colormaps.
    for (std::shared_ptr<Colormap const> const& c : ColormapList::getSharedList()) {
        std::cout << c->getCategory() << " : " << c->getTitle() << std::endl;
    }
    return 0;
}
```

# samples

## MATLAB

* http://www.mathworks.com/products/matlab/

|name          |sample                       |
|--------------|-----------------------------|
|MATLAB\_autumn|![](sample/MATLAB_autumn.png)|
|MATLAB\_bone  |![](sample/MATLAB_bone.png)  |
|MATLAB\_cool  |![](sample/MATLAB_cool.png)  |
|MATLAB\_copper|![](sample/MATLAB_copper.png)|
|MATLAB\_hot   |![](sample/MATLAB_hot.png)   |
|MATLAB\_hsv   |![](sample/MATLAB_hsv.png)   |
|MATLAB\_jet   |![](sample/MATLAB_jet.png)   |
|MATLAB\_parula|![](sample/MATLAB_parula.png)|
|MATLAB\_pink  |![](sample/MATLAB_pink.png)  |
|MATLAB\_spring|![](sample/MATLAB_spring.png)|
|MATLAB\_summer|![](sample/MATLAB_summer.png)|
|MATLAB\_winter|![](sample/MATLAB_winter.png)|

## gnuplot

* http://www.gnuplot.info/

|name                   |sample                          |
|-----------------------|--------------------------------|
|rgbformulae(7, 5, 15)  |![](sample/gnuplot_7_5_15.png)  |
|rgbformulae(3, 11, 6)  |![](sample/gnuplot_3_11_6.png)  |
|rgbformulae(23, 28, 3) |![](sample/gnuplot_23_28_3.png) |
|rgbformulae(21, 22, 23)|![](sample/gnuplot_21_22_23.png)|
|rgbformulae(30, 31, 32)|![](sample/gnuplot_30_31_32.png)|
|rgbformulae(33, 13, 10)|![](sample/gnuplot_33_13_10.png)|
|rgbformulae(34, 35, 36)|![](sample/gnuplot_34_35_36.png)|

## transform

* http://web.archive.org/web/20000520021207/http://www.fortner.com/docs/product_transform.html

|name                      |sample                                 |
|--------------------------|---------------------------------------|
|transform\_rainbow                   |![](sample/transform_rainbow.png)                |
|transform\_apricot                   |![](sample/transform_apricot.png)                |
|transform\_carnation                 |![](sample/transform_carnation.png)              |
|transform\_ether                     |![](sample/transform_ether.png)                  |
|transform\_grayscale\_banded         |![](sample/transform_grayscale_banded.png)       |
|transform\_hot\_metal                |![](sample/transform_hot_metal.png)              |
|transform\_lava\_waves               |![](sample/transform_lava_waves.png)             |
|transform\_malachite                 |![](sample/transform_malachite.png)              |
|transform\_seismic                   |![](sample/transform_seismic.png)                |
|transform\_space                     |![](sample/transform_space.png)                  |
|transform\_morning\_glory            |![](sample/transform_morning_glory.png)          |
|transform\_peanut\_butter\_and\_jerry|![](sample/transform_peanut_butter_and_jerry.png)|
|transform\_purple\_haze              |![](sample/transform_purple_haze.png)            |
|transform\_rose                      |![](sample/transform_rose.png)                   |
|transform\_saturn                    |![](sample/transform_saturn.png)                 |
|transform\_supernova                 |![](sample/transform_supernova.png)              |


# license

The MIT License.
