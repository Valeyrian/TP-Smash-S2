/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "UIStagePage.h"
#include "TitleManager.h"
#include "UIDefaultCursor.h"


UIStagePage::UIStagePage(
    Scene *scene, std::array<PlayerConfig, MAX_PLAYER_COUNT> &playerConfigs,
    StageConfig &stageConfig) :
    UIObject(scene), m_stageConfig(stageConfig), m_playerConfigs(playerConfigs),
    m_ratioHeader(0.2f),
    m_header(nullptr), m_content(nullptr), m_group(nullptr)
{
    SetName("UIStagePage");
    SetParent(m_scene->GetCanvas());

    InputManager *inputManager = m_scene->GetInputManager();
    ApplicationInput *applicationInput = ApplicationInput::GetFromManager(inputManager);

    AssetManager *assets = scene->GetAssetManager();
    SpriteSheet *spriteSheet0 = nullptr;
    SpriteSheet* spriteSheet1 = nullptr;
    SpriteSheet* spriteSheet2 = nullptr;
    SpriteSheet* spriteSheet3 = nullptr;
    SpriteGroup *spriteGroup = nullptr;
    SpriteAnim* anim = nullptr; 
    TTF_Font *font = nullptr;

    //UIRect* first = new UIRect(b2Vec2(0.093, 0.14), b2Vec2(0.26, 0.6), b2Vec2(0.2, 0.2), b2Vec2(0.3, 0.3));
    //UIRect* Secound = new UIRect(b2Vec2(0.28, 0.14), b2Vec2(0.45, 0.6), b2Vec2(0.2, 0.2), b2Vec2(0.3, 0.3));

    //UIObject* cadre = new UIObject(m_scene);
    //cadre->SetLocalRect(*first);
    //cadre->SetColor(Colors::Gold);
    //UIObject* cadre2 = new UIObject(m_scene);
    //cadre2->SetLocalRect(*Secound);
    //UIFillRect* cadrebis = new UIFillRect(scene, Colors::Black);        //fond de l'anim
    //cadrebis->SetParent(cadre);                                         //fond de l'anim
    //cadrebis->SetOpacity(0.1f);                                         //fond de l'anim
    //cadrebis->SetLayer(LAYER_UI_BACKGROUND);                            //fond de l'anim
    //UIFillRect* cadrebis2 = new UIFillRect(scene, Colors::Black);        //fond de l'anim
    //cadrebis2->SetParent(cadre2);                                       //fond de l'anim
    //cadrebis2->SetOpacity(0.1f);                                        //fond de l'anim
    //cadrebis2->SetLayer(LAYER_UI_BACKGROUND);                           //fond de l'anim

//    Animator n°1

    spriteSheet0 = assets->GetSpriteSheet(SHEET_FIRE_WARRIOR);
    AssertNew(spriteSheet0);
    spriteGroup = spriteSheet0->GetGroup("Idle");
    AssertNew(spriteGroup);

    animator[0] = new UIAnimator(m_scene);
    animator[0]->SetScale(10.0f);
    animator[0]->GetLocalRect().anchorMin.Set(0.23, 0.3);
    animator[0]->GetLocalRect().anchorMax.Set(0.3, 0.6);
    animator[0]->SetEnabled(true);
   
    Animator* animator0 = animator[0]->GetAnimator();

    anim = animator0->CreateAnimation("Idle", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    animator0->PlayAnimation("Idle");

    //    Animator n°2

    spriteSheet1 = assets->GetSpriteSheet(SHEET_LIGHTNING_WARRIOR);
    AssertNew(spriteSheet1);
    spriteGroup = spriteSheet1->GetGroup("Idle");
    AssertNew(spriteGroup);

    animator[1] = new UIAnimator(m_scene);
    animator[1]->SetScale(10.0f);
    animator[1]->GetLocalRect().anchorMin.Set(0.17, 0.48);
    animator[1]->GetLocalRect().anchorMax.Set(0.3, 0.6);
    animator[1]->SetEnabled(false);

    Animator* animator1 = animator[1]->GetAnimator();

    anim = animator1->CreateAnimation("Idle", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    animator1->PlayAnimation("Idle");

    //    Animator n°3

    spriteSheet2 = assets->GetSpriteSheet(SHEET_FIRE_WARRIOR);
    AssertNew(spriteSheet2);
    spriteGroup = spriteSheet2->GetGroup("Idle");
    AssertNew(spriteGroup);

    animator[2] = new UIAnimator(m_scene);
    animator[2]->SetScale(10.0f);
    animator[2]->GetLocalRect().anchorMin.Set(0.38, 0.3);
    animator[2]->GetLocalRect().anchorMax.Set(0.52, 0.6);
    animator[2]->SetEnabled(false);

    Animator* animator2 = animator[2]->GetAnimator();

    anim = animator2->CreateAnimation("Idle", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    animator2->PlayAnimation("Idle");

    ///// n°4
    spriteSheet3 = assets->GetSpriteSheet(SHEET_LIGHTNING_WARRIOR);
    AssertNew(spriteSheet3);
    spriteGroup = spriteSheet3->GetGroup("Idle");
    AssertNew(spriteGroup);

    animator[3] = new UIAnimator(m_scene);
    animator[3]->SetScale(10.0f);
    animator[3]->GetLocalRect().anchorMin.Set(0.35, 0.48);
    animator[3]->GetLocalRect().anchorMax.Set(0.52, 0.6);
    animator[3]->SetEnabled(true);

    Animator* animator3 = animator[3]->GetAnimator();

    anim = animator3->CreateAnimation("Idle", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    animator3->PlayAnimation("Idle");

    m_group = new UISelectableGroup(m_scene);
    m_group->SetParent(this);
    m_group->AddInput(&(applicationInput->uiInputs[0]));
    m_group->SetInteractable(true);

    
    //m_group->RemoveAllSelectables();
    ////m_group->RemoveAllInputs();
    //m_group->SetVisible(true, true);
    //m_group->SetInteractable(true);
    //m_group->SetNavigationEnabled(true);

    //--------------------------------------------------------------------------
    // Header

    m_header = new UIObject(scene);
    m_header->SetName("UI Stage Header panel");
    m_header->SetParent(this);
    m_header->GetLocalRect().anchorMin.Set(0.f, 1.f - m_ratioHeader);
    m_header->GetLocalRect().anchorMax.Set(1.f, 1.f);

    UIFillRect *headerFill = new UIFillRect(scene, Colors::DarkBlue);
    headerFill->SetParent(m_header);
    headerFill->SetOpacity(0.5f);
    headerFill->SetLayer(LAYER_UI_BACKGROUND);

    //--------------------------------------------------------------------------
    // Content

    m_content = new UIObject(scene);
    m_content->SetName("UI Stage Content panel");
    m_content->SetParent(this);
    m_content->GetLocalRect().anchorMin.Set(0.f, 0.f);
    m_content->GetLocalRect().anchorMax.Set(1.f, 1.f - m_ratioHeader);

    //--------------------------------------------------------------------------
    // Title text

    font = assets->GetFont(FONT_LARGE);
    m_titleText = new UIText(scene, "Stage selection", font, Colors::Gold);
    m_titleText->SetParent(m_header);
    m_titleText->SetAnchor(Anchor::CENTER);
    
    //--------------------------------------------------------------------------
    // Player text

    font = assets->GetFont(FONT_LARGE);
    m_playerText = new UIText(scene, "Fighter selection", font, Colors::DarkBlue);
    m_playerText->SetAnchor(Anchor::CENTER);

    //--------------------------------------------------------------------------
    // Options text

    font = assets->GetFont(FONT_LARGE);
    m_optionText = new UIText(scene, "Options", font, Colors::DarkBlue);
    m_optionText->SetAnchor(Anchor::WEST);

    //--------------------------------------------------------------------------
    // Cursor

    UIDefaultCursor *cursor = new UIDefaultCursor(scene);
    m_group->SetCursor(cursor);

    //--------------------------------------------------------------------------
    // Player list

    std::string labelString;
    std::vector<std::string> textStrings;
    const float textWidth = 95.f;

    // Player 1
    labelString.assign(" ");
    textStrings.push_back("Fire warrior");
    textStrings.push_back("Lighting warrior");
    m_player1List = new UITextList(
        m_scene, labelString, textStrings, Colors::White, textWidth
    );
    m_player1List->SetIsCycle(true);
    m_player1List->AddSelectableListener(this);

    // Player 2
    labelString.assign(" ");
    m_player2List = new UITextList(
        m_scene, labelString, textStrings, Colors::White, textWidth
    );
    m_player2List->SetIsCycle(true);
    m_player2List->AddSelectableListener(this);

    //--------------------------------------------------------------------------
    // Stage duration list

    labelString.assign("Stage duration");
    textStrings.clear();
    textStrings.push_back("1 min");
    textStrings.push_back("2 min");
    textStrings.push_back("3 min");
    m_timeList = new UITextList(
        m_scene, labelString, textStrings, Colors::White, textWidth
    );
    m_timeList->SetIsCycle(false);

    ////--------------------------------------------------------------------------
    //// TODO : Ajout d'un texte et d'une liste pour la fréquence d'apparition des potions

    font = assets->GetFont(FONT_LARGE); 
   
      
    labelString.assign("Potion level");
    textStrings.clear();    
    textStrings.push_back("Aucune");
    textStrings.push_back("Lente"); 
    textStrings.push_back("Normale"); 
    textStrings.push_back("Rapide"); 
    m_potionlevel = new UITextList(    
        m_scene, labelString, textStrings, Colors::White, textWidth
    );
    m_potionlevel->SetIsCycle(true);
    m_potionlevel->AddSelectableListener(this);

    ////--------------------------------------------------------------------------
   //// TODO : Ajout d'un texte et d'une liste pour la fréquence d'apparition des bombes

    font = assets->GetFont(FONT_LARGE);


    labelString.assign("Bombes level");
    textStrings.clear();
    textStrings.push_back("Aucune");
    textStrings.push_back("Lente");
    textStrings.push_back("Normale");
    textStrings.push_back("Rapide");    
    m_bomblevel = new UITextList( 
        m_scene, labelString, textStrings, Colors::White, textWidth 
    );
    m_bomblevel->SetIsCycle(true);    
    m_bomblevel->AddSelectableListener(this); 


    //--------------------------------------------------------------------------
    // Buttons

    m_startButton = new UIDefaultButton(scene, "Start");
    m_startButton->AddSelectableListener(this);

    m_backButton = new UIDefaultButton(scene, "Back");
    m_backButton->AddSelectableListener(this);

    //--------------------------------------------------------------------------
    // Grid layouts

    // TODO : Modifier le vLayout pour ajouter un champ potion
    UIGridLayout *vLayout = new UIGridLayout(m_scene, 5, 1); 
    vLayout->SetParent(m_content); 
    vLayout->SetAnchor(Anchor::EAST);

    vLayout->SetSpacing(2.f);

    vLayout->SetRowSpacing(2, 5.f);
    vLayout->SetRowSpacing(3, 5.f);
    /*vLayout->SetRowSpacing(5, 5.f);  
    vLayout->SetRowSpacing(6, 5.f);*/ 

     
    vLayout->SetRowSize(20.f); 
    vLayout->SetColumnSize(300.f); 

    /*vLayout->AddObject(m_playerText, 0, 0);
    vLayout->AddObject(m_player1List, 1, 0);
    vLayout->AddObject(m_player2List, 2, 0)*/;
    vLayout->AddObject(m_optionText, 0, 0);
    vLayout->AddObject(m_timeList, 1, 0);
    vLayout->AddObject(m_potionlevel, 2, 0);
    vLayout->AddObject(m_bomblevel, 3, 0);
    


    // Nouveau Grid bis

    UIGridLayout* vLayoutbis = new UIGridLayout(m_scene, 3, 2);
    vLayoutbis->SetParent(this);
    
    //vLayoutbis->SetAnchor(Anchor::WEST);
    vLayoutbis->GetLocalRect().anchorMin.x = 0.0875;
    vLayoutbis->GetLocalRect().anchorMax.y = 0.1;

    vLayoutbis->SetSpacing(2.f);

    vLayoutbis->SetRowSpacing(0, 50.f);
    vLayoutbis->SetRowSpacing(1, 50.f);
    vLayoutbis->SetColumnSpacing(0, 10.f);
    /*vLayout->SetRowSpacing(5, 5.f);
    vLayout->SetRowSpacing(6, 5.f);*/


    vLayoutbis->SetRowSize(10.f);
    vLayoutbis->SetColumnSize(120.f);

    //vLayoutbis->AddObject(m_playerText, 0, 0);
    vLayoutbis->AddObject(m_player1List, 0, 0);
    vLayoutbis->AddObject(m_player2List, 0, 1);
    /*vLayout->AddObject(m_optionText, 3, 0);
    vLayout->AddObject(m_timeList, 4, 0);
    vLayout->AddObject(m_potionlevel, 5, 0);
    vLayout->AddObject(m_bomblevel, 6, 0);
    vLayout->AddObject(hLayout, 7, 0);*/

    UIGridLayout* layoutFighter = new UIGridLayout(m_scene, 1, 1); 
    layoutFighter->SetParent(m_content);
    layoutFighter->GetLocalRect().anchorMin.Set(0.0875, 0.85f);
    layoutFighter->GetLocalRect().anchorMax.Set(0.5, 0.9);

    layoutFighter->AddObject(m_playerText, 0, 0);
    

    UIGridLayout *hLayout = new UIGridLayout(m_scene, 1, 2);
    hLayout->SetSpacing(30.f);
    hLayout->SetAnchor(Anchor::SOUTH);
    hLayout->SetColumnSize(100.f);

    hLayout->AddObject(m_backButton, 0, 0);
    hLayout->AddObject(m_startButton, 0, 1);

    // TODO : Modifier pour laisser la place au champ potion
    vLayout->AddObject(hLayout, 4, 0);

    //vLayout->Update();
    layoutFighter->Update();
    vLayoutbis->Update();
    hLayout->Update();

    //--------------------------------------------------------------------------
    // Fade In/Out et Initialisation

    InitFadeAnim();
    InitPageWithConfig();

    //--------------------------------------------------------------------------
    // Navigation

    m_group->AddSelectable(m_player1List);
    m_group->AddSelectable(m_player2List);
    m_group->AddSelectable(m_timeList);
    m_group->AddSelectable(m_potionlevel);
    m_group->AddSelectable(m_bomblevel);


    m_group->AddSelectable(m_backButton);
    m_group->AddSelectable(m_startButton);
    // TODO : Ajouter la potion

    m_group->ComputeAutoNavigation();

    m_group->SetSelected(m_player1List);
    m_group->SetCursorOnSelected();
}

UIStagePage::~UIStagePage()
{
}

void UIStagePage::Update()
{
    UIObject::Update();

    if (IsFadingIn() || IsFadingOut()) return;

    TitleManager *titleManager = TitleManager::GetFromScene(m_scene);
    if (titleManager == nullptr) return;

    AssetManager *assets = m_scene->GetAssetManager();
    InputManager *inputManager = m_scene->GetInputManager();
    ApplicationInput *applicationInput = ApplicationInput::GetFromManager(inputManager);

    for (const UIInput &input : applicationInput->uiInputs)
    {
        if (input.start)
        {
            m_scene->GetSceneManager()->QuitScene();

            assets->PlaySoundFX(SFX_UI_VALIDATE);

            UpdateConfigs();
            m_group->SetSelected(nullptr);
            m_group->SetInteractable(false);

            titleManager->QuitScene();
        }
    }
}

void UIStagePage::OnClick(UISelectable *which)
{
    TitleManager *titleManager = TitleManager::GetFromScene(m_scene);
    if (titleManager == nullptr) return;

    if (which == m_startButton)
    {
        UpdateConfigs();
        m_group->SetSelected(nullptr);
        m_group->SetInteractable(false);

        titleManager->QuitScene();
    }
    else if (which == m_backButton)
    {
        UpdateConfigs();
        PlayFadeOut();
        m_group->SetSelected(nullptr);
        m_group->SetInteractable(false);

        titleManager->OpenPage(TitleManager::Page::TITLE);
    }
}

void UIStagePage::OnItemChanged(UISelectable *which, int itemIdx, int prevItemIdx, bool increase)
{
    UpdateConfigs();
}

void UIStagePage::OnFadeOutEnd(UIObject *which)
{
    if (which != this) return;

    TitleManager *titleManager = TitleManager::GetFromScene(m_scene);
    if (titleManager == nullptr) return;

    titleManager->QuitPage(TitleManager::Page::STAGE);
}

void UIStagePage::InitFadeAnim()
{
    UIFadeDef fadeDef;
    fadeDef.Reset(1.f);
    fadeDef.fadeOpacity = true;

    SetFadeInAnimation(fadeDef);
    SetFadeOutAnimation(fadeDef);
    SetFadeChildren(false);
}

void UIStagePage::InitPageWithConfig()
{
    switch (m_playerConfigs[0].type)
    {
    default:
    case PlayerConfig::Type::FIRE_WARRIOR: 
        m_player1List->SetFirstSelectedItem(0); break;
    case PlayerConfig::Type::LIGHTNING_WARRIOR: 
        m_player1List->SetFirstSelectedItem(1); break;
    }

    switch (m_playerConfigs[1].type)
    {
    default:
    case PlayerConfig::Type::FIRE_WARRIOR: 
        m_player2List->SetFirstSelectedItem(0); break;
    case PlayerConfig::Type::LIGHTNING_WARRIOR: 
        m_player2List->SetFirstSelectedItem(1); break;
    }

    switch (m_stageConfig.duration)
    {
    default:
    case  1: m_timeList->SetFirstSelectedItem(0); break;
    case  2: m_timeList->SetFirstSelectedItem(1); break;
    case  3: m_timeList->SetFirstSelectedItem(2); break;
    }

    // TODO : Gérer la fréquence de la potion
}

void UIStagePage::UpdateConfigs()
{
    switch (m_player1List->GetSelectedItem())
    {
    default:
    case 0: 
        animator[1]->SetEnabled(false);
        animator[0]->SetEnabled(true);
        m_playerConfigs[0].type = PlayerConfig::Type::FIRE_WARRIOR;
    
        printf("cas 0\n");
        break;
    case 1: 
        
        animator[0]->SetEnabled(false);
        animator[1]->SetEnabled(true);
        m_playerConfigs[0].type = PlayerConfig::Type::LIGHTNING_WARRIOR;
        printf("cas 1\n");
        break;
    }

    switch (m_player2List->GetSelectedItem())
    {
    default:
    case 0: 
        m_playerConfigs[1].type = PlayerConfig::Type::FIRE_WARRIOR;
        animator[2]->SetEnabled(true);
        animator[3]->SetEnabled(false);
        printf("cas 2\n");
        
    break;
    case 1: 
        m_playerConfigs[1].type = PlayerConfig::Type::LIGHTNING_WARRIOR;
        printf("cas 3\n");
        animator[2]->SetEnabled(false);
        animator[3]->SetEnabled(true);
    break;
    }


    switch (m_timeList->GetSelectedItem())
    {
    default:
    case 0: m_stageConfig.duration = 1; break;
    case 1: m_stageConfig.duration = 2; break;
    case 2: m_stageConfig.duration = 3; break;
    }

   switch (m_potionlevel->GetSelectedItem())
   {
   case 0: m_stageConfig.potionLevel = StageConfig::Potion::AUCUNE; break;
   case 1: m_stageConfig.potionLevel = StageConfig::Potion::LENTE; break;
   case 2: m_stageConfig.potionLevel = StageConfig::Potion::NORMALE; break;
   case 3: m_stageConfig.potionLevel = StageConfig::Potion::RAPIDE; break;
   }
   switch (m_bomblevel->GetSelectedItem())
   {
   case 0: m_stageConfig.bombLevel = StageConfig::Bomb::AUCUNE; break;
   case 1: m_stageConfig.bombLevel = StageConfig::Bomb::LENTE; break;
   case 2: m_stageConfig.bombLevel = StageConfig::Bomb::NORMALE; break;
   case 3: m_stageConfig.bombLevel = StageConfig::Bomb::RAPIDE; break;
   }

}
