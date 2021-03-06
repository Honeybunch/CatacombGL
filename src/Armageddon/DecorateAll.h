// Copyright (C) 2018 Arno Ansems
// 
// This program is free software: you can redistribute it and/or modify 
// it under the terms of the GNU General Public License as published by 
// the Free Software Foundation, either version 3 of the License, or 
// (at your option) any later version. 
// 
// This program is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
// GNU General Public License for more details. 
// 
// You should have received a copy of the GNU General Public License 
// along with this program.  If not, see http://www.gnu.org/licenses/ 
#pragma once

#include "DecorateMisc.h"
#include "DecorateBonus.h"
#include "DecorateMonsters.h"
#include "DecorateProjectiles.h"

const std::map<uint16_t, const DecorateActor> decorateArmageddonAll =
{
    std::make_pair(actorIdTomb1, decorateTomb1),
    std::make_pair(actorIdTomb2, decorateTomb2),
    std::make_pair(actorIdTomb3, decorateTomb3),
    std::make_pair(actorIdColumn, decorateColumn),
    std::make_pair(actorIdSulphurGas, decorateSulphurGas),
    std::make_pair(actorIdFirePot, decorateFirePot),
    std::make_pair(actorIdFountain, decorateFountain),
    std::make_pair(actorIdPlayer, decoratePlayer),
    std::make_pair(actorIdBonusExplosion, decorateExplosion),
    std::make_pair(actorIdBonusBolt, decorateBolt),
    std::make_pair(actorIdBonusNuke, decorateNuke),
    std::make_pair(actorIdBonusPotion, decoratePotion),
    std::make_pair(actorIdBonusChest, decorateChest),
    std::make_pair(actorIdBonusWaterChest, decorateWaterChest),
    std::make_pair(actorIdBonusFreezeTime, decorateFreezeTime),
    std::make_pair(actorIdBonusKeyRed, decorateKeyRed),
    std::make_pair(actorIdBonusKeyYellow, decorateKeyYellow),
    std::make_pair(actorIdBonusKeyGreen, decorateKeyGreen),
    std::make_pair(actorIdBonusKeyBlue, decorateKeyBlue),
    std::make_pair(actorIdBonusGemRed, decorateGemRed),
    std::make_pair(actorIdBonusGemYellow, decorateGemYellow),
    std::make_pair(actorIdBonusGemGreen, decorateGemGreen),
    std::make_pair(actorIdBonusGemBlue, decorateGemBlue),
    std::make_pair(actorIdBonusGemPurple, decorateGemPurple),
    std::make_pair(actorIdMonsterZombie, decorateZombie),
    std::make_pair(actorIdMonsterTree, decorateTree),
    std::make_pair(actorIdMonsterBunny, decorateBunny),
    std::make_pair(actorIdMonsterBat, decorateBat),
    std::make_pair(actorIdProjectilePlayerShot, decoratePlayerShot),
    std::make_pair(actorIdProjectilePlayerBigShot, decoratePlayerBigShot),
    std::make_pair(actorIdProjectileNemesisShot, decorateNemesisShot)
};


