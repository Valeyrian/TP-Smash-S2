#pragma once
/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#pragma once

#include "GameSettings.h"
#include "GameCommon.h"
#include "Damager.h"

class Bomb : public Damager
{
public:
    Bomb(Scene* scene);
    virtual ~Bomb();

    virtual void Start() override;
    virtual void Render() override;
    virtual void FixedUpdate() override;

    virtual bool TakeDamage(const Damage& damage, Damager* damager);
    float timeBeforeExplode;
    virtual void Explode();

protected:
    bool m_used;
    Animator m_animator;
   
};
