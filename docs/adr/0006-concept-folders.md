# 0006 — Concept folders and where each class lives

## Status

Accepted

## Context

[ADR 0005](0005-source-layout-by-concept.md) decided that `src/` has one
folder per concept and that `tests/` mirrors it, but it did not say which
concepts exist. The first classes (`Vector`, `Ray`, `Sphere`, `Colour`,
`Camera`) now need a home, and we want a clear rule for where the next one
goes.

## Decision

These are the concept folders, with what belongs in each. The header and the
source file of a class sit side by side in its concept folder, and `tests/`
has a folder of the same name.

| Folder | What belongs there | Classes today |
|---|---|---|
| `src/math/` | General maths that knows nothing about rendering | `Vector` |
| `src/geometry/` | Things that exist in the 3D scene and are intersected | `Ray`, `Sphere` |
| `src/colour/` | Colour values | `Colour` |
| `src/render/` | What turns a scene into pixels | `Camera` |

Includes start from `src/`, as in ADR 0005: `#include "geometry/ray.h"`.
Tests follow the concept folder: `tests/geometry/test_sphere.cpp`.

Current layout:

```
src/
├── main.cpp
├── math/      (vector.h, vector.cpp)
├── geometry/  (ray.*, sphere.*)
├── colour/    (colour.*)
└── render/    (camera.*)
tests/
├── test_main.cpp
├── test_helpers.h, test_helpers.cpp   (shared by every test)
├── math/      (test_vector.cpp)
├── geometry/  (test_sphere.cpp)
├── colour/    (test_colour.cpp)
└── render/    (test_camera.cpp)
```

Helpers shared by tests, such as the vector comparison, live in
`tests/test_helpers.h` and `tests/test_helpers.cpp`. The `tests/` folder is on
the include path of the test target, so any test writes
`#include "test_helpers.h"`.

A new class goes in the folder whose description fits it. If none fits, add a
new concept folder and a row to the table above.

Alternatives considered:

- **A folder per class inside each concept** (`src/math/vector/vector.h`).
  Tried and dropped: it made paths and includes longer, created many folders
  with two files each, and left `src/` and `tests/` with different depths.
- **One `graphics/` folder for `Colour` and `Camera`.** Too broad: a colour
  value and the object that casts rays have little in common.

## Consequences

**Positive:**
- A rule for where new classes go, and a table to update when it changes.
- Short include lines that still say where a class comes from.

**Negative:**
- Concepts overlap at the edges. `Sphere` (geometry) holds a `Colour`, and
  `Camera` (render) builds a `Ray` (geometry). Nothing enforces which folder
  may depend on which, so the table is a convention.
- The right folder for a class can be debatable, and moving it later means
  updating every include of it.
- `src/render/` and `src/colour/` hold one class each for now.

## Not decided here

Everything left out in ADR 0005 stays out: namespaces, one library per folder
and a separate `include/` folder.
