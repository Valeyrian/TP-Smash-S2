#pragma once
#pragma once
#pragma once
/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#pragma once

#include "Terrain.h"

class CityD : public Terrain
{
public:
    CityD(Scene* scene, int layer, b2Vec2 StartPos);
    virtual ~CityD();
    virtual void FixedUpdate() override;

    void SetTargetPosition(b2Vec2 position, float smoothTime, float maxSpeed);
    void SetTargetAngle(float angle, float smoothTime, float maxSpeed);
    void ApplyExternalVelocity();
    void PlatformDeplacement();

    const std::set<GameBody*>& GetBodies() const;
    void AddGameBody(GameBody* gameBody);
    b2Vec2 m_InitPosG;
    b2Vec2 m_startPosG;

    virtual void Start() override;

protected:
    std::set<GameBody*>m_bodies;

    b2Vec2 m_positionTarget;
    float m_positionSmoothTime;
    float m_positionMaxSpeed;

    float m_angleTarget;
    float m_angleSmoothTime;
    float m_angleMaxSpeed;
    int m_DeplacementState;
    float m_TimePhaseOne;
    void InitTiles();
};

inline void CityD::AddGameBody(GameBody* gameBody)
{
    m_bodies.insert(gameBody);
}
