/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef SC_GOSSIP_H
#define SC_GOSSIP_H

#include "Player.h"
#include "GossipDef.h"
#include "QuestDef.h"

// Gossip Item Text
#define GOSSIP_TEXT_BROWSE_GOODS        "Je voudrais examiner vos marchandises."
#define GOSSIP_TEXT_TRAIN               "Formez-moi!"

#define GOSSIP_TEXT_BANK                "La banque"
#define GOSSIP_TEXT_IRONFORGE_BANK      "Banque de Forgefer"
#define GOSSIP_TEXT_STORMWIND_BANK      "Banque de Hurlevent"
#define GOSSIP_TEXT_WINDRIDER           "Le maître des coursiers du vent"
#define GOSSIP_TEXT_GRYPHON             "Le maître des griffons"
#define GOSSIP_TEXT_BATHANDLER          "Éleveur de chauve-souris"
#define GOSSIP_TEXT_HIPPOGRYPH          "Le maître des hippogriffes"
#define GOSSIP_TEXT_ZEPPLINMASTER       "Le maître des zeppelins"
#define GOSSIP_TEXT_DEEPRUNTRAM         "Le tram des profondeurs"
#define GOSSIP_TEXT_FERRY               "Bac de Rut'theran"
#define GOSSIP_TEXT_FLIGHTMASTER        "Le maître de vol"
#define GOSSIP_TEXT_AUCTIONHOUSE        "Hôtel des ventes"
#define GOSSIP_TEXT_GUILDMASTER         "Le maître des Guildes"
#define GOSSIP_TEXT_INN                 "L'auberge"
#define GOSSIP_TEXT_MAILBOX             "Boite aux lettres"
#define GOSSIP_TEXT_STABLEMASTER        "Maître des écuries"
#define GOSSIP_TEXT_WEAPONMASTER        "Maître d'armes"
#define GOSSIP_TEXT_OFFICERS            "Mess des Officiers"
#define GOSSIP_TEXT_BATTLEMASTER        "Maître de guerre"
#define GOSSIP_TEXT_BARBER              "Salon de Coiffure"
#define GOSSIP_TEXT_CLASSTRAINER        "Maître de classe"
#define GOSSIP_TEXT_PROFTRAINER         "Maître de profession"
#define GOSSIP_TEXT_LEXICON             "Lexique de pouvoir"

#define GOSSIP_TEXT_ALTERACVALLEY       "Vallée d'Alterac"
#define GOSSIP_TEXT_ARATHIBASIN         "Bassin d'Arathi"
#define GOSSIP_TEXT_WARSONGULCH         "Goulet des Chanteguerres"
#define GOSSIP_TEXT_ARENA               "Aréne"
#define GOSSIP_TEXT_EYEOFTHESTORM       "L'Œil du cyclone"
#define GOSSIP_TEXT_STRANDOFANCIENT     "Rivage des Anciens"

#define GOSSIP_TEXT_DEATH_KNIGHT        "Chevalier de la mort"
#define GOSSIP_TEXT_DRUID               "Druide"
#define GOSSIP_TEXT_HUNTER              "Chasseur"
#define GOSSIP_TEXT_PRIEST              "Prêtre"
#define GOSSIP_TEXT_ROGUE               "Voleur"
#define GOSSIP_TEXT_WARRIOR             "Guerrier"
#define GOSSIP_TEXT_PALADIN             "Paladin"
#define GOSSIP_TEXT_SHAMAN              "Chaman"
#define GOSSIP_TEXT_MAGE                "Mage"
#define GOSSIP_TEXT_WARLOCK             "Démoniste"

#define GOSSIP_TEXT_ALCHEMY             "Alchimie"
#define GOSSIP_TEXT_BLACKSMITHING       "Forge"
#define GOSSIP_TEXT_COOKING             "Cuisine"
#define GOSSIP_TEXT_ENCHANTING          "Enchantement"
#define GOSSIP_TEXT_ENGINEERING         "Ingénierie"
#define GOSSIP_TEXT_FIRSTAID            "Secourisme"
#define GOSSIP_TEXT_HERBALISM           "Herboristerie"
#define GOSSIP_TEXT_INSCRIPTION         "Calligraphie"
#define GOSSIP_TEXT_JEWELCRAFTING       "Joaillerie"
#define GOSSIP_TEXT_LEATHERWORKING      "Travail du cuir"
#define GOSSIP_TEXT_TAILORING           "Tailleurs"
#define GOSSIP_TEXT_MINING              "Minage"
#define GOSSIP_TEXT_FISHING             "Pêche"
#define GOSSIP_TEXT_SKINNING            "Couture"

enum
{
    // Skill defines
    TRADESKILL_ALCHEMY             = 1,
    TRADESKILL_BLACKSMITHING       = 2,
    TRADESKILL_COOKING             = 3,
    TRADESKILL_ENCHANTING          = 4,
    TRADESKILL_ENGINEERING         = 5,
    TRADESKILL_FIRSTAID            = 6,
    TRADESKILL_HERBALISM           = 7,
    TRADESKILL_LEATHERWORKING      = 8,
    TRADESKILL_POISONS             = 9,
    TRADESKILL_TAILORING           = 10,
    TRADESKILL_MINING              = 11,
    TRADESKILL_FISHING             = 12,
    TRADESKILL_SKINNING            = 13,
    TRADESKILL_JEWLCRAFTING        = 14,
    TRADESKILL_INSCRIPTION         = 15,

    TRADESKILL_LEVEL_NONE          = 0,
    TRADESKILL_LEVEL_APPRENTICE    = 1,
    TRADESKILL_LEVEL_JOURNEYMAN    = 2,
    TRADESKILL_LEVEL_EXPERT        = 3,
    TRADESKILL_LEVEL_ARTISAN       = 4,
    TRADESKILL_LEVEL_MASTER        = 5,
    TRADESKILL_LEVEL_GRAND_MASTER  = 6,

    // Gossip defines
    GOSSIP_ACTION_TRADE            = 1,
    GOSSIP_ACTION_TRAIN            = 2,
    GOSSIP_ACTION_TAXI             = 3,
    GOSSIP_ACTION_GUILD            = 4,
    GOSSIP_ACTION_BATTLE           = 5,
    GOSSIP_ACTION_BANK             = 6,
    GOSSIP_ACTION_INN              = 7,
    GOSSIP_ACTION_HEAL             = 8,
    GOSSIP_ACTION_TABARD           = 9,
    GOSSIP_ACTION_AUCTION          = 10,
    GOSSIP_ACTION_INN_INFO         = 11,
    GOSSIP_ACTION_UNLEARN          = 12,
    GOSSIP_ACTION_INFO_DEF         = 1000,

    GOSSIP_SENDER_MAIN             = 1,
    GOSSIP_SENDER_INN_INFO         = 2,
    GOSSIP_SENDER_INFO             = 3,
    GOSSIP_SENDER_SEC_PROFTRAIN    = 4,
    GOSSIP_SENDER_SEC_CLASSTRAIN   = 5,
    GOSSIP_SENDER_SEC_BATTLEINFO   = 6,
    GOSSIP_SENDER_SEC_BANK         = 7,
    GOSSIP_SENDER_SEC_INN          = 8,
    GOSSIP_SENDER_SEC_MAILBOX      = 9,
    GOSSIP_SENDER_SEC_STABLEMASTER = 10
};

extern uint32 GetSkillLevel(Player* pPlayer, uint32 uiSkill);

// Defined fuctions to use with player.

// This fuction add's a menu item,
// Icon Id
// Text
// Sender(this is to identify the current Menu with this item)
// Option id (identifies this Menu Item)
// Text to be displayed in pop up box
// Money value in pop up box
// Coded
#define ADD_GOSSIP_ITEM(uiIcon, chrText, uiSender, uiOptionId)   PlayerTalkClass->GetGossipMenu().AddMenuItem(uiIcon, chrText, uiSender, uiOptionId, "", 0)
#define ADD_GOSSIP_ITEM_ID(uiIcon, iTextId, uiSender, uiOptionId)   PlayerTalkClass->GetGossipMenu().AddMenuItem(uiIcon, iTextId, uiSender, uiOptionId, 0, 0)
#define ADD_GOSSIP_ITEM_EXTENDED(uiIcon, chrText, uiSender, uiOptionId, chrBoxMessage, uiBoxMoney, bCode)   PlayerTalkClass->GetGossipMenu().AddMenuItem(uiIcon, chrText, uiSender, uiOptionId, chrBoxMessage, uiBoxMoney, bCode)

// This fuction Sends the current menu to show to client, uiTextId - NPCTEXTID(uint32) , uiGuid - npc guid(uint64)
#define SEND_GOSSIP_MENU(uiTextId, uiGuid)      PlayerTalkClass->SendGossipMenu(uiTextId, uiGuid)

// This fuction shows POI(point of interest) to client.
// a - position X
// b - position Y
// c - Icon Id
// d - Flags
// e - Data
// f - Location Name
#define SEND_POI(a, b, c, d, e, f)      PlayerTalkClass->SendPointOfInterest(a, b, c, d, e, f)

// Closes the Menu
#define CLOSE_GOSSIP_MENU()        PlayerTalkClass->CloseGossip()

// Fuction to tell to client the details
// a - quest object
// b - npc guid(uint64)
// c - Activate accept(bool)
#define SEND_QUEST_DETAILS(a, b, c)  PlayerTalkClass->SendQuestDetails(a, b, c)

// Fuction to tell to client the requested items to complete quest
// a - quest object
// b - npc guid(uint64)
// c - Iscompletable(bool)
// d - close at cancel(bool) - in case single incomplite ques
#define SEND_REQUESTEDITEMS(a, b, c, d) PlayerTalkClass->SendRequestedItems(a, b, c, d)

// Fuctions to send NPC lists, a - is always the npc guid(uint64)
#define SEND_VENDORLIST(a)         GetSession()->SendListInventory(a)
#define SEND_TRAINERLIST(a)        GetSession()->SendTrainerList(a)
#define SEND_BANKERLIST(a)         GetSession()->SendShowBank(a)
#define SEND_TABARDLIST(a)         GetSession()->SendTabardVendorActivate(a)
#define SEND_TAXILIST(a)           GetSession()->SendTaxiStatus(a)

// Function to send the Auction List, a - npc guid(uint64), b - pointer to npc(Creature*)
#define SEND_AUCTIONLIST(a, b)     GetSession()->SendAuctionHello(a, b)

// Ressurect's the player if is dead.
#define SEND_SPRESURRECT()         GetSession()->SendSpiritResurrect()
// -----------------------------------

// defined fuctions to use with Creature

#define QUEST_DIALOG_STATUS(a, b, c)   GetSession()->getDialogStatus(a, b, c)
#endif
