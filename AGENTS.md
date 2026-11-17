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

## Code style

- All private member variables must be prefixed with an underscore (e.g. `_x`, not `x`). Constructor parameters and public names stay unprefixed.
- Do not use a `get` prefix on accessors, it is redundant. Name the accessor after the property (e.g. `x()`, not `getX()`).

## Rules

- Never go against an accepted ADR. To change a decision, write a new ADR with status `Proposed` and ask the user.
- Never set an ADR status to `Accepted`.
