/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "StageManager.h"
#include "MainCamera.h"

#include "Player.h"
#include "FireWarrior.h"
#include "LightningWarrior.h"

#include "RockyPassStage.h"
#include "platformG.h"
#include "platformD.h"
#include "Background.h"

#include "Potion.h"
#include "Bomb.h"


StageManager::StageManager(
    InputManager *inputManager,
    std::array<PlayerConfig, MAX_PLAYER_COUNT> &playerConfigs,
    StageConfig &stageConfig) :
    BaseSceneManager(inputManager), m_configs(),
    m_players(), m_paused(false),
    m_pauseMenu(nullptr), m_stageConfig(stageConfig),
    m_delayStage(0.f), m_playerStats(), m_delayPotion(Random::RangeF(1.f, 30.f)),m_MaxDelayPotion(-1),
    m_delayBomb(Random::RangeF(1,  30.f)), m_MaxDelayBomb(-1) // TODO : ajouter un membre pour le délai de la potion (init -1)
{
    Scene *scene = GetScene();
    AssetManager *assets = scene->GetAssetManager();
    InitAssets(assets);
    InitBackground(assets, (int)stageConfig.type);
    InitFonts(assets);
    InitMusic(assets);
    InitSFX(assets);

    // Stage
    if (true)
    {
        InitRockyPass();
        InitPlatformG();
        InitPlatformD();
    }

    // Crée la caméra
    SetMainCamera(new MainCamera(scene));


    if (true)
    {
        m_delayStage = (float)stageConfig.duration * 60.f;
    }

    b2Vec2 startPositions[4] = {
        b2Vec2(-6.f, 0.05f), b2Vec2(+6.f, 0.05f),
        b2Vec2(-2.f, 0.05f), b2Vec2(+2.f, 0.05f),
    };

    // Initialisation des stats
    int playerID = 0;
    for (PlayerConfig &config : playerConfigs)
    {
        if (config.enabled == false) continue;

        config.playerID = playerID;

        m_playerStats.push_back(PlayerStats());
        m_configs.push_back(config);

        playerID++;
    }
    m_playerCount = playerID;

    // Crée les joueurs
    for (int i = 0; i < m_playerCount; i++)
    {
        PlayerConfig *config = &m_configs[i];
        PlayerStats *stats = &m_playerStats[i];

        stats->lifeCount = stageConfig.lifeCount;

        Player *player = nullptr;
        switch (config->type)
        {
        default:
        case PlayerConfig::Type::FIRE_WARRIOR:
            player = new FireWarrior(scene, config, stats);
            break;
        case PlayerConfig::Type::LIGHTNING_WARRIOR:
            player = new LightningWarrior(scene, config, stats);
            break;
        }
        player->SetStartPosition(startPositions[i % 4]);

        m_players.push_back(player);
    }

    // Crée l'interface utilisateur
    m_stageHUD = new UIStageHUD(scene);

    // TODO : Initialiser les potions en fonction du m_stageConfig
    switch (m_stageConfig.potionLevel)
    {
    case StageConfig::Potion::AUCUNE :m_MaxDelayPotion = -1; break;
    case StageConfig::Potion::LENTE: m_MaxDelayPotion = 45; break;
    case StageConfig::Potion::NORMALE: m_MaxDelayPotion = 30; break;
    case StageConfig::Potion::RAPIDE: m_MaxDelayPotion = 15; break;
    }
    switch (m_stageConfig.bombLevel)
    {
    case StageConfig::Bomb::AUCUNE:m_MaxDelayBomb = -1; break;
    case StageConfig::Bomb::LENTE:m_MaxDelayBomb = 75; break;
    case StageConfig::Bomb::NORMALE:m_MaxDelayBomb = 60; break;
    case StageConfig::Bomb::RAPIDE:m_MaxDelayBomb = 15; break;

    }
   
    
}

StageManager::~StageManager()
{
}

void StageManager::OnSceneUpdate()
{
    BaseSceneManager::OnSceneUpdate();

    Scene *scene = GetScene();
    InputManager *inputManager = scene->GetInputManager();
    ApplicationInput *applicationInput = ApplicationInput::GetFromManager(inputManager);

  
    m_delayStage -= scene->GetDelta();
    m_delayBomb -= scene->GetDelta(); 
    m_delayPotion -= scene->GetDelta();
   // printf("mdelaypotion : %f \n", m_delayPotion);
     // mouvement de la platform
  //  printf("mdelayBombde : %f \n", m_delayBomb);


    

    if (m_delayStage < 0.f)
    {
        QuitScene();
    }

    if (applicationInput->pausePressed)
    {
        if (m_paused)
        {
            assert(m_pauseMenu != nullptr);

            m_pauseMenu->PlayFadeOut();
            scene->GetAssetManager()->PlaySoundFX(SFX_UI_UNPAUSE);
        }
        else
        {
            assert(m_pauseMenu == nullptr);

            m_pauseMenu = new UIPauseMenu(scene);
            m_pauseMenu->SetParent(scene->GetCanvas());
            m_pauseMenu->PlayFadeIn();

            scene->GetTime().SetTimeScale(0.0f);
            m_paused = true;

            scene->GetAssetManager()->PlaySoundFX(SFX_UI_PAUSE);
        }
    }
}

void StageManager::OnSceneFixedUpdate()
{
    BaseSceneManager::OnSceneFixedUpdate();
    Scene *scene = GetScene();

    //printf("delayPotion : %f \n",m_delayPotion);

   
    if (m_delayPotion <= 0 && m_MaxDelayPotion != -1)
    {
        AddPotion();

    }
    // TODO : mettre a jour le délai + ajout si délai potion et bombe
    //printf("delayBomb : %f et maxdealayBomb %f\n", m_delayBomb, m_MaxDelayBomb);
    
   if (m_delayBomb <= 0 && m_MaxDelayBomb != -1)
    {
        AddBomb();

    }

}

void StageManager::QuitPause()
{
    m_pauseMenu->Delete();
    m_pauseMenu = nullptr;
    m_paused = false;
    GetScene()->GetTime().SetTimeScale(1.f);

    InputManager *inputManager = GetScene()->GetInputManager();
}

StageManager *StageManager::GetFromScene(Scene *scene)
{
    if (scene == nullptr)
    {
        assert(false);
        return nullptr;
    }
    return dynamic_cast<StageManager *>(scene->GetSceneManager());
}

void StageManager::AddPotion()
{
    Scene *scene = GetScene();
    Potion *potion = new Potion(scene);
    b2Vec2 position(Random::RangeF(-7.f, 7.f), 10.f); 
   // b2Vec2 position(10.f, 10.f);
    potion->SetStartPosition(position);  
    if (m_MaxDelayPotion >= 0)
        m_delayPotion = Random::RangeF(1, m_MaxDelayPotion);
    else
        m_delayPotion = -1;
    printf("add potion \n");
}

void StageManager::AddBomb()
{
    Scene* scene = GetScene();
    Bomb* bomb = new Bomb(scene);
    b2Vec2 position(Random::RangeF(-7.f, 7.f), 10.f);
    // b2Vec2 position(10.f, 10.f);
    bomb->SetStartPosition(position);
    if (m_MaxDelayBomb >= 0)
        m_delayBomb = Random::RangeF(1.f, m_MaxDelayBomb);
    else
        m_delayBomb = -1;
    printf("add bomb \n");
}

void StageManager::InitRockyPass()
{
    Scene *scene = GetScene();

    // Stage
    RockyPassStage *stage = new RockyPassStage(scene);

    // Background
    AssetManager *assets = scene->GetAssetManager();
    Background *background = new Background(scene, LAYER_BACKGROUND);
    const std::vector<SDL_Texture *> &m_textures = assets->GetBackgrounds();
    assert(m_textures.size() == 3);
    float factors[] = { 0.05f, 0.3f, 0.6f };
    Background::RenderMode modes[] = {
        Background::RenderMode::FILL_VERTICAL,
        Background::RenderMode::FILL_BELOW,
        Background::RenderMode::FILL_BELOW
    };
    for (int i = 0; i < 3; i++)
    {
        background->AddLayer(m_textures[i], b2Vec2(factors[i], 0.9f * factors[i]), modes[i]);
    }
    background->SetPixelsPerUnit(14.f);
    b2Vec2 worldDim = background->GetWorldDimensions();
    background->SetWorldCenter(0.5f * worldDim + b2Vec2(0.f, -5.f));

    // Music
    scene->GetAssetManager()->FadeInMusic(MUSIC_ROCKY_PASS);
}

void StageManager::InitPlatformG()
{
    Scene* scene = GetScene();

    // Stage
    PlatformG* stage = new PlatformG(scene);

    // Background
    AssetManager* assets = scene->GetAssetManager();
    Background* background = new Background(scene, LAYER_BACKGROUND);
    const std::vector<SDL_Texture*>& m_textures = assets->GetBackgrounds();
    assert(m_textures.size() == 3);
    float factors[] = { 0.05f, 0.3f, 0.6f };
    Background::RenderMode modes[] = {
        Background::RenderMode::FILL_VERTICAL,
        Background::RenderMode::FILL_BELOW,
        Background::RenderMode::FILL_BELOW
    };
    for (int i = 0; i < 3; i++)
    {
        background->AddLayer(m_textures[i], b2Vec2(factors[i], 0.9f * factors[i]), modes[i]);
    }
    background->SetPixelsPerUnit(14.f);
    b2Vec2 worldDim = background->GetWorldDimensions();
    background->SetWorldCenter(0.5f * worldDim + b2Vec2(0.f, -1.f)); // 0 -5 origine

    // Music
    scene->GetAssetManager()->FadeInMusic(MUSIC_ROCKY_PASS);
}
void StageManager::InitPlatformD()
{
    Scene* scene = GetScene();

    // Stage
    PlatformD* stage = new PlatformD(scene);

    // Background
    AssetManager* assets = scene->GetAssetManager();
    Background* background = new Background(scene, LAYER_BACKGROUND);
    const std::vector<SDL_Texture*>& m_textures = assets->GetBackgrounds();
    assert(m_textures.size() == 3);
    float factors[] = { 0.05f, 0.3f, 0.6f };
    Background::RenderMode modes[] = {
        Background::RenderMode::FILL_VERTICAL,
        Background::RenderMode::FILL_BELOW,
        Background::RenderMode::FILL_BELOW
    };
    for (int i = 0; i < 3; i++)
    {
        background->AddLayer(m_textures[i], b2Vec2(factors[i], 0.9f * factors[i]), modes[i]);
    }
    background->SetPixelsPerUnit(14.f);
    b2Vec2 worldDim = background->GetWorldDimensions();
    background->SetWorldCenter(0.5f * worldDim + b2Vec2(0.f, -1.f)); // 0 -5 origine

    // Music
    scene->GetAssetManager()->FadeInMusic(MUSIC_ROCKY_PASS);
}
