/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ScriptData
SDName: Boss_Ragnaros
SD%Complete: 75
SDComment: Intro Dialog and event NYI
EndScriptData */

#include "../../sc_defines.h"


// Intro dialog is NYI

#define SPELL_HANDOFRAGNAROS        19780
#define SPELL_WRATHOFRAGNAROS       20566
#define SPELL_LAVABURST             21158

#define SPELL_MAGMABURST            20565       //Ranged attack

#define SPELL_SONSOFFLAME_DUMMY     21108       //Server side effect
#define SPELL_RAGSUBMERGE           21107       //Stealth aura
#define SPELL_RAGEMERGE             20568
#define SPELL_MELTWEAPON            21388
#define SPELL_ELEMENTALFIRE         20564
#define SPELL_ERRUPTION             17731

#define SAY_ARRIVAL_1       "TOO SOON! YOU HAVE AWAKENED ME TOO SOON, EXECUTUS! WHAT IS THE MEANING OF THIS INTRUSION?"
#define SAY_ARRIVAL_3       "FOOL! YOU ALLOWED THESE INSECTS TO RUN RAMPANT THROUGH THE HALLOWED CORE, AND NOW YOU LEAD THEM TO MY VERY LAIR? YOU HAVE FAILED ME, EXECUTUS! JUSTICE SHALL BE MET, INDEED!"
#define SAY_ARRIVAL_5       "NOW FOR YOU, INSECTS. BOLDLY YOU SAUGHT THE POWER OF RAGNAROS NOW YOU SHALL SEE IT FIRST HAND."
#define SAY_REINFORCEMENTS1 "COME FORTH, MY SERVANTS! DEFEND YOUR MASTER!"
#define SAY_REINFORCEMENTS2 "YOU CANNOT DEFEAT THE LIVING FLAME! COME YOU MINIONS OF FIRE! COME FORTH YOU CREATURES OF HATE! YOUR MASTER CALLS!"
#define SAY_HAND            "BY FIRE BE PURGED!"
#define SAY_WRATH           "TASTE THE FLAMES OF SULFURON!"
#define SAY_KILL            "DIE INSECT!"
#define SAY_MAGMABURST      "MY PATIENCE IS DWINDILING! COME NATS TO YOUR DEATH!"

#define SOUND_ARRIVAL_1         8043
#define SOUND_ARRIVAL_3         8044
#define SOUND_ARRIVAL_5         8045
#define SOUND_REINFORCEMENTS1   8049
#define SOUND_REINFORCEMENTS2   8050
#define SOUND_HAND              8046
#define SOUND_WRATH             8047
#define SOUND_KILL              8051
#define SOUND_MAGMABURST        8048

#define ADD_1X 848.740356
#define ADD_1Y -816.103455
#define ADD_1Z -229.74327
#define ADD_1O 2.615287

#define ADD_2X 852.560791
#define ADD_2Y -849.861511
#define ADD_2Z -228.560974
#define ADD_2O 2.836073  

#define ADD_3X 808.710632
#define ADD_3Y -852.845764
#define ADD_3Z -227.914963
#define ADD_3O 0.964207

#define ADD_4X 786.597107
#define ADD_4Y -821.132874
#define ADD_4Z -226.350128
#define ADD_4O 0.949377

#define ADD_5X 796.219116
#define ADD_5Y -800.948059
#define ADD_5Z -226.010361
#define ADD_5O 0.560603

#define ADD_6X 821.602539
#define ADD_6Y -782.744109
#define ADD_6Z -226.023575
#define ADD_6O 6.157440

#define ADD_7X 844.924744
#define ADD_7Y -769.453735
#define ADD_7Z -225.521698
#define ADD_7O 4.4539958

#define ADD_8X 839.823364
#define ADD_8Y -810.869385
#define ADD_8Z -229.683182
#define ADD_8O 4.693108

struct MANGOS_DLL_DECL boss_ragnarosAI : public ScriptedAI
{
    boss_ragnarosAI(Creature *c) : ScriptedAI(c) {Reset();}

    uint32 WrathOfRagnaros_Timer;
    uint32 HandOfRagnaros_Timer;
    uint32 LavaBurst_Timer;
    uint32 MagmaBurst_Timer;
    uint32 ElementalFire_Timer;
    uint32 Erruption_Timer;
    uint32 Submerge_Timer;
    uint32 Attack_Timer;
    Creature *Summoned;
    bool HasYelledMagmaBurst;
    bool HasSubmergedOnce;
    bool WasBanished; 
    bool InCombat;
    bool HasAura;

    void Reset()
    {
        WrathOfRagnaros_Timer = 30000;
        HandOfRagnaros_Timer = 25000;
        LavaBurst_Timer = 10000;
        MagmaBurst_Timer = 2000;
        Erruption_Timer = 15000;
        ElementalFire_Timer = 3000;
        Submerge_Timer = 180000;
        Attack_Timer = 90000;
        HasYelledMagmaBurst = false;
        HasSubmergedOnce = false;
        WasBanished = false; 
        InCombat = false;


        //m_creature->RemoveAllAuras();
        //m_creature->DeleteThreatList();
        //m_creature->CombatStop();
        //DoGoHome();

        m_creature->CastSpell(m_creature,SPELL_MELTWEAPON,true);
        HasAura = true;
    }

    void KilledUnit(Unit* victim)
    {
        if (rand()%5)
            return;

        DoYell(SAY_KILL, LANG_UNIVERSAL, NULL);
        DoPlaySoundToSet(m_creature, SOUND_KILL);
    }

    void AttackStart(Unit *who)
    {
        if (!who)
            return;

        if (who->isTargetableForAttack() && who!= m_creature)
        {
            //Begin ranged attack because Ragnaros is rooted at all times
            DoStartRangedAttack(who);

            //Say our dialog on initial aggro
            if (!InCombat)
            {
                DoYell(SAY_ARRIVAL_5,LANG_UNIVERSAL,NULL);
                DoPlaySoundToSet(m_creature,SOUND_ARRIVAL_5);
                InCombat = true;
            }
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!who || m_creature->getVictim())
            return;

        if (who->isTargetableForAttack() && who->isInAccessablePlaceFor(m_creature) && m_creature->IsHostileTo(who))
        {
            float attackRadius = m_creature->GetAttackDistance(who);
            if (m_creature->IsWithinDistInMap(who, attackRadius) && m_creature->GetDistanceZ(who) <= CREATURE_Z_ATTACK_RANGE && m_creature->IsWithinLOSInMap(who))
            {
                if(who->HasStealthAura())
                    who->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);

                if (!HasAura)
                {
                    m_creature->CastSpell(m_creature,SPELL_MELTWEAPON,true);
                    HasAura = true;
                }


                //Begin ranged attack because Ragnaros is rooted at all times
                DoStartRangedAttack(who);

                //Say our dialog on initial aggro
                if (!InCombat)
                {
                    DoYell(SAY_ARRIVAL_5,LANG_UNIVERSAL,NULL);
                    DoPlaySoundToSet(m_creature,SOUND_ARRIVAL_5);
                    InCombat = true;
                }
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (WasBanished && Attack_Timer < diff)
        {
            //Become unbanished again 
            m_creature->setFaction(14);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            DoCast(m_creature,SPELL_RAGEMERGE);
            WasBanished = false;
        } else if (WasBanished)
        {
            Attack_Timer -= diff;
            //Do nothing while banished
            return;
        }

        //Return since we have no target
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

        //WrathOfRagnaros_Timer
        if (WrathOfRagnaros_Timer < diff)
        {
            //Cast
            DoCast(m_creature->getVictim(),SPELL_WRATHOFRAGNAROS);

            if (rand()%2 == 0)
            {
                //Say our dialog
                DoYell(SAY_WRATH,LANG_UNIVERSAL,NULL);
                DoPlaySoundToSet(m_creature,SOUND_WRATH);
            }

            //60 seconds until we should cast this agian
            WrathOfRagnaros_Timer = 30000;
        }else WrathOfRagnaros_Timer -= diff;

        //HandOfRagnaros_Timer
        if (HandOfRagnaros_Timer < diff)
        {
            //Cast
            DoCast(m_creature,SPELL_HANDOFRAGNAROS);

            if (rand()%2==0)
            {
                //Say our dialog
                DoYell(SAY_HAND,LANG_UNIVERSAL,NULL);
                DoPlaySoundToSet(m_creature,SOUND_HAND);
            }

            //60 seconds until we should cast this agian
            HandOfRagnaros_Timer = 25000;
        }else HandOfRagnaros_Timer -= diff;

        //LavaBurst_Timer
        if (LavaBurst_Timer < diff)
        {
            //Cast
            DoCast(m_creature->getVictim(),SPELL_LAVABURST);

            //10 seconds until we should cast this agian
            LavaBurst_Timer = 10000;
        }else LavaBurst_Timer -= diff;

        //Erruption_Timer
        if (LavaBurst_Timer < diff)
        {
            //Cast
            DoCast(m_creature->getVictim(),SPELL_ERRUPTION);

            //10 seconds until we should cast this agian
            Erruption_Timer = 20000 + rand()%25000;
        }else Erruption_Timer -= diff;

        //ElementalFire_Timer
        if (ElementalFire_Timer < diff)
        {
            //Cast
            DoCast(m_creature->getVictim(),SPELL_ELEMENTALFIRE);

            //10 seconds until we should cast this agian
            ElementalFire_Timer = 10000 + rand()%4000;
        }else ElementalFire_Timer -= diff;

        //Submerge_Timer
        if (!WasBanished && Submerge_Timer < diff)
        {
            //Creature spawning and ragnaros becomming unattackable
            //is not very well supported in the core
            //so added normaly spawning and banish workaround and attack again after 90 secs.

            m_creature->InterruptSpell(CURRENT_GENERIC_SPELL);
            //Root self
            DoCast(m_creature,23973);
            m_creature->setFaction(35);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->HandleEmoteCommand(EMOTE_ONESHOT_SUBMERGE);

            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM,0);
            
            

            if (!HasSubmergedOnce)
            {
                DoYell(SAY_REINFORCEMENTS1,LANG_UNIVERSAL,NULL);
                DoPlaySoundToSet(m_creature,SOUND_REINFORCEMENTS1);
                
                // summon 10 elementals
                Unit* target = NULL;
                for(int i = 0; i < 9;i++)
                {
                    target = SelectUnit(SELECT_TARGET_RANDOM,0);
                    Summoned = m_creature->SummonCreature(12143,target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(),0,TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN,900000);
                    ((CreatureAI*)Summoned->AI())->AttackStart(target);
               }

            HasSubmergedOnce = true;
            WasBanished = true;
            DoCast(m_creature,SPELL_RAGSUBMERGE);
            Attack_Timer = 90000;

            }else
            {
                //Say our dialog
                DoYell(SAY_REINFORCEMENTS2,LANG_UNIVERSAL,NULL);
                DoPlaySoundToSet(m_creature,SOUND_REINFORCEMENTS2);
                
                Unit* target = NULL;
                for(int i = 0; i < 9;i++)
                {
                    target = SelectUnit(SELECT_TARGET_RANDOM,0);
                    Summoned = m_creature->SummonCreature(12143,target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(),0,TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN,900000);
                    ((CreatureAI*)Summoned->AI())->AttackStart(target);
                }

            WasBanished = true;
            DoCast(m_creature,SPELL_RAGSUBMERGE);
            Attack_Timer = 90000;
            }

            //3 minutes until we should cast this agian
            Submerge_Timer = 180000;
        }else Submerge_Timer -= diff;

        //If we are within range melee the target
        if( m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
        {
            //Make sure our attack is ready and we arn't currently casting
            if( m_creature->isAttackReady() && !m_creature->IsNonMeleeSpellCasted(false))
            {
                m_creature->AttackerStateUpdate(m_creature->getVictim());
                m_creature->resetAttackTimer();
            }
        }else
        {
            //MagmaBurst_Timer
            if (MagmaBurst_Timer < diff)
            {
                //Cast
                DoCast(m_creature->getVictim(),SPELL_MAGMABURST);

                if (!HasYelledMagmaBurst)
                {
                    //Say our dialog
                    DoYell(SAY_MAGMABURST,LANG_UNIVERSAL,NULL);
                    DoPlaySoundToSet(m_creature,SOUND_MAGMABURST);
                    HasYelledMagmaBurst = true;
                }

                //3 seconds until we should cast this agian
                MagmaBurst_Timer = 2500;
            }else MagmaBurst_Timer -= diff;
        }
    }
}; 
CreatureAI* GetAI_boss_ragnaros(Creature *_Creature)
{
    return new boss_ragnarosAI (_Creature);
}


void AddSC_boss_ragnaros()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="boss_ragnaros";
    newscript->GetAI = GetAI_boss_ragnaros;
    m_scripts[nrscripts++] = newscript;
}
