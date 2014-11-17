This test makes C++ code draw into an HTML canvas element.

The C++ code renders to an uint8 buffer directly (without OpenGL or anything like that). That C++ code is converted to asm.js, then executed from JS making it modify the contents of an HTML canvas element.

Performance is quite low compared to GPU rendering, but still quite usable if target resolution is not very big. For "retro"-style, pixel-art stuff it should work quite well.
