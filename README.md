*This project has been created as part of the 42 curriculum by <ifreire>,<inaomi-i>.*

# push_swap

Sort a random list of integers, held in stack `a`, into ascending order
using only two stacks and a limited set of operations — with the
fewest operations possible.

## Status

🚧 Work in progress. See the [Project board / Issues] for current tasks.

| Part | Status |
|---|---|
| Stack data structure + operations (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`) | ☐ |
| Argument parsing & error handling | ☐ |
| Disorder metric | ☐ |
| Simple sort — O(n²) | ☐ |
| Medium sort — O(n·√n) | ☐ |
| Complex sort — O(n log n) | ☐ |
| Adaptive sort | ☐ |
| `--bench` mode | ☐ |
| Bonus: `checker` | ☐ |
| README fully documented | ☐ |

## Description

`push_swap` takes a list of distinct integers as arguments and prints,
to stdout, the shortest sequence of stack operations that sorts them
into ascending order in stack `a`. Four sorting strategies must be
implemented (`--simple`, `--medium`, `--complex`, `--adaptive`), each
targeting a different operation-count complexity class.

## Instructions

```bash
git clone <this-repo-url>
cd push_swap
make
./push_swap 2 1 3 6 5 8
```

Optional flags: `--simple` `--medium` `--complex` `--adaptive` (default)
and `--bench` (prints metrics to stderr).

## Team

| Login | Role in this project |
|---|---|
| <login1> | |
| <login2> | |

## Resources

- Subject PDF (kept in `docs/` or linked here).
- *(to be filled as we go: articles, references, and a note on how AI was used — see subject Chapter III)*

## License

Educational project — 42 curriculum.
