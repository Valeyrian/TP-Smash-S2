#pragma once
/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#pragma once

#include "GameSettings.h"
#include "GameCommon.h"
#include "UIDefaultButton.h"

class UIEndMenu : public UIObject, public UISelectableListener
{
public:
    UIEndMenu(Scene* scene);

    virtual void OnClick(UISelectable* which) override;

protected:
    virtual void OnPlayFadeIn() override;
    virtual void OnPlayFadeOut() override;
    virtual void OnFadeOutEnd(UIObject* which) override;

private:
    UIText* m_titleText;
    // Player 1 stats //damage gived taked fall count, ko count
    UIText* m_Result;
  
    UIText* m_damageGived1;
    UIText* m_damageGived2;

    UIText* m_damagetake1;
    UIText* m_damagetake2;

    UIText* m_fallCount1;
    UIText* m_fallCount2;

    UIText* m_koCount1;
    UIText* m_koCount2;
    
    UIText* m_DamageGivedTitle;
    UIText* m_DamageTakeTitle;
    UIText* m_FallCountTitle;
    UIText* m_KoCountTitle;






    UIFillRect* m_endFill;
    UISelectableGroup* m_group;

    UIDefaultButton* m_mainMenuButton;
    UIDefaultButton* m_continueButton;

    void InitFadeAnim();
};