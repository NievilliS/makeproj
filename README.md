# Makeproj
## A project creation tool

Makeproj is a command line project creation tool. It creates directories, subdirectories, makefiles, etc.

I recommend something like this if you do not use IDE-Integrated Compilers like me.
Creating makefiles or similar can be relatively time-consuming.

## Functionality

Makeproj is best used as a user command as `/usr/bin/makeproj` .
### It is Linux only! (But contains a windres option for some reason)

Compile via `$ make (run, debug, clean, install) [args="something"]` .

Right now you are able to create a .gitignore, a functional makefile, an empty CMakeList.txt, positively structural directories, .vscode settings for cmake, among several makefile customizations.

## Usage

```
Usage for makeproj Ver 1.0_beta:
  ->  $ makeproj <option> <value> <option> <value> ...

This application creates Linux workspaces for VSCode, gnu makefile and cmake.
Think of it as a simple wizard that prepares structural directories and simple files for you to be able to start coding without having to prepare too much.
By default you will develop in 70_DEV, documentate in 00_DOC, build in 90_BUILD, etc.

Options are determined by a minus (-) suffix.
Option List (* means required):
    -? [<section>] : Shows this or option-specific usage manuals
        Check all help sections:
          ->  $ makeproj -??

    -v : Gives version and application details

*   -d <full project path, no spaces>
*   -d "<full project path>" : Full directory to project path, including project dir, creates dir if it does not exist

*   -p <project name, no spaces>
*   -p "<project name>"

    -o <output file, no spaces>
    -o "<output file>" : By default the output name equals the project name, but this can be changed with this option

    -i <inclusion 1>,<inclusion 2>,... : Basic settings that determine the project's language, whether it should use cmake, have debug, etc.
        Check all inclusions via:
          ->  $ makeproj -? i

    -f <flag 1>,<flag 2>,... : Pass cc-/cxxflags onto makefile, do NOT add minuses (-) before the flags!!
        Check all flag rules via:
          ->  $ makeproj -? f
```

## Inclusion List
```
List of inclusions:
    -i c            // Makefile has CC compiler
    -i cpp          // Makefile has CXX compiler (by default, unless only -i c)
    -i cmake        // CMakeFile.txt is created, but makefile is not (makefile is created by default)
    -i debug        // Makefile supports gdb debug building
    -i doc          // Create Documentation folder
    -i extern       // Create Library folder
    -i gitignore    // Create .gitignore file with basic rules
    -i run          // Makefule supports run (and rundebug when paired with debug)
    -i wr           // Makefule has windres compiler (Win32 only!)
```

## Practical Examples
```bash
# From makeproj -?d:
$ makeproj -d "~/Documents/Proj/Foo Bar" -p "Foo Bar" -o foobar -i cpp,debug,run
# From makeproj -?p:
$ makeproj -d~/Documents/Proj/Foobar -p "Foo Bar" -o foo_bar -i c,run,debug
# From makeproj -?o:
$ makeproj -d ~/Documents/Proj/Foobar -p "Foo Bar" -o foo_bar -i cpp,run,debug
# From makeproj -?i:
$ makeproj -d~/foo -pbar -i cpp,c,debug,run,gitignore,doc,extern
      # -> Project supports cpp, c building, make run, make debug, make rundebug
      # -> Project creates DOC and EXTERN folder, Project created .gitignore
```
