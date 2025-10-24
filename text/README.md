Text
====

The initial features of this library include a `String` and `StringView`.  These
are simple containers to store text where `String` owns the backing memory and
`StringView` does not, it only references it.  This makes `StringView` lighter
weight, but has some lifetime and safety caveats.

Since then `Formatter` has been added (and is still WIP), and encoding is
planned.

## Strings

## Formatting

## Encodings
Along with storing and managing text, this library will also implement
interfaces to assist with text encoding and transcoding.  In particular Unicode
encodings are of interest, including:
- UTF-8
- UTF-16
- UTF-32
UTF-32 appears to be the best starting point, as it's the easiest to implement
encoding and transcoding software for[^1].

[^1]: [YouTube - Nic Barker: UTF-8, Explained Simply](https://www.youtube.com/watch?v=vpSkBV5vydg)

### ASCII
[ASCII](#ASCII) is a fairly basic encoding with some rudimentary handy
properties such as upper and lower case letters being separated by 32 instead of
the, perhaps expected, 26.  This makes swapping between them pretty easy with a
bit-wise operation.  And so on.

### Unicode
#### UTF-8
UTF-8 is a variable width encoding.  To explain it, I will summarize some of the
history of its development so that a logical progression can be followed.  I do
not know any of this history from primary sources, and have instead found
discussions about this primarily on [youtube][^1] instead.

When Unicode was developed [ASCII](#ASCII) had become the de-facto standard for
text encoding and transmission.  ASCII characters are actually only 7-bits,
instead of the typical 8.  Unfortunately this only allows for 127 different
characters to be represented.  This is unusable for most asian languages, and
is certainly unusable to represent multiple different languages in general, let
alone in the same document.

<fill in the rest of the history...>

|`0XXXXXXX`| First bit as `0` indicates using ASCII encoding as is.  Since
ASCII is actually 7-bits, this matches quite well, and allows for forward
compatibility of all ASCII documents to be UTF-8 compatible.

When the first bit is `1`, the number of following bits (is the first included?),
indicates how many bytes will follow (follow, or total?).  All continuation
bytes use a leading 2 bits of `10`.

#### UTF-16
#### UTF-32
