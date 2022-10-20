/**
 * @file cr_dir.hpp
 * @author David Schoosleitner (d.g.schoosi@gmail.com)
 * @brief Responsible for creating directories to the path if nonexistent
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
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>
#include <regex>
#include <stdlib.h>

/**
 * @brief Project namespace
 * 
 */
namespace makeproj
{

/**
 * @brief Create project root (can create in tree form)
 * 
 * @param projroot Project root path
 * @return true if successful
 */
inline const bool cr_dir_mkdir(const std::string projroot)
{
    std::string cmd{"mkdir -p "};
    cmd += projroot;
    const int dir_err = system(cmd.c_str());
    if (dir_err < 0)
    {
        return false;
    }
    return true;
}

/**
 * @brief Check if directory exists
 * 
 * @param projroot Project root path
 * @return true is exists
 */
inline const bool cr_dir_exists(const std::string projroot)
{
    DIR *dr = opendir(projroot.c_str());
    if(dr != NULL)
    {
        closedir(dr);
        return true;
    }
    return false;
}

inline const std::string cr_tilde_replace(const std::string in_)
{
    std::string in = in_;

    std::regex tilde{"[~]"};

    const char *home = getenv("HOME");
    if(home)
        return std::regex_replace(in, tilde, home, std::regex_constants::match_any);
    return in;
}

}
