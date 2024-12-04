Felt buggy might delete later.
This is a repo to replicate a bug I've been having with statically linking c++ object files in zig. From what I can tell so far, the issue is zig mangles symbols differently than gcc.

# Building

You can just do `zig build` or `zig build run`. I've included my object file alongside it, but if you delete it, you can run `make` in the ext/cpp directory and recompile it. I thin I did some things wrong in the c++ code so that there should be a runtime issue, but for the moment, I can't even compile.
