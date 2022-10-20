/**
 * @file config.hpp
 * @author David Schooseitner
 * @brief Configuration defines and constants
 * @version 0.1
 * @date 2022-10-18
 * 
 * @copyright David Schooseitner (c) 2022
 * 
 */

#pragma once

/**********
 *  GENERAL DEFINES
 */
#define VERSION 1.0_beta
#define VERSIONSTR "1.0_beta"

/**********
 *  DIRECTORY DEFINES
 */
#define DIR_DOC         "00_DOC"
#define DIR_DEV         "70_DEV"
#define DIR_EXT         "80_EXTERN"
#define DIR_BUILD       "90_BUILD"
#define DIR_DEBUG       DIR_BUILD "/debug"

/**
 * @brief Project namespace
 * 
 */
namespace makeproj
{

/**
 * @brief Static Data Holder Type that is used to select what to include
 * 
 */
typedef struct {
    bool doc00;
    bool gitignore;
    bool extern80;
    bool cmake;
    bool run;
    bool debug;
    bool c;
    bool cpp;
    bool wr;
} incl_dat_t;

/**
 * @brief Static Data Holder that is used to select what to include
 * 
 */
static incl_dat_t incl_dat/*{
    false, false, false, false, false, false, false, false, false
}*/;

};

/**********
 * USAGE DEFINES
 */
#define USAGE_GENERAL (                                                       "\
Usage for makeproj Ver " VERSIONSTR ":"                                     "\n\
  ->  $ makeproj <option> <value> <option> <value> ..."                     "\n\
\n\
This application creates Linux workspaces for VSCode, gnu makefile and cmake.\n\
Think of it as a simple wizard that prepares structural directories and simple files for you to be able to start coding without having to prepare too much.\n\
By default you will develop in 70_DEV, documentate in 00_DOC, build in 90_BUILD, etc.\n\
\n\
Options are determined by a minus (-) suffix."                              "\n\
Option List (* means required):"                                            "\n\
    -? [<section>] : Shows this or option-specific usage manuals"           "\n\
        Check all help sections:"                                           "\n\
          ->  $ makeproj -??"                                               "\n\
\n\
    -v : Gives version and application details"                             "\n\
\n\
*   -d <full project path, no spaces>"                                      "\n\
*   -d \"<full project path>\" : Full directory to project path, including project dir, creates dir if it does not exist\n\
\n\
*   -p <project name, no spaces>"                                           "\n\
*   -p \"<project name>\""                                                  "\n\
\n\
    -o <output file, no spaces>"                                            "\n\
    -o \"<output file>\" : By default the output name equals the project name, but this can be changed with this option\n\
\n\
    -i <inclusion 1>,<inclusion 2>,... : Basic settings that determine the project's language, whether it should use cmake, have debug, etc.\n\
        Check all inclusions via:"                                          "\n\
          ->  $ makeproj -? i"                                              "\n\
\n\
    -f <flag 1>,<flag 2>,... : Pass cc-/cxxflags onto makefile, do NOT add minuses (-) before the flags!!\n\
        Check all flag rules via:"                                          "\n\
          ->  $ makeproj -? f"                                              "\n")

#define USAGE_HELP_D (                                                      "\
Help for the directory option:"                                             "\n\
  -d or -D are options to select your project root."                        "\n\
  Keep in mind that said directory is not the project's parent, you will find 70_DEV, etc inside of this directory\n\
  Relate and absolute directories are handled by the OS itself. So you can easily cd into any directory and pass -d foobar to get the folder in current dir.\n\
\n\
  The option provides some liberty with the way you format it."             "\n\
    -d FooBar           // Valid -> \"FooBar\""                             "\n\
    -DFooBar            // Valid -> \"FooBar\""                             "\n\
    -D \"FooBar\"         // Valid -> \"FooBar\""                           "\n\
    -d\"FooBar\"          // Valid -> \"FooBar\""                           "\n\
\n\
  However, often times directories contain spaces, in that case you want to stick with using quotation marks:\n\
    -d Foo Bar          // Invalid -> \"Foo\""                              "\n\
    -d\"Foo Bar\"         // Valid -> \"Foo Bar\""                          "\n\
    -d \"    Foo Bar   \" // Valid -> \"Foo Bar\""                          "\n\
\n\
  Practical Example:"                                                       "\n\
    $ makeproj -d \"~/Documents/Proj/Foo Bar\" -p\"Foo Bar\" -o foobar -i cpp,debug,run\n")

#define USAGE_HELP_QQ (                                                     "\
List of help sections:"                                                     "\n\
  -? : Shows usage\n  -?? : Shows this\n  -? d : Shows help for the directory option\n\
  -? p : Shows help for the project name option\n  -? o : Shows help for the output file option\n\
  -? i : Lists all inclusion options\n  -? f : Shows help for the flags option\n")

#define USAGE_HELP_P (                                                      "\
Help for the project name option:"                                          "\n\
  -p Provides the a project name for your directory, which can currently only be found as a\n\
     Default output for makefile and within the header comments of makefile. \n\
  This file it free of any character restrictions aside from '/' and '\"'." "\n\
    As a result, you might want to consider giving makeproj a -o option to make the output file not invalid.\n\
\n\
  The option provides some liberty with the way you format it."             "\n\
    -p Foobar           // Valid -> \"Foobar\""                             "\n\
    -PFoobar            // Valid -> \"Foobar\""                             "\n\
    -P \"Foobar\"         // Valid -> \"Foobar\""                           "\n\
    -p\"Foobar\"          // Valid -> \"Foobar\""                           "\n\
\n\
  However, sometimes a project name can contain special characters or spaces, in that case you want to stick with quotation marks.\n\
    -p Foo bar          // Invalid -> \"Foo\""                              "\n\
    -p \"Foo bar\"        // Valid -> \"Foo bar\""                          "\n\
    -p \"Foo/bar\"        // Invalid -> Will not get accepted"              "\n\
    -p \"Foo\\\"bar\"       // Invalid -> Will probably mess up default arg parsing and not get accepted\n\
\n\
  Practical Example:"                                                       "\n\
    $ makeproj -d~/Documents/Proj/Foobar -p \"Foo Bar\" -o foo_bar -i c,run,debug\n")

#define USAGE_HELP_O (                                                      "\
Help for the output name option:"                                           "\n\
  -o Gives leniency with how your output file is going to be called."       "\n\
  By default, this option is set to the same name as -p, the project name"  "\n\
  Therefore, if your project name contained a space or a colon, said output would either be titled by an awkward or an illegal file name\n\
\n\
  This option provides some liberty with the way you use it:"               "\n\
    -o foobar           // Valid -> \"foobar\""                             "\n\
    -Ofoobar            // Valid -> \"foobar\""                             "\n\
    -O \"foobar\"         // Valid -> \"foobar\""                           "\n\
    -o\"foobar\"          // Valid -> \"foobar\""                           "\n\
\n\
  However, some characters are to be avoided within file names."            "\n\
  This application follows this website: https://www.mtu.edu/umc/services/websites/writing/characters-avoid\n\
  Their guideline applies for web-programming, but can be mostly applied for application filenames in general.\n\
\n\
  Allowed characters:"                                                      "\n\
    'a-z'; 'A-Z'; '0-9'; '-'; '_'; '+'; '.'; ','; ';';"                     "\n\
  Allowed first and last characters:"                                       "\n\
    'a-z'; 'A-Z'; '0-9'; '_';"                                              "\n\
\n\
  Examples:"                                                                "\n\
    -o \"Foo bar\"        // Invalid -> Will not be accepted"               "\n\
    -o foo-bar          // Valid -> \"foo-bar\""                            "\n\
    -o \";\"              // Invalid -> Will not be accepted"               "\n\
    -o foo_bar.exe      // Valid but questionable on linux -> \"foo_bar.exe\"\n\
\n\
  Practical Example:"                                                       "\n\
    $ makeproj -d ~/Documents/Proj/Foobar -p\"Foo Bar\" -o foo_bar -i cpp,run,debug\n\n")

#define USAGE_VERSION (                                                     "\
makeproj " VERSIONSTR " by David Schoosleitner"                             "\n\
Copyright (c) David Schoosleitner 2022"                                     "\n\
\n\
THIS PROGRAMM IS WITHOUT WARRANTY OR ANYTHING ALIKE"                        "\n")

#define USAGE_HELP_I (                                                      "\
Help for the inclusion option:"                                             "\n\
  -i Allows you to customize your project setup. With it you can easily create files, but only if you want them to.\n\
  Often times it generates one file rather than the other. Example: cmake inclusion generates CMakeList.txt but not makefile.\n\
  Unlike most options, spaces are not allowed and this rule cannot be bypassed.\n\
\n\
  List of inclusions:"                                                      "\n\
    -i c            // Makefile has CC compiler"                            "\n\
    -i cpp          // Makefile has CXX compiler (by default, unless only -i c)\n\
    -i cmake        // CMakeFile.txt is created, but makefile is not (makefile is created by default)\n\
    -i debug        // Makefile supports gdb debug building"                "\n\
    -i doc          // Create Documentation folder"                         "\n\
    -i extern       // Create Library folder"                               "\n\
    -i gitignore    // Create .gitignore file with basic rules"             "\n\
    -i run          // Makefule supports run (and rundebug when paired with debug)\n\
    -i wr           // Makefule has windres compiler (Win32 only!)"         "\n\
\n\
  Practical Example:"                                                       "\n\
    $ makeproj -d~/foo -pbar -i cpp,c,debug,run,gitignore,doc,extern"       "\n\
      // -> Project supports cpp, c building, make run, make debug, make rundebug\n\
      // -> Project creates DOC and EXTERN folder, Project created .gitignore\n\n")

#define USAGE_HELP_F (                                                      "\
Help for the flags option:"                                                 "\n\
  -f Passes CC- and CXXFLAGS onto makefile. It will build with those flags" "\n\
  makeproj will automatically add dashes before each flag, do not add dashes by yourself!\n\
\n\
  This option provides some liberty with the way you use it:"               "\n\
    -f lglfw3               // Linking with glfw3"                          "\n\
    -Fg                     // Debug"                                       "\n\
    -F \"DCUSTOM_DEF=1\"      // Define \"CUSTOM_DEF\" as one"              "\n\
\n\
  Since quotation marks are a critical character to parsing, you are not able to pass\n\
  definition flags (-DFOO=\"Bar\") intuitively."                            "\n\
  Instead, use this hardcoded workaround:"                                  "\n\
    -f \"DFOO=\"hello world\"\"   // Invalid -> Parser breaks"              "\n\
    -f \"DFOO=\\\'hello world\\\'\" // Valid -> FOO defined as c-str \"hello world\"\n\
\n\
  Practical Example:"                                                       "\n\
    $ makeproj -d~/foobar -p Foo -o foo -i cpp,run -f \"ld,lglfw,DVER=\\\'1.0_beta\\\',DVERFLOAT=1.0f\"\n\n")
    