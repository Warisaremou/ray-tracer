# 0005 — Organise source and tests by concept

## Status

Accepted

## Context

All source files started in a single flat `src/` folder. That works for one
class, but a ray tracer quickly grows many (vectors, rays, shapes, materials,
cameras, image output). A flat folder of dozens of files makes it hard to see
how the code is grouped, and tests would be just as hard to match to the code
they cover.

We want to be able to go from a concept (for example "math") to its classes
and their tests without searching, and to see at a glance where a new class
belongs.

Current layout:

```
src/
├── main.cpp
└── math/
    ├── vector.h
    └── vector.cpp
tests/
├── test_main.cpp          (smoke tests)
└── math/
    ├── test_vector.cpp
    └── vector_matchers.h  (test-only helper)
```

Alternatives considered:

- **Stay flat** — simplest, but does not scale and gives no hint of structure.
- **Group by file type** (`headers/`, `sources/`) — separates things that
  change together, so each change touches several folders.
- **Group by concept, but keep tests in a separate flat folder** — tests are
  harder to find from the code they cover.

## Decision

1. Each concept gets its own folder under `src/` (for example `src/math/`).
   A class's header and source live together in that folder.
2. `tests/` mirrors `src/`. The tests for `src/math/vector.*` live in
   `tests/math/test_vector.cpp`. Helpers used only by tests (such as
   `vector_matchers.h`) live next to the tests that use them.
3. Includes start from `src/`: `#include "math/vector.h"`. The `src/`
   directory is added to the include path once, on the `raytracer_core`
   library in `CMakeLists.txt`, and consumers inherit it. A `.cpp` file may
   include its own header by bare name (`#include "vector.h"`), since the two
   sit in the same folder.
4. `main.cpp` and the cross-cutting smoke tests (`tests/test_main.cpp`) stay at
   the top level, since they do not belong to a single concept.
5. All sources except `main.cpp` are listed once, on the `raytracer_core`
   static library. The executable and the test target both link it.

## Consequences

**Positive:**
- A class, its header, and its tests are found from its concept alone.
- Include lines show where a class comes from (`math/vector.h`).
- Paths do not depend on where the including file sits, so moving a file does
  not require `../` edits elsewhere.
- Adding a source file means one line in `CMakeLists.txt`.

**Negative:**
- Someone has to decide which concept a new class belongs to, and the answer
  can be unclear or change over time. Moving a class later means updating the
  include lines of every file that uses it.
- Concept folders can be premature: a folder with a single file is overhead
  until the concept grows.
- The `tests/` mirror can drift out of date if a class is moved without moving
  its tests. Nothing enforces the mirroring.
- Source and test files are still listed by hand in `CMakeLists.txt`, so a new
  file can be forgotten.
- Without namespaces, nothing stops code in one folder from depending on any
  other, so the structure is a convention and not an enforced boundary.

## Deliberately left out for now

| Left out | Why not now | Becomes worth it when |
|---|---|---|
| **Namespaces** (for example `raytracer::math`) | Few types, no name collisions, and folder prefixes in includes already show where a class comes from. | Names start to collide (for example a `Color` or `Ray` clashing with a dependency), or the code is used by a third party. |
| **One library per folder** | A single `raytracer_core` library is enough and keeps `CMakeLists.txt` short. | Build times suffer because everything relinks, or we want to enforce which concept may depend on which (for example `math` must not depend on `shapes`). |
| **A separate `include/` folder** for public headers | Nothing outside this repository consumes the headers. | The code is shipped or installed as a library, and we need to separate public headers from implementation details. |
