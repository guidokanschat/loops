# loops

## Questions

1. Is sum factorization by hand really faster than optimizations by the compiler?
1. Does hand optimization obstruct compiler optimization?
1. How does vectorization play in?
1. Plain loops vs. recursion by dimension?

## Compiler options for `g++`

```
g++ -Ofast -funroll-loops --param max-completely-peeled-insns=10000 --param max-completely-peel-times=10000
```
