/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#pragma once

#include "GameSettings.h"
#include "GameCommon.h"
#include "Damager.h"

extern const float ATTACK_FRAME_TIME;

class PlayerAI;
class Player : public Damager, public AnimationListener
{
public:
    Player(Scene *scene, const PlayerConfig *config, PlayerStats *stats);
    virtual ~Player();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void FixedUpdate() override;

    enum class State
    {

        IDLE, RUN, JUMP, FALL, ATTACK, ATTACK2, ATTACK3, DEFEND, TAKE_DAMAGE, LAUNCHED, ATTACK_AIR, SMASH_START, SMASH_HOLD, SMASH_RELEASE, ROLLING, DASH, SPECIAL,FAR_ATTACK

    };

    virtual void OnCollisionStay(GameCollision &collision) override;
    virtual bool TakeDamage(const Damage &damage, Damager *damager) override;

    virtual void OnStateChanged(Player::State state, Player::State prevState);
    void Heal(float amount); // TODO : decommenter
    void GetDownJumpCount(int ckeck);


    const PlayerConfig *GetConfig() const;
    Player::State GetState() const;
    float GetEjectionScore() const;
    const PlayerStats *GetStats() const;


    void AddExternalVelocity(b2Vec2 externalVelocity);
    
    void AddDamageGive(float DamageAmount);

    void PlaySFXAttack(int soundID);
    void PlaySFXHit(bool hit, int soundID);
    Color getDamageColor();

    

    float m_countJump;


protected:
    const PlayerConfig *m_config;
    PlayerStats *m_stats;

    friend class PlayerAI;
    PlayerAI *m_ai;
    
    b2Vec2 m_externalVelocity;
    b2Vec2 m_renderShift;


    Animator m_animator;

    Animator m_shieldAnimator;
    Damager *m_lastDamager;

    float m_delayEarlyJump;
    float m_delayAttack;
    float m_delaySmash;
    float m_delaySpecial;
    float m_delayLock;
    float m_delayLockAttack;
    float m_delayRoll;
    float m_delayLockRoll;
    float m_delayLockFarAttack;
    float m_askedFarAttack;
    float m_delayJumpPotionleft;
    float m_hasToucjedFloor;
 


    float m_ejectionScore;
    float m_hDirection;

    enum class AttackType
    {
        COMBO, SPECIAL, SMASH, NONE
    };
    AttackType m_attackType;

    bool m_isGrounded;
    bool m_wasGrounded;

    bool m_facingRight;
    bool m_defend;
    bool m_launchBegins;
    bool m_inContact;
    bool m_hasAutoVelocity;
    
    float m_accGround;
    float m_accAir;
    float m_maxSpeed;
    float m_hVelocity;
    float m_autoVelocity;

    float m_jumpImpulse;
    float m_countSmash;
    int m_delayAnimation;
    int m_delayAnimationLight;

    b2Fixture *m_feetFixture;
    b2Fixture *m_bodyFixture;
    b2Vec2 m_ejection;

    void SetState(Player::State state);

    void FixedUpdateIsGrounded();
    void FixedUpdateState();
    void FixedUpdateAutoVelocity();
    void FixedUpdatePhysics();

    const PlayerInput &GetPlayerInput() const;

    void OnPlayerKO();
    void Respawn();
    void LockAttack(float lockTime);
    bool IsAttacking() const;
    bool CanAttack() const;

    void EmitEjectionParticles();
    void EmitSmallDust(float xShift);
    void EmitDustImpact();
    void EmitDustJump();
    void EmitHitParticle();
    void SmashParticle();
    void SmashParticleLight();


private:
    State m_state;
};

inline bool Player::IsAttacking() const
{
    return (m_state == State::ATTACK || m_state == State::ATTACK_AIR || m_state == State::SMASH_START || m_state == State::SMASH_HOLD || m_state == State::SMASH_START);//|| m_state == State::SPECIAL);
}

inline bool Player::CanAttack() const
{
    return m_delayLockAttack < 0.f;
}

inline const PlayerConfig *Player::GetConfig() const
{
    return m_config;
}

inline Player::State Player::GetState() const
{
    return m_state;
}


inline float Player::GetEjectionScore() const
{
    return m_ejectionScore;
}

inline const PlayerStats *Player::GetStats() const
{
    return m_stats;
}

inline void Player::AddExternalVelocity(b2Vec2 externalVelocity)
{
    if (m_isGrounded)
        m_externalVelocity += externalVelocity;
}
    
inline void Player::AddDamageGive(float DamageAmount) 
{
    m_stats->damageGiven += DamageAmount;
}

inline Color Player::getDamageColor()
{
    if (m_ejectionScore >= 0 && m_ejectionScore <= 15)
        return Colors::White;
    else if (m_ejectionScore > 15 && m_ejectionScore <= 30)
        return Colors::Yellow;
    else if (m_ejectionScore > 30 && m_ejectionScore <= 45)
        return Colors::Orange;
    else if (m_ejectionScore > 45 && m_ejectionScore <= 70)
        return Colors::Magenta;
    else if (m_ejectionScore > 70 && m_ejectionScore <= 85)
        return Colors::Purple;
    else if (m_ejectionScore > 85 && m_ejectionScore <= 99)
        return Colors::Brown;
    else if (m_ejectionScore > 99)
        return Colors::Red;
}
