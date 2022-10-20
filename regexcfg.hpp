/**
 * @file regexcfg.hpp
 * @author David Schoosleitner (d.g.schoosi@gmail.com)
 * @brief Declaration of multiple regex constants relevant to e.g. arg parsing
 * @version 0.1
 * @date 2022-10-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

/**********
 *  STD INCLUDES 
 */
#include <regex>

/**
 * @brief Project namespace
 * 
 */
namespace makeproj
{

/**
 * @brief Contains std::regex constants
 * 
 */
namespace regexword
{

//! Slightly cheeky macro for saving characters and potentially a bit of oversight
#define _R(A, B) const static std::regex A{B}

_R(     _intern_space_      ,           " "                                         );
_R(     directory_no_space  ,           " -[dD] ?([^ ]+)"                           );
_R(     directory_bracket   ,           " -[dD] ?\" *([^\"]+) *\""                  );
_R(     proj_name_no_space  ,           " -[pP] ?([^ ]+)"                           );
_R(     proj_name_bracket   ,           " -[pP] ?\" *([^/\"]+) *\""                 );
_R(     outp_name_no_space  ,           " -[oO] ?([^ ]+)"                           );
_R(     outp_name_bracket   ,           " -[oO] ?\" *([^/\"]+) *\""                 );
_R(     incl_gen            ,           " -[iI] ?([^ ]+)"                           );
_R(     ccflags_rx_no_space ,           " -[fF] ?([^ ]+)"                           );
_R(     ccflags_rx_bracket  ,           " -[fF] ?\" *([^\"]+) *\""                  );
_R(     version_rx          ,           " -[vV]"                                    );
_R(     help_gen_rx         ,           " -[?]"                                     );
_R(     help_rx             ,           " -[?] ?([^ ]+)"                            );
_R(     outp_name_allowed   ,   "^(?=[a-zA-Z0-9_])[a-zA-Z0-9-_+.,;]*[a-zA-Z0-9_]$" );

_R(     _intern_comma_      ,           ","                                         );
_R(     _intern_quote_subst_,           "[\\\\]'"                                   );

_R(     incl_gitignore      ,           "gitignore,"                                );
_R(     incl_doc            ,           "doc,"                                      );
_R(     incl_extern         ,           "extern,"                                   );
_R(     incl_cmake          ,           "cmake,"                                    );
_R(     incl_run            ,           "run,"                                      );
_R(     incl_debug          ,           "debug,"                                    );
_R(     incl_c              ,           "c,"                                        );
_R(     incl_cpp            ,           "cpp,"                                      );
_R(     incl_wr             ,           "wr,"                                       );



};

};
