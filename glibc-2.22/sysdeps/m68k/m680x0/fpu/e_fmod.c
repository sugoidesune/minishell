/* Copyright (C) 1996-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <math.h>
#include <math_private.h>
#include "mathimpl.h"

#ifndef FUNC
# define FUNC __ieee754_fmod
# define FUNC_FINITE __fmod_finite
#endif
#ifndef float_type
# define float_type double
#endif

float_type
FUNC (x, y)
     float_type x;
     float_type y;
{
  return __m81_u(FUNC)(x, y);
}
#ifdef FUNC_FINITE
strong_alias (FUNC, FUNC_FINITE)
#endif
