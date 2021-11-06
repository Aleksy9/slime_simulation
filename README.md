# Slime Simulation


Small project based on the work of Sebastian Lague where he simulated the behaviour of slime using Unity: `https://www.youtube.com/watch?v=X-iSQQgOd1A`. This project attempts to recreate his results but in OpenGL 4.6


## Current status

Currently, 500 ant positions are passed to the shaders using a uniform vector. This is not optimal as uniforms are limited in size and the data cannot be modified within the shaders, only in the C++ loop.

## Next steps

1. Use compute shaders and a Shader Storage Buffer Object to store info related to each slime element.
2. Make Slime elements follow trails left behind by other slimes.
3. Have the trails diffuse over time.
