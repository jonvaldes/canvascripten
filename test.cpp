#include <emscripten/emscripten.h>
#include <stdio.h>
#include <math.h>

extern "C" {

void EMSCRIPTEN_KEEPALIVE paint(unsigned char* u8pixels, int width, int height, float time) {
    unsigned int* pixels = (unsigned int*)u8pixels;
    for(int y = 0; y < height; y++) {
        float fy = y / (float)height;
        int stride = y * width;
        for(int x = 0; x < width; x++) {
            float fx = x / (float)width;
            int c = 0xFF;

            float px = -1.0 + 2.0 * fx;
            float py = -1.0 + 2.0 * fy;
            px *= width / (float)height;

            // animation
            float tz = 0.5 - 0.5 * cos(0.225 * time * 0.001);
            float zoo = pow(0.5, 13.0 * tz);
            float cx = -0.05 + px * zoo;
            float cy = 0.6805 + py * zoo;

            // iterate
            float zx = 0.0f, zy = 0.0f;
            float m2 = 0.0f;
            float dzx = 0.0, dzy = 0.0;

            for(int i = 0; i < 256; i++) {
                if(m2 > 1024.0)
                    continue;

                // Z' -> 2·Z·Z' + 1
                float tempX = 2.0 * (zx * dzx - zy * dzy) + 1.0;
                dzy = 2.0 * (zx * dzy + zy * dzx);
                dzx = tempX;

                // Z -> Z² + c
                tempX = zx * zx - zy * zy + cx;
                zy = 2.0 * zx * zy + cy;
                zx = tempX;

                m2 = zx * zx + zy * zy;
            }
            // distance
            float d = 0.5 * sqrt((zx * zx + zy * zy) / (dzx * dzx + dzy * dzy)) * log(zx * zx + zy * zy);

            // do some soft coloring based on distance
            d = 8.0 * d / zoo;
            d = d < 0 ? 0.0 : d > 1 ? 1.0 : d;

            d = pow(d, 0.25);
            unsigned char v = d * 255;
            pixels[x + stride] = v | v << 8 | v << 16 | 0xFF000000;
        }
    }
}
}
