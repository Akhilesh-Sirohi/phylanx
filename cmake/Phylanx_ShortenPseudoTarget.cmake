# Copyright (c) 2015 Hartmut Kaiser
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

macro(shorten_phylanx_pseudo_target target shortened_target)
  phylanx_debug("shorten_phylanx_pseudo_target" "shortening pseudo target: ${target}")
  if(WIN32)
    set(args)
    foreach(arg ${target})
      # convert to a list
      string(REPLACE "." ";" elements ${arg})
      # retrieve last element of target to be used as shortened target name
      list(GET elements -1 arg)
      set(args ${args} ${arg})
    endforeach()
    set(${shortened_target} ${args})
    phylanx_debug("shorten_phylanx_pseudo_target" "shortened pseudo target: ${${shortened_target}}")
  else()
    set(${shortened_target} ${target})
  endif()
endmacro()

