float colormap_f(float x) {
    return (cos(133.0 * x) * 28.0 + 230.0 * x + 27.0) / 255.0;
}

vec4 colormap(float x) {
    float v = colormap_f(x);
    return vec4(v, v, v, 1.0);
}
