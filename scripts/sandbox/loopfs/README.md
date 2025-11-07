# Loop device
Mounting a 'normal' file as a mounted filesystem!

# Create the file
Being familiar with linux, there's two ways that came to mind at first for creating this file.  Not knowing the requirements, I wasn't sure which one to use.

## Touch
To create an arbitrary empty file, you can use `touch`.  The problem is that
`touch` creates an empty file with size `0`; this means that the filesystem
can't be created, and no files can be added to it!
`touch` was my first thought, but since it has no size, I wondered where the
data would be put.  Naturally, since there is no size, it actually simply can
not work.
```
touch fs-file.img
```

## Disk Dump
The next most natural answer for me was using `dd`, since you can specify the size.
```
dd -if=/dev/zero -of=$FSFILE -bs=1M --count=100
```

## Truncate
truncate -s $FSSIZE $FSFILE

## Fallocate
fallocate
