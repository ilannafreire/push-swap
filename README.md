*This project has been created as part of the 42 curriculum by ifreire and inaomi-i.*

# push_swap

Sort a random list of integers, held in stack `a`, into ascending order
using only two stacks and a limited set of operations — with the
fewest operations possible.

## Contributions

| Login | Contributions |
|---|---|
| ifreire | Stack data structure, all 11 operations (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`), argument parsing, disorder metric, radix sort (complex), Makefile |
| inaomi-i | Selection sort (simple), chunk-based sort (medium), sort utilities, adaptive strategy, bench mode, README |

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

## Algorithms

### Disorder metric

Before any moves, the program computes a **disorder** value in [0, 1]
measuring how far stack `a` is from sorted order. It counts the fraction
of inversions over all pairs:

```
disorder = mistakes / total_pairs
```

where `mistakes` is the number of pairs `(i, j)` with `i < j` but
`a[i] > a[j]`, and `total_pairs = n*(n-1)/2`.

### 1. Simple sort — O(n²)  (`--simple`)

**Technique:** selection sort adaptation.

For each step, the minimum remaining element in stack `a` is located by
index. If its position `p` satisfies `p ≤ n - p`, it is rotated to the
top with `p` forward rotations (`ra`); otherwise with `n - p` reverse
rotations (`rra`). The element is then pushed to `b` (`pb`). After all
elements are in `b` (sorted descending from top), all are pushed back to
`a` via `pa`.

**Complexity:** Finding the minimum is O(n), done n times → **O(n²)
Push_swap operations**. Space: O(1) extra (no auxiliary arrays).

### 2. Medium sort — O(n√n)  (`--medium`)

**Technique:** chunk-based partitioning.

The value range [min, max] is divided into `⌈√n⌉` equal-width chunks.
Elements are distributed from `a` to `b` chunk by chunk (lowest chunk
first). Within each chunk (while reassembling back to `a`), a local
selection sort is applied to bring elements in sorted order before
pushing them back.

**Rationale for chunk count:** `⌈√n⌉` chunks balances the cost of the
distribution pass (O(n) rotations per chunk × √n chunks = O(n√n)) with
the local sort within each chunk (O(chunk_size²) = O(1) per element on
average for chunk_size ≈ √n).

**Complexity:** Distribution is O(n√n) operations. Local sort per chunk
is O(√n) elements × O(√n) cost each = O(n) per chunk × √n chunks =
**O(n√n) Push_swap operations total**. Space: O(√n) for the `sizes`
array.

### 3. Complex sort — O(n log n)  (`--complex`)

**Technique:** LSD radix sort on pre-computed ranks.

Before sorting, each element in `a` is assigned a **rank** (0-based
position in sorted order) by counting how many elements are strictly
smaller. This pre-computation is O(n²) time but done once and only
affects setup cost, not the operation count.

Each bit pass (from LSB to MSB over ⌈log₂ n⌉ bits) scans all elements
of `a`: those with bit `k` = 0 are pushed to `b`; those with bit `k` =
1 are rotated to the back of `a`. Then all elements from `b` are pushed
back to `a`. After ⌈log₂ n⌉ passes, `a` is sorted by rank (ascending).

**Complexity:** Each of the ⌈log₂ n⌉ passes costs O(n) operations →
**O(n log n) Push_swap operations**. Space: O(1) extra (rank stored
in each node).

### 4. Adaptive sort — O(n²) / O(n√n) / O(n log n)  (`--adaptive`, default)

**Technique:** strategy selection based on measured disorder.

| Disorder | Threshold | Strategy used | Complexity |
|---|---|---|---|
| Low | `disorder < 0.2` | Simple (selection) | O(n²) |
| Medium | `0.2 ≤ disorder < 0.5` | Medium (chunks) | O(n√n) |
| High | `disorder ≥ 0.5` | Complex (radix) | O(n log n) |

**Rationale for thresholds:**
- Below 0.2 disorder the input is nearly sorted; selection sort exploits
  this because the minimum is often close to the top, making rotations
  cheap. The quadratic bound is acceptable for small inversion counts.
- Between 0.2 and 0.5 the input is partially ordered. Chunk sort groups
  elements into regions that are already somewhat localised, reducing the
  effective work within each chunk.
- Above 0.5 the input is close to worst-case random; radix sort's
  data-independent O(n log n) cost is consistently optimal here.

## Resources

### References

- Bhargava, Aditya Y. *Grokking Algorithms: An Illustrated Guide for Programmers and Other Curious People*, Manning Publications, 2016 — accessible introduction to sorting algorithms, Big O notation, and algorithmic thinking; directly relevant to the complexity analysis required by this project.
- [push_swap — medium article by Jamie Dawson](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a) — practical walkthrough of stack-based sorting approaches.
- [42 push_swap visualiser](https://github.com/o-reo/push_swap_visualizer) — tool used to visualise and debug operation sequences.

### AI usage

GitHub Copilot (Claude Sonnet 4.6) was used during this project for the following tasks:

- **ifreire**: used AI to verify formulas (disorder metric, complexity bounds), to review edge cases in argument parsing (e.g. empty-string arguments, INT_MIN/INT_MAX bounds), and to help generate and structure the README.
- **inaomi-i**: used AI to study the structure of the chunk-based sort and understand how the distribution loop works; the resulting code was then fully reviewed and rewritten manually.
