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

#include "GameAbyss.h"
#include "GameMapsAbyss.h"
#include "IntroViewAbyss.h"
#include "..\Engine\IRenderer.h"

// Decorate
#include "DecorateAll.h"

static const std::string AbyssV113Name = "Catacomb Abyss v1.13 Shareware";
static const std::string AbyssV124Name = "Catacomb Abyss v1.24 Registered";

GameAbyss::GameAbyss(const uint8_t gameId, const std::string gamePath, IRenderer& renderer) :
    m_gameId (gameId),
    m_gamePath (gamePath),
    m_renderer (renderer),
    m_zombie_base_delay (0),
    m_introView (NULL)
{
    m_gameMaps = NULL;
    m_egaGraph = NULL;
    m_audioRepository = NULL;
    m_audioPlayer = NULL;
}

GameAbyss::~GameAbyss()
{
    if (m_gameMaps != NULL)
    {
        delete m_gameMaps;
    }
    if (m_egaGraph != NULL)
    {
        delete m_egaGraph;
    }
    if (m_audioRepository != NULL)
    {
        delete m_audioRepository;
    }
    if (m_audioPlayer != NULL)
    {
        delete m_audioPlayer;
    }
    if (m_introView != NULL)
    {
        delete m_introView;
    }
}

void GameAbyss::SpawnActors(Level* level, const DifficultyLevel difficultyLevel)
{
    Actor** actors = level->GetBlockingActors();
    Actor* const playerState = level->GetPlayerActor();

    for (uint16_t y = 0; y < level->GetLevelHeight(); y++)
    {
        for (uint16_t x = 0; x < level->GetLevelWidth(); x++)
        {
            const uint16_t tile = level->GetFloorTile(x, y);
            switch (tile)
            {
            case 1:
            case 2:
            case 3:
            case 4:
                {
                    playerState->SetX(x + 0.5f);
                    playerState->SetY(y + 0.5f);
                    playerState->SetAngle((tile - 1) * 90.0f);
                    break;
                }
            case 5:
                {
                    Actor* bonusActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateBolt);
                    actors[(y * level->GetLevelWidth()) + x] = bonusActor;
                    break;
                }
            case 6:
                {
                    Actor* bonusActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateNuke);
                    actors[(y * level->GetLevelWidth()) + x] = bonusActor;
                    break;
                }
            case 7:

                {
                    Actor* bonusActor = new Actor(x + 0.5f, y + 0.5f, 0, decoratePotion);
                    actors[(y * level->GetLevelWidth()) + x] = bonusActor;
                    break;
                }
            case 8:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateKeyRed);
                break;
            case 9:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateKeyYellow);
                break;
            case 10:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateKeyGreen);
                break;
            case 11:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateKeyBlue);
                break;
            case 12:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateScroll1);
                break;
            case 13:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateScroll2);
                break;
            case 14:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateScroll3);
                break;
            case 15:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateScroll4);
                break;
            case 16:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateScroll5);
                break;
            case 17:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateScroll6);
                break;
            case 18:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateScroll7);
                break;
            case 19:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateScroll8);
                break;
            case 29:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateKeyRed2);;
                break;
            case 21:
                {
                    Actor* bonusActorChest = level->IsWaterLevel() ? new Actor(x + 0.5f, y + 0.5f, 0, decorateWaterChest) : new Actor(x + 0.5f, y + 0.5f, 0, decorateChest);
                    actors[(y * level->GetLevelWidth()) + x] = bonusActorChest;
                    break;
                }
            case 20:
            case 24:
            case 30:
                {
                    Actor* redDemonActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateRedDemon);
                    actors[(y * level->GetLevelWidth()) + x] = redDemonActor;
                    break;
                }
            case 43:
                if (difficultyLevel < Hard)
                {
                    break;
                }
            case 38:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 25:
                {
                    Actor* batActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateBat);
                    actors[(y * level->GetLevelWidth()) + x] = batActor;
                    break;
                }
            case 44:
                if (difficultyLevel < Hard)
                {
                    break;
                }
            case 39:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 26:
                {
                    Actor* demonActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateDemon);
                    actors[(y * level->GetLevelWidth()) + x] = demonActor;
                    break;
                }
            case 41:
                if (difficultyLevel < Hard)
                {
                    break;
                }
            case 36:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 22:
                {
                    Actor* trollActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateTroll);
                    actors[(y * level->GetLevelWidth()) + x] = trollActor;
                    break;
                }
            case 42:
                if (difficultyLevel < Hard)
                {
                    break;
                }
            case 37:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 23:
                {
                    Actor* orcActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateOrc);
                    actors[(y * level->GetLevelWidth()) + x] = orcActor;
                    break;
                }
            case 65:
                if (difficultyLevel < Hard)
                {
                    break;
                }
            case 64:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 63:
                {
                    const int16_t wetManDelay = (5*60)+ rand() % (5*60);
                    Actor* wetManActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateWetMan);
                    wetManActor->SetTemp2(wetManDelay);
                    actors[(y * level->GetLevelWidth()) + x] = wetManActor;
                    break;
                }
            case 68:
                if (difficultyLevel < Hard)
                {
                    break;
                }
            case 67:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 66:
                {
                    Actor*eyeActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateEye);
                    actors[(y * level->GetLevelWidth()) + x] = eyeActor;
                    break;
                }
            case 45:
                if (difficultyLevel < Hard)
                {
                    break;
                }
            case 40:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 27:
                {
                    Actor* mageActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateMage);
                    actors[(y * level->GetLevelWidth()) + x] = mageActor;
                    break;
                }
            case 28:
                {
                    Actor* nemesisActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateNemesis);
                    actors[(y * level->GetLevelWidth()) + x] = nemesisActor;
                    break;
                }
            case 31:
                {
                    actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateWarpPortal1);
                    break;
                }
            case 32:
                {
                    actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateWarpPortal2);
                    break;
                }
            case 33:
                {
                    actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateWarpPortal3);
                    break;
                }
            case 34:
                {
                    actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateWarpPortal4);
                    break;
                }
            case 35:
                {
                    actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateWarpPortal5);
                    break;
                }
            case 54:
                {
                    actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateWarpPit);
                    break;
                }
            case 46:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateTomb1);
                break;
            case 47:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateTomb2);
                break;
            case 48:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateTomb3);
                break;
            case 51:
                if (difficultyLevel < Hard)
                {
                    break;
                }
            case 50:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 49:
                {
                    int16_t spook_delay;
                    unsigned int tile = level->GetFloorTile(x, y + 1);
                    if (tile != 0)
                        spook_delay = (tile>>8)*30;
                    else
                    {
                        spook_delay = (2*60)+ rand() % (5*60);
                    }
                    Actor* spookActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateSpook);
                    spookActor->SetTemp2(spook_delay);
                    actors[(y * level->GetLevelWidth()) + x] = spookActor;
                    break;
                }
            case 53:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 52:
                {

                    int16_t zombie_delay;
                    unsigned int tile = level->GetFloorTile(x, y + 1);
                    if (tile != 0)
                        zombie_delay = (tile>>8)*30;
                    else
                    {
                        const int16_t current_zombie_delay = (2*60)+ rand() % (4*60);
                        zombie_delay = m_zombie_base_delay+current_zombie_delay;
                        m_zombie_base_delay += current_zombie_delay;
                        if (m_zombie_base_delay > 8*60)
                            m_zombie_base_delay = 0;
                    }
                    Actor* zombieActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateZombie);
                    zombieActor->SetTemp2(zombie_delay);
                    actors[(y * level->GetLevelWidth()) + x] = zombieActor;
                    break;
                }
            case 56:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 55:
                {
                    Actor* skeletonActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateSkeleton);
                    actors[(y * level->GetLevelWidth()) + x] = skeletonActor;
                    break;
                }
            case 57:
                {
                    Actor* freezeTimeActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateFreezeTime);
                    actors[(y * level->GetLevelWidth()) + x] = freezeTimeActor;
                    break;
                }
            case 58:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateGemRed);
                break;
            case 59:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateGemGreen);
                break;
            case 60:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateGemBlue);
                break;
            case 61:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateGemYellow);
                break;
            case 62:
                actors[(y * level->GetLevelWidth()) + x] = new Actor(x + 0.5f, y + 0.5f, 0, decorateGemPurple);
                break;
            case 71:
                if (difficultyLevel < Hard)
                {
                    break;
                }
            case 70:
                if (difficultyLevel < Normal)
                {
                    break;
                }
            case 69:
                {
                    int16_t xofs[] = {0,0,-1,+1};
                    int16_t yofs[] = {-1,+1,0,0};
                    uint16_t floorTile = 0;
                    for (int16_t loop=0; loop<4; loop++)
                    {
                        const uint16_t wallTile = level->GetWallTile(x + xofs[loop], y + yofs[loop]);
                        if (wallTile == 6 || wallTile == 7 || wallTile == 8 || wallTile == 41 || wallTile == 42 || wallTile == 43 || wallTile == 44)
                        {
                            floorTile = level->GetFloorTile(x + xofs[loop], y + yofs[loop]);
                        }

                    }
                    int16_t zombie_delay;
                    if (floorTile > 0)
                    {
                        zombie_delay = (floorTile>>8)*30;
                    }
                    else
                    {
                        const int16_t current_zombie_delay = (2*60)+ rand() % (4*60);
                        zombie_delay = m_zombie_base_delay+current_zombie_delay;
                        m_zombie_base_delay += current_zombie_delay;
                        if (m_zombie_base_delay > 8*60)
                            m_zombie_base_delay = 0;
                    }
                    Actor* wallSkeletonActor = new Actor(x + 0.5f, y + 0.5f, 0, decorateWallSkeleton);
                    wallSkeletonActor->SetTemp2(zombie_delay);
                    actors[(y * level->GetLevelWidth()) + x] = wallSkeletonActor;
                    break;
                }
            default:
                break;
            }
        }
    }
}

void GameAbyss::DrawStatusBar(const int16_t health, const std::string& locationMessage, const PlayerInventory& playerInventory)
{
    m_renderer.Render2DPicture(GetEgaGraph()->GetPicture(egaGraphicsAbyss::STATUSPIC), 0, 120);
    
    DrawHealth(health);
    DrawScrolls(playerInventory);
    DrawKeys(playerInventory);
    DrawBonus(playerInventory);
    DrawGems(playerInventory);

    m_renderer.RenderTextCentered(locationMessage.c_str(), GetEgaGraph()->GetFont(3), EgaBrightYellow, 160, 121); 
}

void GameAbyss::DrawHealth(const int16_t health)
{
    const uint16_t percentage = (uint16_t) health;

    m_renderer.RenderNumber(percentage, GetEgaGraph()->GetFont(3), 3, EgaBrightYellow, 74, 176);

    uint16_t picnum;
    if (percentage > 75)
    {
        picnum = FACE1PIC;
    }
    else if (percentage > 50)
    {
        picnum = FACE2PIC;
    }
    else if (percentage > 25)
    {
        picnum = FACE3PIC;
    }
    else if (percentage)
    {
        picnum = FACE4PIC;
    }
    else
    {
        picnum = FACE5PIC;
    }

    m_renderer.Render2DPicture(GetEgaGraph()->GetPicture(picnum), 64, 134);
}

void GameAbyss::DrawScrolls(const PlayerInventory& playerInventory)
{
    for (uint8_t loop=0;loop<8;loop++)
    {
        if (playerInventory.GetScroll(loop))
        {
            uint8_t y = 150 + ((loop > 3) * 10);
            uint8_t x = 209 + (loop % 4) * 8;
            m_renderer.RenderNumber(loop + 1, GetEgaGraph()->GetFont(3), 1, EgaBlack, x, y);
        }
    }
}

void GameAbyss::DrawKeys(const PlayerInventory& playerInventory)
{
    m_renderer.RenderNumber(playerInventory.GetKeys(RedKey), GetEgaGraph()->GetFont(3), 2, EgaBrightYellow, 160, 149);
    m_renderer.RenderNumber(playerInventory.GetKeys(YellowKey), GetEgaGraph()->GetFont(3), 2, EgaBrightYellow, 184, 176);
    m_renderer.RenderNumber(playerInventory.GetKeys(GreenKey), GetEgaGraph()->GetFont(3), 2, EgaBrightYellow, 184, 149);
    m_renderer.RenderNumber(playerInventory.GetKeys(BlueKey), GetEgaGraph()->GetFont(3), 2, EgaBrightYellow, 160, 176);
}

void GameAbyss::DrawBonus(const PlayerInventory& playerInventory)
{
    m_renderer.RenderNumber(playerInventory.GetBolts(), GetEgaGraph()->GetFont(3), 2, EgaBrightYellow, 134, 137);
    m_renderer.RenderNumber(playerInventory.GetNukes(), GetEgaGraph()->GetFont(3), 2, EgaBrightYellow, 134, 155);
    m_renderer.RenderNumber(playerInventory.GetPotions(), GetEgaGraph()->GetFont(3), 2, EgaBrightYellow, 134, 173);
}

void GameAbyss::DrawGems(const PlayerInventory& playerInventory)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        if (playerInventory.GetGem(i))
        {
            const uint16_t picNum = RADAR_RGEMPIC + i;
            m_renderer.Render2DPicture(GetEgaGraph()->GetPicture(picNum), 256 + (i * 8), 173);
        }
    }
}

GameMaps* GameAbyss::GetGameMaps()
{
    if (m_gameMaps == NULL)
    {
        m_gameMaps = new GameMaps(gameMapsAbyss, m_gamePath);
    }

    return m_gameMaps;
}

EgaGraph* GameAbyss::GetEgaGraph()
{
    if (m_egaGraph == NULL)
    {
        const egaGraphStaticData& staticData = (m_gameId == 1) ? egaGraphAbyss : egaGraphAbyssV124;
        m_egaGraph = new EgaGraph(staticData, m_gamePath, m_renderer);
    }

    return m_egaGraph;
}

AudioRepository* GameAbyss::GetAudioRepository()
{
    if (m_audioRepository == NULL)
    {
        m_audioRepository = new AudioRepository(audioRepositoryAbyss, m_gamePath);
    }

    return m_audioRepository;
}

AudioPlayer* GameAbyss::GetAudioPlayer()
{
    if (m_audioPlayer == NULL)
    {
        m_audioPlayer = new AudioPlayer(GetAudioRepository());
    }

    return m_audioPlayer;
}

IIntroView* GameAbyss::GetIntroView()
{
    if (m_introView == NULL)
    {
        m_introView = new IntroViewAbyss(m_renderer, m_gamePath);
    }

    return m_introView;
}

const std::map<uint16_t, const DecorateActor>& GameAbyss::GetDecorateActors() const
{
    return decorateAbyssAll;
}

const std::string& GameAbyss::GetName() const
{
    return (m_gameId == 1) ? AbyssV113Name : AbyssV124Name;
}

const uint8_t GameAbyss::GetId() const
{
    return m_gameId;
}