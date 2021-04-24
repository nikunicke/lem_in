# Lem-In

Lem-in is an algorithmic project that requires us to find the maximum flow in a graph with both edge **and** vertex capacities. In addition to finding the maximum flow, a set number of elements should be sent trough the graph using the paths found while figuring out the maximum flow.

## Usage
- Makefile rules:

```
make            # make lem-in
make clean      # clean *.o files
make fclean     # clean *.o and binary files
make re         # make lem-in, ignoring if files have changed or not
```
- Run:
```
./lem-in < path/filename
```

## Performance
**Tested on MacBook Pro i9 16GB**

These results probably better on an iMac at school 🤪
### With output

map|~timeframe(s)
-|-
big-superposition|0.3 - 1.0

### Without output

map|~timeframe(s)
-|-
big-superposition|0.05 - 0.30

We are not really interested in other types of maps here. The generated superposition maps vary quite a bit in size and the number of ants. On this scale, most of the time is going to write operations (especially printing the result). The maximum flow algorithm is O(|V||E|^2).

## Implementation
The graph is represented by an adjacency list structure where each specific key represent some room. The keys (indexes) are hashed, meaning lookup of a room is instant (considering we do not have hash collisions). The value that the key is pointing to is a list with edges sourcing from the key (room).

Maximum flow is computed using Edmon's Karp algorithm. This implies that the path finding method used is BFS.

Output and the distribution of elements to the paths is calculated with quite trivial math. Read more about this in NOTES.md.
