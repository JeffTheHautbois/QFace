# Installation instructions

Prerequisets:
* [Python 3+](https://www.python.org/downloads/), newest version
* GNU Make.
    * MacOS instructions: Open Terminal.app or iTerm.app, then run `xcode-select --install`
    * Windows: If you already have cygwin or MinGW, then you may already have make preinstalled. Otherwise, you can try installing it [here](http://gnuwin32.sourceforge.net/packages/make.htm)
* cpplint. If you have pip3 installed (it should come bundled with python), you can simply use `pip3 install cpplint`.

1. Download [emscripten](http://kripken.github.io/emscripten-site/). Reccomended: make a folder called "compiler" in this repo, and keep enscripten there.
2. The C++ compiler binary is called `em++`. Update the Makefile.variable `EMSCRIPTEN_HOME` variable to the path of `em++` on your system.
3. Run `make all` while being in the root directory to compile the C++ code to javascipt.
4. Run `make server`
