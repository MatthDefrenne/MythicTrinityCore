#include "MythicManager.h"

MythicManager::~MythicManager()
{
}

MythicManager* MythicManager::instance()
{
    static MythicManager instance;
    return &instance;
}

void MythicManager::InitializeMythicDungeonBosses()
{

}

void MythicManager::InitializeMythicDungeons()
{

}

void MythicManager::InitializePlayerMythicKeys()
{

}

void MythicManager::InitializeRewardsDungeons()
{

}

void MythicManager::InitializeWeeklyAffixes()
{

}

void MythicManager::InitializeCreatureKillingCount()
{

}

void MythicManager::InitializeMultipliers()
{

}

void MythicManager::HandleChangeDungeonDifficulty(Player* _player)
{
    Group* group = _player->GetGroup();
    if (group)
    {
        if (group->IsLeader(_player->GetGUID()))
        {
            for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
            {
                Player* groupGuy = itr->GetSource();
                if (!groupGuy)
                    continue;

                if (!groupGuy->IsInWorld())
                {
                    _player->SendDungeonDifficulty(group != nullptr);
                    return;
                }

                if (groupGuy->GetGUID() == _player->GetGUID() ? groupGuy->GetMap()->IsDungeon() : groupGuy->GetMap()->IsNonRaidDungeon())
                {
                    _player->SendDungeonDifficulty(group != nullptr);
                    return;
                }
            }
            group->ResetInstances(INSTANCE_RESET_CHANGE_DIFFICULTY, false, _player);
            group->SetDungeonDifficulty(DUNGEON_DIFFICULTY_EPIC);
        }
    }
    else {
        _player->SetDungeonDifficulty(DUNGEON_DIFFICULTY_EPIC);
        _player->SendDungeonDifficulty(false);
        _player->ResetInstances(INSTANCE_RESET_CHANGE_DIFFICULTY, false);
    }
}

void MythicManager::SaveMythicKey(Player* player)
{

}

void MythicManager::Update(uint32 diff)
{
    for (auto mythic : MythicStore)
        mythic.second->Update(diff);
}

void MythicManager::AddMythicDungeon(ObjectGuid::LowType guid, Mythic* m)
{
    MythicStore[guid] = m;
}

void MythicManager::RemoveGroup(Group* group)
{
    MythicStore.erase(group->GetLowGUID());
}

bool MythicManager::IsThisMapIdAvailableForMythic(uint32 mapId)
{
    return false;
}

bool MythicManager::IsPlayerMeetingConditionsToStartMythic(Player* player)
{
    return false;
}

uint32 MythicManager::GetRandomMythicDungeonForPlayer(Player* player)
{
    return uint32();
}

uint32 MythicManager::GetRandomLoot(Player* player, uint32 dungeonId, uint32 level)
{

    std::vector<MythicReward> loots = {};

    auto itr = MythicDungeonLootStore.find(dungeonId);
    if (itr != MythicDungeonLootStore.end())
        for (auto item : itr->second)
            if ((item.classMask & player->GetClassMask()) && item.level == level)
                loots.push_back(item);

    uint32 rand = urand(0, loots.size() - 1);

    return loots[rand].itemId;
}

uint32 MythicManager::GetItemIdWithDungeonId(uint32 dungeonId)
{
    return uint32();
}

uint32 MythicManager::GetEnchantByMythicLevel(uint32 level)
{
    return uint32();
}


Mythic* MythicManager::GetMythicDungeonByGroupGuid(ObjectGuid::LowType guid)
{
    auto itr = MythicStore.find(guid);
    if (itr != MythicStore.end())
        return itr->second;

    return nullptr;
}

float MythicManager::GetKillCountByCreatureId(uint32 creatureId)
{
    float count = 1;
    auto itr = MythicKillCounterStore.find(creatureId);
    if (itr != MythicKillCounterStore.end())
        count =  itr->second;

    return count;
}

MythicDungeon MythicManager::GetMythicDungeonByDungeonId(uint32 dungeonId)
{
    return MythicDungeon();
}

MythicKey* MythicManager::GetCurrentPlayerMythicKey(Player* player)
{
    auto itr = MythicPlayerKeyStore.find(player->GetGUID());
    if (itr != MythicPlayerKeyStore.end()) {
        return &itr->second;
    }

    return nullptr;
}

std::vector<uint32> MythicManager::GetMythicBossesByDungeonId(uint32 dungeonId)
{
    return std::vector<uint32>();
}
