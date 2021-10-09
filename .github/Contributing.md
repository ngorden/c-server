# Welcome

## Required Software

- [git](https://git-scm.com/downloads)
- [GNU Make](https://www.gnu.org/software/make/)
- [GNU Compiler](https://gcc.gnu.org/), although in the future this project should be compiler agnostic.
- Pthread Library [Windows](https://sourceforge.net/projects/pthreads4w/), MacOs and Linux users should already have it 😉

## Coding Standards

This project follows and will enforce certain coding and formatting standards. If you do not follow them, you will not be able to merge your changes. This project will conform to the GNU C [formatting standards](https://www.gnu.org/prep/standards/html_node/Formatting.html).

## Setup/Clone

``` bash
git clone --recursive git@github.com:ngorden/c-server.git server-project
cd server-project
```

## Building

All that should be required is to type `make` and you're ready to go.

## Testing

All PR's will be required to test changes made as well as regression testing. Adding unit tests will also be required where appropriate.
The current preferred testing framework is [minunit](https://github.com/siu/minunit).
