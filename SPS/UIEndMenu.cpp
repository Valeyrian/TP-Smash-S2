/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "UIEndMenu.h"
#include "StageManager.h"
#include "UIDefaultCursor.h"

UIEndMenu::UIEndMenu(Scene* scene) : 
    UIObject(scene)
{
    SetName("UIEndMenu");
    SetParent(m_scene->GetCanvas());

    InputManager* inputManager = m_scene->GetInputManager();
    ApplicationInput* applicationInput = ApplicationInput::GetFromManager(inputManager);

    AssetManager* assets = scene->GetAssetManager();
    SpriteSheet* spriteSheet = nullptr;
    SpriteGroup* spriteGroup = nullptr;

    SpriteSheet* spriteSheetEnd1 = nullptr; //sprite des players
    SpriteSheet* spriteSheetEnd2 = nullptr;
    SpriteSheet* spriteSheetEnd3 = nullptr;
    SpriteSheet* spriteSheetEnd4 = nullptr;
    SpriteAnim* playerAnim = nullptr;
    SpriteGroup *SpriteGrpanimEnd1 = nullptr; 
    SpriteGroup *SpriteGrpanimEnd2= nullptr; 
    SpriteGroup *SpriteGrpanimEnd3 = nullptr; 
    SpriteGroup *SpriteGrpanimEnd4 = nullptr; 

    TTF_Font* font = nullptr;

    m_group = new UISelectableGroup(m_scene);
    m_group->SetParent(this);
    m_group->AddInput(&(applicationInput->uiInputs[0]));
    m_group->SetInteractable(true);

    //sprite sheet fire 
    spriteSheetEnd1 = assets->GetSpriteSheet(SHEET_SHOWTIME_WARRIOR);   
    spriteSheetEnd2 = assets->GetSpriteSheet(SHEET_FIRE_WARRIOR); 
    spriteSheetEnd3 = assets->GetSpriteSheet(SHEET_SHOWTIME_LIGHTNING);   
    spriteSheetEnd4 = assets->GetSpriteSheet(SHEET_LIGHTNING_WARRIOR);


    SpriteGrpanimEnd1 = spriteSheetEnd1->GetGroup("ShowTime");
    AssertNew(SpriteGrpanimEnd1);
    

    SpriteGrpanimEnd2 = spriteSheetEnd2->GetGroup("Die");
    AssertNew(SpriteGrpanimEnd2);
 

    //sprite ligtning

    SpriteGrpanimEnd3 = spriteSheetEnd3->GetGroup("ShowTime");
    AssertNew(SpriteGrpanimEnd3);
   
    
    SpriteGrpanimEnd4 = spriteSheetEnd4->GetGroup("Die");  
    AssertNew(SpriteGrpanimEnd4);
  




    //--------------------------------------------------------------------------
    // Title text

    font = assets->GetFont(FONT_LARGE);
    m_titleText = new UIText(scene, "End Of Game", font, Colors::Gold);
    m_titleText->SetName("UI End Title");
    m_titleText->SetAnchor(Anchor::NORTH);
    m_titleText->GetLocalRect().anchorMin.y = 0.01;
    m_titleText->GetLocalRect().anchorMax.y = 0.9;

    //--------------------------------------------------------------------------
    // Fill

    m_endFill = new UIFillRect(scene, Colors::DarkBlue);
    m_endFill->SetParent(this);
    m_endFill->SetLayer(LAYER_UI_BACKGROUND);
    m_endFill->SetOpacity(1.f);


    //--------------------------------------------------------------------------
    // Animation

    m_animator[0] = new UIAnimator(m_scene);
    m_animator[0]->SetScale(8);
    m_animator[0]->GetLocalRect().anchorMin.Set(0.5, 0.5);
    m_animator[0]->GetLocalRect().anchorMax.Set(0.5, 0.5);

    m_animator[1] = new UIAnimator(m_scene);
    m_animator[1]->SetScale(8);
    m_animator[1]->GetLocalRect().anchorMin.Set(0.5, 0.5);
    m_animator[1]->GetLocalRect().anchorMax.Set(0.5, 0.5);

    m_animator[2] = new UIAnimator(m_scene);
    m_animator[2]->SetScale(8);
    m_animator[2]->GetLocalRect().anchorMin.Set(0.5, 0.5);
    m_animator[2]->GetLocalRect().anchorMax.Set(0.5, 0.5);

    m_animator[3] = new UIAnimator(m_scene);
    m_animator[3]->SetScale(8);
    m_animator[3]->GetLocalRect().anchorMin.Set(0.5, 0.5);
    m_animator[3]->GetLocalRect().anchorMax.Set(0.5, 0.5);

    m_animator[4] = new UIAnimator(m_scene);
    m_animator[4]->SetScale(8);
    m_animator[4]->GetLocalRect().anchorMin.Set(0.5, 0.5);
    m_animator[4]->GetLocalRect().anchorMax.Set(0.5, 0.5);

    m_animator[5] = new UIAnimator(m_scene);
    m_animator[5]->SetScale(8);
    m_animator[5]->GetLocalRect().anchorMin.Set(0.5, 0.5);
    m_animator[5]->GetLocalRect().anchorMax.Set(0.5, 0.5);

    m_animator[6] = new UIAnimator(m_scene);
    m_animator[6]->SetScale(8);
    m_animator[6]->GetLocalRect().anchorMin.Set(0.5, 0.5);
    m_animator[6]->GetLocalRect().anchorMax.Set(0.5, 0.5);

    m_animator[7] = new UIAnimator(m_scene);
    m_animator[7]->SetScale(8);
    m_animator[7]->GetLocalRect().anchorMin.Set(0.5, 0.5);
    m_animator[7]->GetLocalRect().anchorMax.Set(0.5, 0.5);

    Animator* animEnd0 = m_animator[0]->GetAnimator(); //fire gagnant gauche
    playerAnim = animEnd0->CreateAnimation("Idle", SpriteGrpanimEnd1);
    playerAnim->SetCycleCount(-1);
    playerAnim->SetFPS(15.f);
    animEnd0->PlayAnimation("Idle");

    Animator* animEnd1 = m_animator[1]->GetAnimator(); // fire gauche perdant
    playerAnim = animEnd1->CreateAnimation("Idle", SpriteGrpanimEnd2);
    playerAnim->SetCycleCount(-1);
    playerAnim->SetFPS(15.f);
    animEnd1->PlayAnimation("Idle");

    Animator* animEnd2 = m_animator[2]->GetAnimator(); // lightning gauche gagnant
    playerAnim = animEnd2->CreateAnimation("Idle", SpriteGrpanimEnd3);
    playerAnim->SetCycleCount(-1);
    playerAnim->SetFPS(15.f);
    animEnd2->PlayAnimation("Idle");

    Animator* animEnd3 = m_animator[3]->GetAnimator(); // ligthning gauche perdant
    playerAnim = animEnd3->CreateAnimation("Idle", SpriteGrpanimEnd4);
    playerAnim->SetCycleCount(-1);
    playerAnim->SetFPS(15.f);
    animEnd3->PlayAnimation("Idle");

    Animator* animEnd4 = m_animator[4]->GetAnimator(); // fire droite gagant
    playerAnim = animEnd4->CreateAnimation("Idle", SpriteGrpanimEnd1);
    playerAnim->SetCycleCount(-1);
    playerAnim->SetFPS(15.f);
    animEnd4->PlayAnimation("Idle");

    Animator* animEnd5 = m_animator[5]->GetAnimator(); // fire droite perdant
    playerAnim = animEnd5->CreateAnimation("Idle", SpriteGrpanimEnd2);
    playerAnim->SetCycleCount(-1);
    playerAnim->SetFPS(15.f);
    animEnd5->PlayAnimation("Idle");

    Animator* animEnd6 = m_animator[6]->GetAnimator(); // ligthning droite gagnant
    playerAnim = animEnd6->CreateAnimation("Idle", SpriteGrpanimEnd3);
    playerAnim->SetCycleCount(-1);
    playerAnim->SetFPS(15.f);
    animEnd6->PlayAnimation("Idle");

    Animator* animEnd7 = m_animator[7]->GetAnimator(); // lightning droite perdant
    playerAnim = animEnd7->CreateAnimation("Idle", SpriteGrpanimEnd4);
    playerAnim->SetCycleCount(-1);
    playerAnim->SetFPS(15.f);
    animEnd7->PlayAnimation("Idle");

    //--------------------------------------------------------------------------
    // Player 1 Init stats
        
    font = assets->GetFont(FONT_NORMAL); 
    m_damageGived1 = new UIText(scene, "Damage Gived Player 1", font, Colors::Gold);
    m_damageGived1->SetName("Damage Gived Player 1");
   
    font = assets->GetFont(FONT_NORMAL); 
    m_damagetake1 = new UIText(scene, "Damage Took Player 1", font, Colors::Gold); 
    m_damagetake1->SetName("Damage Took Player 1"); 

    font = assets->GetFont(FONT_NORMAL); 
    m_fallCount1 = new UIText(scene, "Fall Count Player 1", font, Colors::Gold);
    m_fallCount1->SetName("Fall Count Player 1");

    font = assets->GetFont(FONT_NORMAL);
    m_accuracy1 = new UIText(scene, "Accuracy Player 1", font, Colors::Gold);
    m_accuracy1->SetName("Accuracy Player 1");
    
    //--------------------------------------------------------------------------
    // Player 2 Init stats

    font = assets->GetFont(FONT_NORMAL);
    m_damageGived2 = new UIText(scene, "Damage Gived Player 2", font, Colors::Gold);
    m_damageGived2->SetName("Damage Gived Player 2");

    font = assets->GetFont(FONT_NORMAL);
    m_damagetake2 = new UIText(scene, "Damage Took Player 2", font, Colors::Gold);
    m_damagetake2->SetName("Damage Took Player 2");

    font = assets->GetFont(FONT_NORMAL);
    m_fallCount2 = new UIText(scene, "Fall Count Player 2", font, Colors::Gold);
    m_fallCount2->SetName("Fall Count Player 2");

    font = assets->GetFont(FONT_NORMAL);    
    m_accuracy2 = new UIText(scene, "Accuracy Player 2", font, Colors::Gold);
    m_accuracy2->SetName("AccuracyPlayer 2");
    

    //--------------------------------------------------------------------------
    /// player Stats Attribution

    StageManager* stageManager = StageManager::GetFromScene(m_scene);
 
    Player* player1 = stageManager->GetPlayer(0);
    int score1 = (int)player1->GetEjectionScore();    
    PlayerStats const* stat1 = player1->GetStats();

    Player* player2 = stageManager->GetPlayer(1);
    int score2 = (int)player1->GetEjectionScore();
    PlayerStats const* stat2 = player2->GetStats();
    PlayerConfig const* config1 = player1->GetConfig();
    PlayerConfig const* config2 = player2->GetConfig();


    m_damageGived1->SetString(std::to_string((int)stat1->damageGiven));
    m_damageGived2->SetString(std::to_string((int)stat2->damageGiven));
    if (stat1->damageGiven > stat2->damageGiven)
    {
        m_damageGived1->SetColor(Colors::Green);
        m_damageGived2->SetColor(Colors::Red);
    }
    else if (stat1->damageGiven < stat2->damageGiven)
    {
        m_damageGived1->SetColor(Colors::Red);    
        m_damageGived2->SetColor(Colors::Green);  
    }
    else 
    {
        m_damageGived1->SetColor(Colors::Gold);
        m_damageGived2->SetColor(Colors::Gold);
    }


    m_damagetake1->SetString(std::to_string((int)stat1->damageTaken));
    m_damagetake2->SetString(std::to_string((int)stat2->damageTaken));
    if (stat1->damageTaken < stat2->damageTaken)
    {
        m_damagetake1->SetColor(Colors::Green);
        m_damagetake2->SetColor(Colors::Red);
    }
    else if (stat1->damageTaken > stat2->damageTaken)
    {
        m_damagetake1->SetColor(Colors::Red);
        m_damagetake2->SetColor(Colors::Green);
    }
    else 
    {
        m_damagetake1->SetColor(Colors::Gold);
        m_damagetake2->SetColor(Colors::Gold);
    }

    m_fallCount1->SetString(std::to_string(stat1->fallCount));
    m_fallCount2->SetString(std::to_string(stat2->fallCount));
    if (stat1->fallCount < stat2->fallCount)
    {
        m_fallCount1->SetColor(Colors::Green); 
        m_fallCount2->SetColor(Colors::Red);
       
        if (config1->type == PlayerConfig::Type::FIRE_WARRIOR)
        {
            m_animator[0]->SetEnabled(true);//on fire ganant droite
            m_animator[7]->SetEnabled(true); //on lightning perdant gauche
            
            m_animator[1]->SetEnabled(false);
            m_animator[2]->SetEnabled(false);
            m_animator[3]->SetEnabled(false);
            m_animator[4]->SetEnabled(false);
            m_animator[5]->SetEnabled(false);
            m_animator[6]->SetEnabled(false);
        }
      
        if (config1->type == PlayerConfig::Type::LIGHTNING_WARRIOR)
        {
            m_animator[2]->SetEnabled(true);//on lithning gagant droite
            m_animator[5]->SetEnabled(true); // on

                m_animator[0]->SetEnabled(false);
            m_animator[1]->SetEnabled(false);
            m_animator[3]->SetEnabled(false);
            m_animator[4]->SetEnabled(false);
            m_animator[6]->SetEnabled(false);
            m_animator[7]->SetEnabled(false);
        }
    }
    else  if (stat1->fallCount > stat2->fallCount)
    {
        m_fallCount1->SetColor(Colors::Red);
        m_fallCount2->SetColor(Colors::Green);

    }
    else
    {
        m_fallCount1->SetColor(Colors::Gold);
        m_fallCount2->SetColor(Colors::Gold);
    }

    // travail de l'accuracy
    float accuracy1 = (stat1->attackDone / stat1->totalAttack) * 100;
    float accuracy2 = (stat2->attackDone / stat2->totalAttack) * 100;

    m_accuracy1->SetString(std::to_string((int)accuracy1) + "%");
    m_accuracy2->SetString(std::to_string((int)accuracy2) + "%");
    if (accuracy1 > accuracy2)
    {
        m_accuracy1->SetColor(Colors::Green);  
        m_accuracy2->SetColor(Colors::Red);    
    }
    else if (accuracy1 < accuracy2)
    {
        m_accuracy1->SetColor(Colors::Red);    
        m_accuracy2->SetColor(Colors::Green);   
    }
    else
    {
        m_accuracy1->SetColor(Colors::Gold);
        m_accuracy2->SetColor(Colors::Gold); 
    }
   
 //--------------------------------------------------------------------------
  /// Title Stats Attribution

     font = assets->GetFont(FONT_NORMAL);
   
     m_DamageGivedTitle = new UIText(scene, "Damage Gived ", font, Colors::White);
     m_DamageGivedTitle->SetName("Damage Gived Title");

     m_DamageTakeTitle = new UIText(scene, "Damage Take", font, Colors::White);
     m_DamageTakeTitle->SetName("Damage Gived Title");

     m_FallCountTitle = new UIText(scene, "Fall Count ", font, Colors::White);
     m_FallCountTitle->SetName("Damage Gived Title");

     m_AccuracyTitle = new UIText(scene, "Accuracy", font, Colors::White);
     m_AccuracyTitle->SetName("Accuracy Title");
    
    //--------------------------------------------------------------------------
    // Buttons

    m_continueButton = new UIDefaultButton(scene, "Quit Game");
    m_continueButton->AddSelectableListener(this);
    m_continueButton->SetSoundOnClick(SFX_UI_UNPAUSE);

    m_mainMenuButton = new UIDefaultButton(scene, "Quit to menu");
    m_mainMenuButton->AddSelectableListener(this);

    //--------------------------------------------------------------------------
    // Cursor

    UIDefaultCursor* cursor = new UIDefaultCursor(scene);
    m_group->SetCursor(cursor);

    //--------------------------------------------------------------------------
    // Button Grid layout

    UIGridLayout* vLayout = new UIGridLayout(m_scene, 1, 2);
    vLayout->SetParent(this);
    vLayout->SetAnchor(Anchor::SOUTH);
    //vLayout->SetSpacing(5.f);
    vLayout->SetRowSize(22.f);
    vLayout->SetColumnSize(100.f);
    vLayout->SetColumnSpacing(5.f);

    vLayout->AddObject(m_continueButton, 0, 1);
    vLayout->AddObject(m_mainMenuButton, 0, 0);

    //--------------------------------------------------------------------------
    // Grid layout Stat 

    UIGridLayout* StatLayout = new UIGridLayout(m_scene, 4, 2);    
    StatLayout->SetParent(this);   
    StatLayout->SetAnchor(Anchor::CENTER);  
    //StatLayout->SetSpacing(5.f);
    StatLayout->SetRowSize(22.f);  
    StatLayout->SetColumnSize(100.f);  
    StatLayout->SetColumnSpacing(20.f); 
    StatLayout->SetRowSpacing(25.f);
    
    StatLayout->AddObject(m_damageGived1, 0, 0);
    StatLayout->AddObject(m_damageGived2, 0, 1); 

    StatLayout->AddObject(m_damagetake1, 1, 0);
    StatLayout->AddObject(m_damagetake2, 1, 1);

    StatLayout->AddObject(m_fallCount1, 2, 0);
    StatLayout->AddObject(m_fallCount2, 2, 1);

    StatLayout->AddObject(m_accuracy1, 3, 0);
    StatLayout->AddObject(m_accuracy2, 3, 1);

    //--------------------------------------------------------------------------
   // Grid layout Stat Title

    UIGridLayout* TitleStatLayout = new UIGridLayout(m_scene, 4, 1); 
    TitleStatLayout->SetParent(this);    
    TitleStatLayout->SetAnchor(Anchor::CENTER);  
    TitleStatLayout->SetRowSize(22.f);
    TitleStatLayout->SetColumnSize(100);
    TitleStatLayout->SetColumnSpacing(20.f);    
    TitleStatLayout->SetRowSpacing(25.f);   

    TitleStatLayout->AddObject(m_DamageGivedTitle, 0, 0);
    TitleStatLayout->AddObject(m_DamageTakeTitle, 1, 0);
    TitleStatLayout->AddObject(m_FallCountTitle, 2, 0);
    TitleStatLayout->AddObject(m_AccuracyTitle, 3, 0);


   
    //--------------------------------------------------------------------------
    // Fade In/Out


    InitFadeAnim();

    //--------------------------------------------------------------------------
    // Navigation

    m_group->AddSelectable(m_continueButton);
    m_group->AddSelectable(m_mainMenuButton);
    m_group->ComputeAutoNavigation();

    m_group->SetSelected(m_continueButton);
    m_group->SetCursorOnSelected();
}

void UIEndMenu::OnClick(UISelectable* which)
{
    StageManager* stageManager = StageManager::GetFromScene(m_scene);
    if (stageManager == nullptr) return;

    if (which == m_continueButton)
    {
      stageManager->QuitGame(); 
    }
    else if (which == m_mainMenuButton)
    {
        stageManager->QuitScene();
    }
}

void UIEndMenu::OnPlayFadeIn()
{
    PlayFadeInAlone();

    UIObject* objects[] = {
        m_titleText, m_continueButton, m_mainMenuButton,
        m_group->GetCursor(), m_endFill
    };
    for (UIObject* object : objects)
    {
        object->PlayFadeIn();
    }
}

void UIEndMenu::OnPlayFadeOut()
{
    PlayFadeOutAlone();

    UIObject* objects[] = {
        m_titleText,  m_mainMenuButton,//m_continueButton,
        m_group->GetCursor(), m_endFill
    };
    for (UIObject* object : objects)
    {
        object->PlayFadeOut();
    }
}

void UIEndMenu::OnFadeOutEnd(UIObject* which)
{
}

void UIEndMenu::InitFadeAnim()
{
    UIFadeDef fadeDef;
    fadeDef.Reset(0.5f);

    SetFadeInAnimation(fadeDef);
    SetFadeOutAnimation(fadeDef);
    SetFadeChildren(false);

    fadeDef.Reset(0.5f);
    fadeDef.fadeOpacity = true;
    fadeDef.shift = b2Vec2(0.f, 10.f);

    m_titleText->SetFadeInAnimation(fadeDef);
    m_continueButton->SetFadeInAnimation(fadeDef);
    m_mainMenuButton->SetFadeInAnimation(fadeDef);
    m_group->GetCursor()->SetFadeInAnimation(fadeDef);

    fadeDef.Reset(0.5f);
    fadeDef.fadeOpacity = true;
    fadeDef.shift = b2Vec2(0.f, -10.f);

    m_titleText->SetFadeOutAnimation(fadeDef);
    m_continueButton->SetFadeOutAnimation(fadeDef);
    m_mainMenuButton->SetFadeOutAnimation(fadeDef);
    m_group->GetCursor()->SetFadeOutAnimation(fadeDef);

    fadeDef.Reset(0.5f);
    fadeDef.fadeOpacity = true;
    m_endFill->SetFadeInAnimation(fadeDef);
    m_endFill->SetFadeOutAnimation(fadeDef);
}
