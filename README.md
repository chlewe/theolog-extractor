# TheoLog Extractor

Extractor for specific LaTeX tags of the lecture slides located at the [TheoLog repository](https://github.com/mkroetzsch/TheoLog).
Currently the tags `defbox` and `theobox` are searched for and output to a user-specified file, together with their bodies.

## How to use
```
make all
./theologExtractor <path/to/lectureN.tex> <path/to/output.file>
```
