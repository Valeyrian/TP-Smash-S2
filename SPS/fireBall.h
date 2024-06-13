#pragma once
#pragma once
/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#pragma once

#include "GameCommon.h"
#include "GameSettings.h"
#include "Damager.h"
#include "Player.h"


class fireBall : public Damager
{
public:
    fireBall(Scene* scene, int s, int playerID);
    virtual ~fireBall();

    virtual void Start() override;
    virtual void Render() override;
    virtual void FixedUpdate() override;

    float timeBeforeExplode;
    virtual void PlaySFXAttak(SoundID sound);

    void OnCollisionEnter(GameCollision& collision);


protected:
    bool m_used;
    Animator m_animator;
    int sens;

};
