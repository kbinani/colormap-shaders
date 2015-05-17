# glsl-colormap

A collection of GLSL fragment shaders to draw color map like this:

![rainbow](sample/rainbow.png).

# usage

Each `*.frag` shader sources provide a `colormap` function, which takes an `foat` argument `x` (`x` should be: `0.0 <= x <= 1.0`). `colormap` function returns `vec4` value which represents a RGBA color.

```
/* include "rainbow.frag" here, for example. */

void main() {
    gl_FragColor = colormap(gl_TexCoord[0].x);
}
```

# samples

|name            |sample                          |
|----------------|--------------------------------|
|rainbow         |![](sample/rainbow.png)         |
|apricot         |![](sample/apricot.png)         |
|carnation       |![](sample/carnation.png)       |
|ether           |![](sample/ether.png)           |
|grayscale_banded|![](sample/grayscale_banded.png)|
|hot_metal       |![](sample/hot_metal.png)       |
|lava_waves      |![](sample/lava_waves.png)      |
|malachite       |![](sample/malachite.png)       |
|seismic         |![](sample/seismic.png)         |
|space           |![](sample/space.png)           |

# license

The MIT License.
