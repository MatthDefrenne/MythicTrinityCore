#pragma once

#define _MYTHICMGR_H

#include <list>
#include <map>
#include <mutex>
#include <unordered_map>

#include "Define.h"
#include "DatabaseEnvFwd.h"
#include "DBCEnums.h"
#include "ObjectDefines.h"
#include <ObjectGuid.h>
#include "Player.h"
#include "Group.h"
#include "Creature.h"
#include "ObjectAccessor.h"

class Mythic {

public:
    Mythic(Map* map, Group* group, uint32 dungeonId, uint32 level, Player* leader);
    ~Mythic();

    typedef std::map<uint32, bool> StateBossMythicContainer;
    void Prepare();
    void Update(uint32 diff);
    void PrepareCreature(Creature* creature);
private:


    void OnCompleteMythicDungeon(Player* player);
    void OnKillBoss(Player* player, Creature* killed);
    void OnKillCreature(Player* player, Creature* killed);
    void OnPlayerKilledByCreature();
    void OnPlayerRelease();
    bool MeetTheConditionsToCompleteTheDungeon();
    void GiveRewards();
    void UpdatePlayerKey(Player* player);
    void SaveMythicDungeon();
    // std::list<Group::MemberSlot> GetRandomMemberSlot();

    // Addon Messages;
    void SendStart(Player* player);
    void SendUpdateBossKill();
    void SendEnemyForces();

    void SetRespawnPosition(Position position) { LastestPosition = position; };

    Position LastestPosition;
    Group* m_Group;
    Player* Leader;
    uint32 DungeonId;
    uint32 TimeToComplete;
    Map* Dungeon;
    int StartTimer;
    bool Started;
    bool ChestDecrapeted;
    bool Done;
    uint32 ElapsedTime;
    float EnemyForces;
    uint32 Deaths;
    uint32 Level;
    StateBossMythicContainer StateBossMythicStore;
};
