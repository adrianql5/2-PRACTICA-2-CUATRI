# Sistema Solar

Proyecto OpenGL/GLUT adaptado para compilar en Linux con `make`.

## Dependencias

En Debian/Ubuntu:

```bash
sudo apt install build-essential freeglut3-dev libglu1-mesa-dev libstb-dev
```

En otras distribuciones instala los equivalentes de:

- `g++` / herramientas de compilación
- `freeglut`
- `GLU`
- `stb`

## Compilación

```bash
make
```

## Ejecución

```bash
make run
```

Las texturas se cargan automáticamente desde el directorio actual o desde `SistemaSolarFinal/`.
