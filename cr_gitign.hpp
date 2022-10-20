/**
 * @file cr_gitign.hpp
 * @author David Schoosleitner (d.g.schoosi@gmail.com)
 * @brief Responsible for creating .gitignore at project root
 * @version 0.1
 * @date 2022-10-19
 * 
 * @copyright Copyright (c) David Schoosleitner 2022
 * 
 */

#pragma once

/**********
 *  STD INCLUDES 
 */
#include <iostream>
#include <fstream>

/**********
 *  LOCAL INCLUDES 
 */
#include "config.hpp"

/**
 * @brief Project namespace
 * 
 */
namespace makeproj
{

inline const bool cr_gitign(
    std::string proj_path,
    incl_dat_t &dat)
{
    if(!dat.gitignore) return true;

    std::ofstream g(proj_path + "/.gitignore");
    g <<
    "# Custom \n\
.idea \n\
cmake-build* \n\
.vscode \n\
90_BUILD/* \n\
\n\
# Prerequisites \n\
*.d \n\
\n\
# Compiled Object files \n\
*.slo \n\
*.lo \n\
*.o \n\
*.obj \n\
\n\
# Precompiled Headers \n\
*.gch \n\
*.pch \n\
\n\
# Compiled Dynamic libraries \n\
*.so \n\
*.dylib \n\
*.dll \n\
\n\
# Fortran module files \n\
*.mod \n\
*.smod \n\
\n\
# Compiled Static libraries \n\
*.lai \n\
*.la \n\
*.a \n\
*.lib \n\
\n\
# Executables \n\
*.exe \n\
*.out \n\
*.app" << std::endl;

    g.close();
    if(g.bad())
    {
        return false;
    }
    return true;
}

};
