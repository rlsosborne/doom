/* Emacs style mode select   -*- C++ -*- 
 *-----------------------------------------------------------------------------
 *
 * $Id: p_maputl.h,v 1.4 1999/10/12 13:00:57 cphipps Exp $
 *
 *  LxDoom, a Doom port for Linux/Unix
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *   and Colin Phipps
 *  
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 
 *  02111-1307, USA.
 *
 * DESCRIPTION:
 *      Map utility functions
 *
 *-----------------------------------------------------------------------------*/

#ifndef __P_MAPUTL__
#define __P_MAPUTL__

#include "r_defs.h"
#include "p_setup.h"
#include "doomstat.h"
#include "r_defs.h"
#include "r_state.h"
#include "r_main.h"

/* mapblocks are used to check movement against lines and things */
#define MAPBLOCKUNITS   128
#define MAPBLOCKSIZE    (MAPBLOCKUNITS*FRACUNIT)
#define MAPBLOCKSHIFT   (FRACBITS+7)
#define MAPBMASK        (MAPBLOCKSIZE-1)
#define MAPBTOFRAC      (MAPBLOCKSHIFT-FRACBITS)

#define PT_ADDLINES     1
#define PT_ADDTHINGS    2
#define PT_EARLYOUT     4

typedef struct {
  fixed_t     x;
  fixed_t     y;
  fixed_t     dx;
  fixed_t     dy;
} divline_t;

typedef struct intercept_s {
  fixed_t     frac;           /* along trace line */
  boolean     isaline;
  union {
    mobj_t* thing;
    line_t* line;
  } d;
} intercept_t;

fixed_t P_AproxDistance (fixed_t dx, fixed_t dy);
int     P_PointOnLineSide (fixed_t x, fixed_t y, const line_t *line);
int     P_BoxOnLineSide (const fixed_t *tmbox, const line_t *ld);

void    P_LineOpening (const line_t *linedef);
void    P_UnsetThingPosition(mobj_t *thing);
void    P_SetThingPosition(mobj_t *thing);

typedef enum {
  PTR_SLIDETRAVERSE,
  PTR_AIMTRAVERSE,
  PTR_SHOOTTRAVERSE,
  PTR_USETRAVERSE,
  PTR_NOWAYTRAVERSE,
} traverserfunc_t;

boolean P_PathTraverse(fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2,
                       int flags, traverserfunc_t func);

extern fixed_t opentop;
extern fixed_t openbottom;
extern fixed_t openrange;
extern fixed_t lowfloor;
extern divline_t trace;

//
// BLOCK MAP ITERATORS
// For each line/thing in the given mapblock,
// call the passed PIT_* function.
// If the function returns false,
// exit with false without checking anything else.
//

//
// P_BlockLinesIterator
// The validcount flags are used to avoid checking lines
// that are marked in multiple mapblocks,
// so increment validcount before the first call
// to P_BlockLinesIterator, then make one or more calls
// to it.
//
// killough 5/3/98: reformatted, cleaned up

template <typename T>
boolean P_BlockLinesIterator(int x, int y, T func)
{
  int        offset;
  const long *list;   // killough 3/1/98: for removal of blockmap limit
  
  if (x<0 || y<0 || x>=bmapwidth || y>=bmapheight)
    return true;
  offset = y*bmapwidth+x;
  offset = *(blockmap+offset);
  list = blockmaplump+offset;     // original was reading         // phares
  // delmiting 0 as linedef 0     // phares
  
  // killough 1/31/98: for compatibility we need to use the old method.
  // Most demos go out of sync, and maybe other problems happen, if we
  // don't consider linedef 0. For safety this should be qualified.
  
  if (!demo_compatibility) // killough 2/22/98: demo_compatibility check
    list++;     // skip 0 starting delimiter                      // phares
  for ( ; *list != -1 ; list++)                                   // phares
  {
    line_t *ld = &lines[*list];
    if (ld->validcount == validcount)
      continue;       // line has already been checked
    ld->validcount = validcount;
    if (!func(ld))
      return false;
  }
  return true;  // everything was checked
}

template <typename T>
boolean P_BlockThingsIterator(int x, int y, T func)
{
  mobj_t *mobj;
  if (!(x<0 || y<0 || x>=bmapwidth || y>=bmapheight))
    for (mobj = blocklinks[y*bmapwidth+x]; mobj; mobj = mobj->bnext)
      if (!func(mobj))
        return false;
  return true;
}

#endif  /* __P_MAPUTL__ */

/*----------------------------------------------------------------------------
 *
 * $Log: p_maputl.h,v $
 * Revision 1.4  1999/10/12 13:00:57  cphipps
 * Changed header to GPL, converted C++ comments to C
 *
 * Revision 1.3  1998/12/21 21:50:38  cphipps
 * Fix CONSTFUNC after m_fixed.h was modified
 *
 * Revision 1.2  1998/10/04 13:45:02  cphipps
 * Added const attribute to many functions and their parameters.
 *
 * Revision 1.1  1998/09/13 16:49:50  cphipps
 * Initial revision
 *
 * Revision 1.1  1998/05/03  22:19:26  killough
 * External declarations formerly in p_local.h
 *
 *
 *----------------------------------------------------------------------------*/
