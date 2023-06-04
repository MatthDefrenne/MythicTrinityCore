/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef TRINITY_MYTHICMANAGER_H
#define TRINITY_MYTHICMANAGER

#include <list>
#include <map>
#include <mutex>
#include <unordered_map>

#include "Define.h"
#include "DatabaseEnvFwd.h"
#include "DBCEnums.h"
#include "ObjectDefines.h"
#include <ObjectGuid.h>
#include "Mythic.h"
#include "Player.h"
#include "Group.h"
#include "Map.h"
#include "Mythic.h"

struct MythicDungeon {
    uint32 id;
    uint32 timeToComplete;
    uint32 mapId;
    float x;
    float y;
    float z;
    float o;
    bool enabled;
    uint32 itemId;
};

struct MythicMultiplier {
    float hp;
    float damage;
};

struct MythicBoss {
    uint32 dungeonId;
    uint32 order;
    uint32 creatureId;
};

struct MythicKey {
    uint32 dungeonId;
    uint32 level;
};

struct MythicReward {
    uint32 level;
    uint32 itemId;
    uint32 classMask;
};

class TC_GAME_API MythicManager
{
private:
    MythicManager() { };
    ~MythicManager();
public:


    static MythicManager* instance();
    typedef std::map<ObjectGuid::LowType, Mythic*> RunMythicDungeonContainer;
    typedef std::map<uint32, MythicMultiplier> MythicMutiplierContainer;
    typedef std::map<uint32, float> MythicKillCounterContainer;
    typedef std::vector<MythicBoss> MythicDungeonBossContainer;
    typedef std::vector<MythicDungeon> MythicDungeonContainer;
    typedef std::map<uint32, std::vector<MythicReward>> MythicRewardsContainer;
    typedef std::map<ObjectGuid::LowType, MythicKey> MythicPlayerKeyContainer;

    void InitializeMythicDungeonBosses();
    void InitializeMythicDungeons();
    void InitializePlayerMythicKeys();
    void InitializeRewardsDungeons();
    void InitializeWeeklyAffixes();
    void InitializeCreatureKillingCount();
    void InitializeMultipliers();
    void HandleChangeDungeonDifficulty(Player* player);
    void SaveMythicKey(Player* player);

    uint32 GetRandomMythicDungeonForPlayer(Player* player);
    uint32 GetRandomLoot(Player* player, uint32 dungeonId, uint32 level);
    uint32 GetItemIdWithDungeonId(uint32 dungeonId);
    uint32 GetEnchantByMythicLevel(uint32 level);

    void Update(uint32 diff);

    void AddMythicDungeon(ObjectGuid::LowType, Mythic* m);
    void RemoveGroup(Group* group);

    void onGroupDisband(Group* group);

    bool IsThisMapIdAvailableForMythic(uint32 mapId);
    bool IsPlayerMeetingConditionsToStartMythic(Player* player);
    Mythic* GetMythicDungeonByGroupGuid(ObjectGuid::LowType guid);

    float GetKillCountByCreatureId(uint32 creatureId);
    MythicMultiplier GetMultplierByLevel(uint32 level);
    MythicDungeon GetMythicDungeonByDungeonId(uint32 dungeonId);
    MythicKey* GetCurrentPlayerMythicKey(Player* player);
    std::vector<uint32> GetMythicBossesByDungeonId(uint32 dungeonId);

private:
    RunMythicDungeonContainer MythicStore;
    MythicMutiplierContainer MythicMultiplierStore;
    MythicKillCounterContainer MythicKillCounterStore;
    MythicDungeonBossContainer MythicDungeonBossStore;
    MythicDungeonContainer MythicDungeonStore;
    MythicPlayerKeyContainer MythicPlayerKeyStore;
    MythicRewardsContainer MythicDungeonLootStore;
};

#define sMythicMgr MythicManager::instance()
#endif
