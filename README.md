Build (emscripten)
==================

```
mkdir build && cd build
emcmake cmake .. -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ninja
```

Build (linux)
==================

```
mkdir buildl && cd buildl
cmake .. -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ninja
```

Run (emscripten)
================

```
cd build
python -m http.server
```
