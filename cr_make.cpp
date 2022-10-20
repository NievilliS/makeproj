/**
 * @file cr_make.cpp
 * @author David Schoosleitner (d.g.schoosi@gmail.com)
 * @brief Responsible for creating makefile at the project
 * @version 0.1
 * @date 2022-10-19
 * 
 * @copyright Copyright (c) David Schoosleitner 2022
 * 
 */

/**********
 *  LOCAL INCLUDES
 */
#include "cr_make.hpp"

/**
 * @brief Project namespace
 * 
 */
namespace makeproj
{

/**
 * @brief makefile creation tool
 * 
 * @param outpname Project's output file name passed from parse
 * @param ccflags CCflags passed from parse
 * @return const int Code = 0: Success | Code > 0: Error
 */
const bool cr_makefile(
    const std::string projname,
    const std::string projroot,
    const std::string outpname,
    const std::string ccflags,
    const incl_dat_t &dat
)
{
    std::ofstream f(cr_tilde_replace(projroot + "/makefile"));
    
    //! Full headcomment
    f   << CR_MAKE_HEADCOMMENT1
        << projname
        << CR_MAKE_HEADCOMMENT2
        << std::flush;
    
    f   << CR_MAKE_COMPILERCOMMENT
        << std::flush;
    
    //! C Compiler
    if(dat.c)
    {
        f   << CR_MAKE_CCDEF
            << std::flush;
    }

    //! C++ Compiler
    if(!dat.c || dat.cpp)
    {
        f   << CR_MAKE_CXXDEF
            << std::flush;
    }

    //! Windres compiler
    if(dat.wr)
    {
        f   << CR_MAKE_WINDRESDEF
            << std::flush;
    }

    //! GDB
    if(dat.debug)
    {
        f   << CR_MAKE_GDBDEF
            << std::flush;
    }

    //! Directory Comment + Build dir
    f   << CR_MAKE_DIRCOMMENT
        << CR_MAKE_BUILDDIR
        << std::flush;
    
    //! Debug build dir
    if(dat.debug)
    {
        f   << CR_MAKE_DEBUGDIR
            << std::flush;
    }

    //! Dir end and Full build args block
    f   << CR_MAKE_SRCDIR
        << CR_MAKE_BUILDARGSCOMMENT
        << CR_MAKE_OUTPUT
        << outpname
        << CR_MAKE_DOUBLE_N
        << CR_MAKE_CCFLAGS
        << ccflags
        << CR_MAKE_DOUBLE_N
        << std::flush;
    
    //! Source obj block
    f   << CR_MAKE_SOURCEOBJCOMMENT
        << CR_MAKE_SOURCEOBJ
        << std::flush;
    
    //! Debug obj block
    if(dat.debug)
    {
        f   << CR_MAKE_DEBUGOBJ
            << std::flush;
    }

    //! Script comment + mkbuild
    f   << CR_MAKE_SCRIPTCOMMENT
        << CR_MAKE_MKBUILD
        << std::flush;
    
    //! Debug build dir
    if(dat.debug)
    {
        f   << CR_MAKE_MKDEBUGBUILD
            << std::flush;
    }

    //! C application build
    if(dat.c && !dat.cpp)
    {
        f   << CR_MAKE_MKDEFAULTC
            << std::flush;
    }

    //! C++ application build
    else
    {
        f   << CR_MAKE_MKDEFAULTCPP
            << std::flush;
    }

    //! Debug application build
    if(dat.debug)
    {
        //! Debug C application
        if(dat.c && !dat.cpp)
        {
            f   << CR_MAKE_MKDEBUGC
                << std::flush;
        }

        //! Debug C++ application
        else
        {
            f   << CR_MAKE_MKDEBUGCPP
                << std::flush;
        }
    }

    //! Build C objects
    if(dat.c)
    {
        f   << CR_MAKE_OBJC
            << std::flush;
    }

    //! Build C++ objects
    else
    {
        f   << CR_MAKE_OBJCPP
            << std::flush;
    }

    //! Build Debug objects
    if(dat.debug)
    {
        //! C
        if(dat.c)
        {
            f   << CR_MAKE_OBJDEBUGC
                << std::flush;
        }

        //! CPP
        else
        {
            f   << CR_MAKE_OBJDEBUGCPP
                << std::flush;
        }
    }

    //! Build windres objects
    if(dat.wr)
    {
        f   << CR_MAKE_OBJWR
            << std::flush;
        
        //! Debug
        if(dat.debug)
        {
            f   << CR_MAKE_OBJDEBUGWR
                << std::flush;
        }
    }

    //! Clean command
    f   << CR_MAKE_MKCLEAN
        << std::flush;
    
    //! Run command
    if(dat.run)
    {
        f   << CR_MAKE_MKRUN
            << std::flush;
        
        //! Rundebug command
        if(dat.debug)
        {
            f   << CR_MAKE_MKRUNDEBUG
                << std::flush;
        }
    }

    f.close();

    if(f.bad())
    {
        return false;
    }

    return true;
}

};
