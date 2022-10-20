/**
 * @file main.cpp
 * @author David Schoosleitner (d.g.schoosi@gmail.com)
 * @brief main file responsible for the application and process itself
 * @version 0.1
 * @date 2022-10-18
 * 
 * @copyright Copyright (c) David Schoosleitner 2022
 * 
 */

/**********
 *  STD INCLUDES 
 */
#include <iostream>
#include <sstream>

/**********
 *  LOCAL INCLUDES
 */
#include "regexcfg.hpp"
#include "config.hpp"
#include "cr_dir.hpp"
#include "cr_make.hpp"
#include "cr_gitign.hpp"

using namespace makeproj;

/**
 * @brief Console interface, parses arguments and runs generators
 * 
 * @param argc Number of raw arguments + application name
 * @param argv All raw arguments + application name
 * @return application exit code
 */
int main(int argc, char **argv)
{
    //!! Static Incl Data init
    incl_dat.c = false;
    incl_dat.cmake = false;
    incl_dat.cpp = false;
    incl_dat.debug = false;
    incl_dat.doc00 = false;
    incl_dat.extern80 = false;
    incl_dat.gitignore = false;
    incl_dat.run = false;
    incl_dat.wr = false;

    //!!! Argument combining and parsing 
    std::stringstream ss;
    for(int i = 0; i < argc; i++)
    {
        if(std::regex_search(argv[i], regexword::_intern_space_))
            ss << '"' << argv[i] << '"' << ' ';
        else
            ss << argv[i] << ' ';
    }
    std::string args = ss.str();

    //!! Required args
    std::string proj_path{""};
    std::string proj_name{""};

    //!! Optional args
    std::string outp_name{""};
    std::string incl_gens{""};
    std::string ccflags_s{""};
    std::string help_s{""};

    //!! Smatch types
    std::smatch proj_path_sm;
    std::smatch proj_name_sm;
    std::smatch outp_name_sm;
    std::smatch incl_gens_sm;
    std::smatch ccflags_sm;
    std::smatch reserved_sm;

    //!! Matching procedure
    //! Help section
    if(std::regex_search(args, reserved_sm, regexword::help_rx))
    {
        std::string segm_s = reserved_sm[1];
        if(segm_s == "?")
        {
            std::cout << USAGE_HELP_QQ;
        }
        else if(segm_s == "d" || segm_s == "D")
        {
            std::cout << USAGE_HELP_D;
        }
        else if(segm_s == "p" || segm_s == "P")
        {
            std::cout << USAGE_HELP_P;
        }
        else if(segm_s == "o" || segm_s == "O")
        {
            std::cout << USAGE_HELP_O;
        }
        else if(segm_s == "i" || segm_s == "I")
        {
            std::cout << USAGE_HELP_I;
        }
        else if(segm_s == "f" || segm_s == "F")
        {
            std::cout << USAGE_HELP_F;
        }
        else if(segm_s == "v")
        {
            std::cout << "<3\n";
        }
        else
        {
            std::cerr << "Unrecognized segment \'" << segm_s << "\'.\nRun \'makeproj -??\' to list all segments\n";
        }

        std::cout << std::flush;
        return 0;
    }

    //! Else general help?
    if(std::regex_search(args, regexword::help_gen_rx))
    {
        std::cout << USAGE_GENERAL << std::endl;
        return 0;
    }

    //! Version
    if(std::regex_search(args, regexword::version_rx))
    {
        std::cout << USAGE_VERSION << std::endl;
        return 0;
    }

    //! Project Path
    if(std::regex_search(args, proj_path_sm, regexword::directory_bracket) ||
        std::regex_search(args, proj_path_sm, regexword::directory_no_space))
    {
        proj_path = proj_path_sm[1];
    }

    //! Project Name
    if(std::regex_search(args, proj_name_sm, regexword::proj_name_bracket) ||
        std::regex_search(args, proj_name_sm, regexword::proj_name_no_space))
    {
        proj_name = proj_name_sm[1];
    }

    //! Output File Name or use Project Name
    if(std::regex_search(args, outp_name_sm, regexword::outp_name_bracket) ||
        std::regex_search(args, outp_name_sm, regexword::outp_name_no_space))
    {
        outp_name = outp_name_sm[1];
    } else {
        outp_name = proj_name;
    }

    //! Include Generations
    if(std::regex_search(args, incl_gens_sm, regexword::incl_gen))
    {
        incl_gens = incl_gens_sm[1];
        incl_gens += ',';

        //! Include Checkups
        if(std::regex_search(incl_gens, regexword::incl_c))
        {
            incl_dat.c = true;
        }
        if(std::regex_search(incl_gens, regexword::incl_cmake))
        {
            incl_dat.cmake = true;
        }
        if(std::regex_search(incl_gens, regexword::incl_cpp))
        {
            incl_dat.cpp = true;
        }
        if(std::regex_search(incl_gens, regexword::incl_debug))
        {
            incl_dat.debug = true;
        }
        if(std::regex_search(incl_gens, regexword::incl_doc))
        {
            incl_dat.doc00 = true;
        }
        if(std::regex_search(incl_gens, regexword::incl_extern))
        {
            incl_dat.extern80 = true;
        }
        if(std::regex_search(incl_gens, regexword::incl_gitignore))
        {
            incl_dat.gitignore = true;
        }
        if(std::regex_search(incl_gens, regexword::incl_run))
        {
            incl_dat.run = true;
        }
        if(std::regex_search(incl_gens, regexword::incl_wr))
        {
            incl_dat.wr = true;
        }
    }

    //!! CCFlags
    if(std::regex_search(args, ccflags_sm, regexword::ccflags_rx_bracket) ||
        std::regex_search(args, ccflags_sm, regexword::ccflags_rx_no_space))
    {
        std::string ccflags_sr = ccflags_sm[1];
        ccflags_s = std::regex_replace(ccflags_sr, regexword::_intern_comma_, " -", std::regex_constants::match_any);
        ccflags_s = '-' + ccflags_s;
        ccflags_s = std::regex_replace(ccflags_s, regexword::_intern_quote_subst_, "\"", std::regex_constants::match_any);
    }

    //!! Checking for required
    if(
        proj_path.size() <= 0 ||
        proj_name.size() <= 0)
    {
        std::cout << USAGE_GENERAL << std::endl;
        return 0;
    }

    //!! Checking for valid output name
    if(!std::regex_match(outp_name, regexword::outp_name_allowed))
    {
        if(outp_name == proj_name)
        {
            std::cerr << "Invalid output file name!: \'" << outp_name << "\'\n"
            << "Run \'makeproj -? o\' to see filename conventions.\n"
            << "Make sure to add the -o option to override the default file name (being the project name)." << std::endl;
        } else
        {
            std::cerr << "Invalid output file name!: \'" << outp_name << "\'\n"
            << "Run \'makeproj -? o\' to see filename conventions." << std::endl; 
        }
        return 0;
    }

    //!! Create directory if not exists
    if(!cr_dir_exists(proj_path))
    {
        if(!cr_dir_mkdir(proj_path))
        {
            std::cerr << "Directory " << proj_path << " could not be created! Error occoured!" << std::endl;
            return -1;
        }
        std::cout << "Created project root " << proj_path << std::endl;
    }

    //!! Create subdirs
    if(!cr_dir_exists(proj_path + '/' + DIR_DEV))
    {
        if(!cr_dir_mkdir(proj_path + '/' + DIR_DEV))
        {
            std::cerr << "Directory " << (proj_path + '/' + DIR_DEV) << " could not be created! Error occoured!" << std::endl;
            return -1;
        }
        std::cout << "Created project subdir " << (proj_path + '/' + DIR_DEV) << std::endl;
    }
    if(!cr_dir_exists(proj_path + '/' + DIR_BUILD))
    {
        if(!cr_dir_mkdir(proj_path + '/' + DIR_BUILD))
        {
            std::cerr << "Directory " << (proj_path + '/' + DIR_BUILD) << " could not be created! Error occoured!" << std::endl;
            return -1;
        }
        std::cout << "Created project subdir " << (proj_path + '/' + DIR_BUILD) << std::endl;
    }
    if(incl_dat.doc00 && !cr_dir_exists(proj_path + '/' + DIR_DOC))
    {
        if(!cr_dir_mkdir(proj_path + '/' + DIR_DOC))
        {
            std::cerr << "Directory " << (proj_path + '/' + DIR_DOC) << " could not be created! Error occoured!" << std::endl;
            return -1;
        }
        std::cout << "Created project subdir " << (proj_path + '/' + DIR_DOC) << std::endl;
    }
    if(incl_dat.extern80 && !cr_dir_exists(proj_path + '/' + DIR_EXT))
    {
        if(!cr_dir_mkdir(proj_path + '/' + DIR_EXT))
        {
            std::cerr << "Directory " << (proj_path + '/' + DIR_EXT) << " could not be created! Error occoured!" << std::endl;
            return -1;
        }
        std::cout << "Created project subdir " << (proj_path + '/' + DIR_EXT) << std::endl;
    }

    //!! Create makefile if not using cmake
    if(!incl_dat.cmake)
    {
        if(!cr_makefile(proj_name, proj_path, outp_name, ccflags_s, incl_dat))
        {
            std::cerr << "makefile creation error!" << std::endl;
            return -1;
        }
        std::cout << "Created makefile at root" << std::endl;
    } else
    {
        if(!cr_cmakelist(proj_path, incl_dat))
        {
            std::cerr << "CMakeList.txt creation error!" << std::endl;
            return -1;
        }
        std::cout << "Created empty CMakeList.txt at root" << std::endl;
    }

    //!! Create gitignore file
    if(incl_dat.gitignore)
    {
        if(!cr_gitign(proj_path, incl_dat))
        {
            std::cerr << ".gitignore creation error!" << std::endl;
            return -1;
        }
        std::cout << "Created .gitignore at root" << std::endl;
    }

    std::cout << "\nSuccessfully created Project " << proj_name << " in " << proj_path <<
    " outputting " << outp_name << " whilst including " << incl_gens << " !\n\
    Happy coding! :)\n" << std::endl;

    return 0;
}
