# Agents

## Commands

**Build:**
```
make build
```

**Run:**
```
make run
```

**Test:**
```
make test
```

**Clean:**
```
make clean
```

**Format:**
```
make format
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for dev container setup, make commands, TDD workflow, and how to work with ADRs.

See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for community standards.

## Architecture decisions

Our architecture decisions live in `docs/adr/`. Read them before changing the build system, tooling, or test setup.

New classes go in the folder of their concept under `src/` (`math/`, `geometry/`, `colour/`, `render/`), with the header and cpp side by side, for example `src/geometry/sphere.h`. Their tests go in the matching folder under `tests/`, for example `tests/geometry/test_sphere.cpp` (see [ADR 0005](docs/adr/0005-source-layout-by-concept.md) and [ADR 0006](docs/adr/0006-concept-folders.md)).

## Code style

- All private member variables must be prefixed with an underscore (e.g. `_x`, not `x`). Constructor parameters and public names stay unprefixed.
- Do not use a `get` prefix on accessors, it is redundant. Name the accessor after the property (e.g. `x()`, not `getX()`).

## How we work

- TDD: write a failing test first, then only enough code to make it pass.
- Expected values in tests come from the maths, not from running the code. If a test fails, ask before changing what it expects.
- One small step at a time, and only what was asked for.
- Keep the C++ simple: no advanced features unless asked.
- Keep the code clean: no duplication (DRY), each class and function does one thing (single responsibility), and clear names. Apply SOLID only where it solves a problem that exists today: no interfaces, base classes or patterns "for later".
- Do not build or run anything on the host: the commands run in the dev container.

## Rules

- Never go against an accepted ADR. To change a decision, write a new ADR with status `Proposed` and ask the user.
- Never set an ADR status to `Accepted`.
