Data Structures for text-editing
================================
The naive implementation of a text editor would use something like a
`std::string`.  While naive and inarguably inefficient, it will likely still do
well for even moderately sized files.  While annoying, on modern hardware a text
file of several MiB should still perform adequately.  However this will not
scale past that, and will likely also incur annoying memory
allocation/deallocations as well as repetitive `memcpy`s.

The only operations `std::string` would be efficient for is appending to the
end.  While much editing is done in that way, the vast majority will not.  This
alone should raise a red-flag that `std::string` is not the 'correct' answer.

The general approach all of the structures below follow the same principle.
Provide some way to create a gap such that arbitrary insertion is feasible
without repeatedly copying memory for each character inserted.

- [Gap Buffer](#Gap%20Buffer)
- [Rope](#Rope)
- [Piece Table](#Piece%20Table)
- [B/B+-Tree Variants](#B/B+-Tree%20Variants)
- [Linked List of Lines (or Chunks)](Linked%20List%20of%20Lines%20(or%20Chunks))
- [CRDT-backed Buffers (Conflict-free Replicated Data Types)](CRDT-backed%20Buffers%20(Conflict-free%20Replicated%20Data%20Types))
- [Piecewise Arrays ("Chunked Array")](Piecewise%20Arrays%20("Chunked%20Array"))

## Gap Buffer
- **Definition**: Contiguous array with a *gap*, representing the cursor insertion location.
- **Operations**:
  - Insertion at cursor: just fill the gap - O(1) amortized until gap runs out.
  - Deletion at cursor: advance the gap forward - O(1).
  - Moving the cursor: requires shifting the gap to the new location - O(n) worst case.
- **Use case**: Very efficient for single-cursor editing where edits have spatial locality.
- **Downside**: Bad for large files with edits scattered all over (frequent costly gap moves). Doesn’t scale well.

### Illustation
`To be or not                                                  to be.  That is the question.`
`             ^------------------------------------------------                             `
Where *-* underneath the location represents the *gap*, and *^* represents the cursor location.  Inserting at the cursor is easy, change the next *-* into the desired character, and update the cursor.  Nothing else necessary.  Changing the cursor location involves `memcpy`.

`To be or not to be.                                                  That is the question.`
`                    ^------------------------------------------------                     `
In the above example, `to be` simply needs to be copied from after the gap, to before.  In fact, since the memory contents of the gap do not matter, `to be` could be left in memory, like so: 
`To be or not to be.                                          to be.  That is the question.`
`                    ^------------------------------------------------                     `
Note that under `to be.` is still marked with *-*, indicating it is within the gap region.

Once the gap is filled, the buffer either must be reallocated/grown, or a new buffer allocated to accomodate.

## Rope
- **Definition**: A balanced binary tree where each leaf holds a short string (~32–128 chars). Internal nodes store subtree lengths to support fast indexing.
- **Operations**:
  - Insert/delete: O(log n) to split and rebalance leaves.
  - Random access: O(log n) to traverse the tree.
  - Concatenation/splitting: O(log n).
- **Use case**: Large documents, random edits, collaborative editing. Cache-friendly since leaves are small.
- **Downside**: Larger overhead for smaller documents.

Only the leaves store actual string data.

## Piece Table
- **Definition**: Original buffer plus an "add buffer". Maintains a table of pieces: references to contiguous ranges in either buffer.
- **Operations**:
  - Insert: append text to add buffer, update table - O(1) for the text + O(log n) for piece table updates (depending on data structure).
  - Delete: adjust piece ranges - O(1).
  - Undo/redo: just adjust the table.
- **Use case**: Basis for many editors (e.g., **MS Word**). Scales well with large files. Good for undo systems.
- **Downside**: Table management can get large and fragmented without compaction.

### Illustration
   `0123456789012345678`
0: `To be or not to be.`
1: `eat pieeat cake`
Pieces Table:
```
std::vector<std::string_view> table {
// Table id
// start index
// stop index
  {0, 0, 2}, // -> `To `
  {1, 0, 6}, // -> `eat pie`
  {0, 5, 15},// -> ` or not to `
  {1, 7, 14},// -> `eat cake`
};
```
Resulting in: *To eat pie or not to eat cake*.  Which, in retrospect, doesn't make sense, but I don't want to write a different example :).

Notably the add buffer is only ever appended to.  This makes most operations faster, since append is the fastest operations for `std::string` array-like types.  As edits are made, new content is simply added to the add buffer, and new *pieces* are created to reflect the end-content.

This makes undo operations easy, as the only thing that need be stored is the piece table at the restore-state (assuming indexes are used, not pointers, since the add buffer will inevitably need reallocated at some point).

## B/B+-Tree Variants
- **Definition**: Generalization of ropes: a B-tree where leaves hold chunks of text, and internal nodes track sizes.
- **Operations**:
  - Insertion/deletion: O(log n).
  - Indexing by position: O(log n).
- **Use case**: Often used in database-like editors, collaborative systems, or when disk persistence is needed. Can be tuned for cache and disk.
- **Downside**: Complexity, memory overhead.

## Linked List of Lines (or Chunks)
- **Definition**: Each line or chunk is a node in a linked list.
- **Operations**:
  - Insert/delete line: O(1).
  - Random access: O(n).
- **Use case**: Very simple editors or when edits are line-oriented (classic Unix `ed`, `vi` internally uses something like this).
- **Downside**: Poor for random character-level access. Not cache-friendly.

### Illustration
vi-like editors primarily operate on lines.  Intuitively, they would store text as a linked-list of lines.  That way addition and removal of lines is easy/intuitive.  Additionally, 'scripts'/commands can often be executed on each applicable line itself.
```
head
-> |"#include <print>| -> |""| -> |"int main() {"|
-> |"  std::println("Hello, {}", argv[1]);"| -> |"  return 0;"| -> |"}"|
```
Then, to insert a new line is trivial, as well as removal, since it is simply
list-node insertion or removal.  Cache-locality isn't great since each line is
likely a little too small to take advantage of cache properly, however they will
likely not be cache-unfriendly due to being too long.  Many lines should fit in
cache easily; fragmentation is likely more problematic.

## CRDT-backed Buffers (Conflict-free Replicated Data Types)
- **Definition**: A distributed structure where each character or chunk has an identifier; order is maintained by partial ordering rules.
- **Operations**:
  - Insert/delete: O(log n) to integrate.
  - Merging: naturally conflict-free, supports distributed editing.
- **Use case**: Collaborative editors (Google Docs, Figma, etc.).
- **Downside**: Much higher metadata overhead (IDs can take more space than characters themselves). Not optimized for local-only editing.

## Piecewise Arrays ("Chunked Array")
- **Definition**: Divide the text into fixed-size arrays (chunks). Maintain a sequence of them (e.g., via an array or balanced tree).
- **Operations**:
  - Insert in middle of chunk: O(chunk size).
  - Split/merge chunks: O(log n) if tree-backed.
- **Use case**: Combines benefits of arrays (cache locality) with flexibility of lists. Common in hybrid designs.
- **Downside**: Implementation complexity higher than gap buffers.

## Comparison Table (rough complexity / tradeoffs)
| Structure     | Cursor Ins/Del  | Rand Ins/Del | Indexing | Undo/Redo | Scale     |
| ------------- | --------------- | ------------ | -------- | --------- | --------- |
| Gap Buffer    | O(1)            | O(n)         | O(1)     | Manual    | Poor      |
| Rope          | O(log n)        | O(log n)     | O(log n) | Easy      | Excellent |
| Piece Table   | O(1)            | O(log n)     | O(log n) | Natural   | Excellent |
| B-Tree        | O(log n)        | O(log n)     | O(log n) | Possible  | Excellent |
| Linked List   | O(1) (per line) | O(n)         | O(n)     | Manual    | Moderate  |
| CRDT Buffer   | O(log n)        | O(log n)     | O(log n) | Built-in  | Excellent |
| Chunked Array | O(chunk size)   | O(log n)     | O(log n) | Possible  | Good      |


## Conclusions
- **Small, local editing** -> *Gap buffer*.
- **Large single-user files** -> *Rope* or *Piece table*.
- **Collaborative/distributed** -> *CRDTs*.
- **Persistence and huge scale** -> *B-Tree-based*.
