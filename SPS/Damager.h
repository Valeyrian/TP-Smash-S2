/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#pragma once

#include "GameSettings.h"
#include "GameCommon.h"

class Damage
{
public:
    Damage();
    virtual ~Damage();

    float amount;
    float lockTime;
    float lockAttackTime;
    bool hasEjection;
    b2Vec2 ejection;

    bool isfromBomb;
    b2Vec2 bombCenter;
};

class Damager : public GameBody
{
public:
    Damager(Scene *scene, int layer);
    virtual ~Damager();

    // Prend des d�gats
    virtual bool TakeDamage(const Damage &damage, Damager *damager);

    int GetPlayerID() const;
    const PlayerConfig *GetPlayerConfig() const;

    // Zone dans laquelle on donnera des degats
    // Appelle un takeDamage des objets rp�sents dans la zone
    bool AttackCircle(
        const Damage &damage, const QueryFilter &filter,
        b2Vec2 center, float radius
    );
    bool AttackPolygon(
        const Damage &damage, const QueryFilter &filter,
        const b2Vec2 *vertices, int vertexCount
    );
    bool AttackBox(
        const Damage &damage, const QueryFilter &filter,
        b2Vec2 center, float hx, float hy, float angleDeg
    );
protected:
    void SetPlayerID(int playerID);

private:
    int m_playerID; // Le playerId de celui qui a activ� l'item (-1 par d�faut) 
};

inline int Damager::GetPlayerID() const
{
    return m_playerID;
}

inline void Damager::SetPlayerID(int playerID)
{
    m_playerID = playerID;
}
