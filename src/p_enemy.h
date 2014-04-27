/* Emacs style mode select   -*- C++ -*- 
 *-----------------------------------------------------------------------------
 *
 * $Id: p_enemy.h,v 1.2 1999/10/12 13:01:15 cphipps Exp $
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
 *      Enemy thinking, AI.
 *      Action Pointer Functions
 *      that are associated with states/frames.
 *
 *-----------------------------------------------------------------------------*/

#ifndef __P_ENEMY__
#define __P_ENEMY__

#include "p_mobj.h"

void P_NoiseAlert (mobj_t *target, mobj_t *emmiter);
void P_SpawnBrainTargets(void); /* killough 3/26/98: spawn icon landings */

extern struct brain_s {         /* killough 3/26/98: global state of boss brain */
  int easy, targeton;
} brain;

void A_KeenDie(mobj_t* mo);
void A_Look(mobj_t *actor);
void A_Chase(mobj_t *actor);
void A_FaceTarget(mobj_t *actor);
void A_PosAttack(mobj_t *actor);
void A_SPosAttack(mobj_t* actor);
void A_CPosAttack(mobj_t *actor);
void A_CPosRefire(mobj_t *actor);
void A_SpidRefire(mobj_t* actor);
void A_BspiAttack(mobj_t *actor);
void A_TroopAttack(mobj_t *actor);
void A_SargAttack(mobj_t *actor);
void A_HeadAttack(mobj_t *actor);
void A_CyberAttack(mobj_t *actor);
void A_BruisAttack(mobj_t *actor);
void A_SkelMissile(mobj_t *actor);
void A_Tracer(mobj_t *actor);
void A_SkelWhoosh(mobj_t *actor);
void A_SkelFist(mobj_t *actor);
void A_VileChase(mobj_t* actor);
void A_VileStart(mobj_t *actor);
void A_StartFire(mobj_t *actor);
void A_FireCrackle(mobj_t* actor);
void A_Fire(mobj_t *actor);
void A_VileTarget(mobj_t *actor);
void A_VileAttack(mobj_t *actor);
void A_FatRaise(mobj_t *actor);
void A_FatAttack1(mobj_t *actor);
void A_FatAttack2(mobj_t *actor);
void A_FatAttack3(mobj_t *actor);
void A_SkullAttack(mobj_t *actor);
void A_PainAttack(mobj_t *actor);
void A_PainDie(mobj_t *actor);
void A_Scream(mobj_t *actor);
void A_XScream(mobj_t *actor);
void A_Pain(mobj_t *actor);
void A_Fall(mobj_t *actor);
void A_Explode(mobj_t *thingy);
void A_BossDeath(mobj_t *mo);
void A_Hoof (mobj_t* mo);
void A_Metal(mobj_t *mo);
void A_BabyMetal(mobj_t *mo);
void A_OpenShotgun2(player_t *player, pspdef_t *psp);
void A_LoadShotgun2(player_t *player, pspdef_t *psp);
void A_ReFire(player_t *player, pspdef_t *psp);
void A_CloseShotgun2(player_t *player, pspdef_t *psp);
void A_BrainAwake(mobj_t *mo);
void A_BrainPain(mobj_t *mo);
void A_BrainScream(mobj_t *mo);
void A_BrainExplode(mobj_t *mo);
void A_BrainDie(mobj_t *mo);
void A_BrainSpit(mobj_t *mo);
void A_SpawnSound(mobj_t *mo);
void A_SpawnFly(mobj_t *mo);
void A_PlayerScream(mobj_t *mo);
void A_Die(mobj_t *actor);
void A_Detonate(mobj_t *mo);
void A_Mushroom(mobj_t *actor);
void A_Spawn(mobj_t *mo);
void A_Turn(mobj_t *mo);
void A_Face(mobj_t *mo);
void A_Scratch(mobj_t *mo);
void A_PlaySound(mobj_t *mo);
void A_RandomJump(mobj_t *mo);
void A_LineEffect(mobj_t *mo);

#endif // __P_ENEMY__

/*----------------------------------------------------------------------------
 *
 * $Log: p_enemy.h,v $
 * Revision 1.2  1999/10/12 13:01:15  cphipps
 * Changed header to GPL
 *
 * Revision 1.1  1998/09/13 16:49:50  cphipps
 * Initial revision
 *
 * Revision 1.1  1998/05/03  22:29:32  killough
 * External declarations formerly in p_local.h
 *
 *
 *----------------------------------------------------------------------------*/
