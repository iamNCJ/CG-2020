# My Solar System

## Build

```bash
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.bat
./vcpkg/vcpkg install freeglut glew # glew is needed on Windows
cmake .
```

> **Note**:
>
> 1. `GLEW` is only needed on Windows
> 2. Download the textures from GitHub's release and place them under `assets/`
