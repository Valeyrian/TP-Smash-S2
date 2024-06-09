/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "LightningWarrior.h"

LightningWarrior::LightningWarrior(Scene *scene, const PlayerConfig *config, PlayerStats *stats) :
    Player(scene, config, stats)
{
    SetName("LightningWarrior");
    AssetManager *assets = scene->GetAssetManager();
    SpriteSheet *spriteSheet = nullptr;
    SpriteGroup *spriteGroup = nullptr;
    SpriteAnim *anim = nullptr;

    spriteSheet = assets->GetSpriteSheet(SHEET_LIGHTNING_WARRIOR);

    // Animation "Idle"
    spriteGroup = spriteSheet->GetGroup("Idle");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Idle", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    // TODO : Toutes les animations
    // Animation "Run"
    spriteGroup = spriteSheet->GetGroup("Run");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Run", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    // TODO : Animation "JumpUp"
    spriteGroup = spriteSheet->GetGroup("JumpUp");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("JumpUp", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    // TODO : Animation "JumpTop"

    spriteGroup = spriteSheet->GetGroup("JumpTop");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("JumpTop", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    // TODO : Animation "JumpDown"

    spriteGroup = spriteSheet->GetGroup("JumpDown");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("JumpDown", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    // TODO : Animation "Attack" (c'est fait, c'est cadeau)
    const float attackFPS = 1.0f / (float)ATTACK_FRAME_TIME;

    spriteGroup = spriteSheet->GetGroup("Attack1");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Attack1", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(attackFPS);


    // TODO : Animations Attack2 et Attack3

    spriteGroup = spriteSheet->GetGroup("Attack2");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Attack2", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(attackFPS);


    spriteGroup = spriteSheet->GetGroup("Attack3");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Attack3", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(attackFPS);

   


     m_animator.PlayAnimation("Idle");


    // Physique
    m_accAir = 30.f;
    m_accGround = 60.f;
    m_maxSpeed = 8.f;

    // Render
    m_renderShift.Set(0.4f, -0.75f);
}

LightningWarrior::~LightningWarrior()
{
}

void LightningWarrior::Start()
{
    Player::Start();

    b2World &world = m_scene->GetWorld();
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = GetStartPosition();
    bodyDef.fixedRotation = true;
    bodyDef.allowSleep = false;
    bodyDef.bullet = true;

    b2Body *body = CreateBody(&bodyDef);

    // TODO : Modifer les paramètres
    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.75f, b2Vec2(0.f, 1.1f), 0.f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.f;
    fixtureDef.restitution = 0.f;
    fixtureDef.filter.categoryBits = m_config->teamMask;
    fixtureDef.filter.maskBits = m_config->otherTeamMask | CATEGORY_PROJECTILE;

    m_bodyFixture = CreateFixture(&fixtureDef);

    // TODO : Modifer les paramètres
    b2CircleShape circle;
    circle.m_p = b2Vec2(0.0f, 0.5f); //ici pour le cercle
    circle.m_radius = 0.5f;

    fixtureDef.shape = &circle;
    fixtureDef.density = 2.f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.f;
    fixtureDef.filter.categoryBits = m_config->teamMask;
    fixtureDef.filter.maskBits = CATEGORY_TERRAIN;

    m_feetFixture = CreateFixture(&fixtureDef);
}

void LightningWarrior::OnStateChanged(Player::State state, Player::State prevState)
{
    Player::OnStateChanged(state, prevState);

    switch (state)
    {
    case State::IDLE:        m_animator.PlayAnimation("Idle");  printf("Is Idle\n");       break;
    case State::RUN:         m_animator.PlayAnimation("Run");   printf("Is Running\n");        break;
    case State::ATTACK:      m_animator.PlayAnimation("Attack1"); printf("Is Attacking\n");      break;
    case State::JUMP:      m_animator.PlayAnimation("JumpUp");   printf("Is  Jumping\n");   break;
    default:
        break;
    }
}

void LightningWarrior::OnAnimationEnd(Animation *which, const std::string &name)
{
    if (m_scene->GetUpdateMode() == Scene::UpdateMode::STEP_BY_STEP && GetPlayerID() == 0)
    {
        std::cout << "[OnAnimationEnd] "
            << "Animation = " << name << std::endl;
    }

    m_autoVelocity = 0.0f;

    if (name == "Attack1")
    {
        if (GetPlayerInput().attackDown)
        {
            m_animator.PlayAnimation("Attack2");

        }
        else
        {
            SetState(Player::State::IDLE);
            LockAttack(0.1f);
        }
    }

    // TODO : Enchainement des Attack2, Attack3
    else if (name == "Attack2")
    {
        if (GetPlayerInput().attackDown)
        {
            m_animator.PlayAnimation("Attack3");

        }
        else
        {
            SetState(Player::State::IDLE);
            LockAttack(0.1f);
        }
    }

    else if (name == "Attack3")
    {

        SetState(Player::State::IDLE);
        LockAttack(0.25f);

    }

}

void LightningWarrior::OnFrameChanged(Animation *which, const std::string &name, int frameID)
{
    if (m_scene->GetUpdateMode() == Scene::UpdateMode::STEP_BY_STEP && GetPlayerID() == 0)
    {
        std::cout << "[OnFrameChanged] "
            << "Animation = " << name << ", "
            << "FrameID = " << frameID << std::endl;
    }

    m_autoVelocity = 0.f;

    QueryFilter filter;
    filter.maskBits = m_config->otherTeamMask | CATEGORY_ITEM;
    filter.solidOnly = true;

    const float lockTime = 0.2f;
    float s = m_facingRight ? 1.f : -1.f;

    if (name == "Attack1")
    {
        switch (frameID)
        {
            // TODO : Vitesse crédible
        case 0: m_autoVelocity = s * 1.0f; break;
        case 1: m_autoVelocity = s * 2.0f; break;
        case 2: m_autoVelocity = s * 2.0f; break;
        case 3: m_autoVelocity = s * 1.0f; break;
        default: break;
        }

        if (frameID == 1)
        {
            PlaySFXAttack(SFX_WHOOSH);
        }
        if (frameID == 2)
        {
            // TODO : apdapter le centre de l'attaque
            b2Vec2 position = GetPosition();
            position += b2Vec2(s * 1.2f, 1.17f);

            Damage damage;
            damage.amount = 3.f;


            // TODO : Verrouillage pour la victime

            damage.lockAttackTime = 10.5f * ATTACK_FRAME_TIME;

            // TODO : adapter la zone d'attaque
            bool hit = AttackBox(damage, filter, position, 1.3f, 0.3f, 0.f); 

            PlaySFXHit(hit, SFX_HIT);
        }
    }
    else if (name == "Attack2")
    {
        // TODO : autoVelocité

        // TODO : déclenchement de l'attaque
        if (frameID == 2)
        {
            PlaySFXAttack(SFX_WHOOSH);

            b2Vec2 position = GetPosition();

            Damage damage;
            damage.amount = 3.f;
            damage.lockTime = lockTime;
            // TODO : paramètres supplémentaires ?

            b2Vec2 vertices[] = { // C'est cadeau
                position + b2Vec2(s * 0.7f, 2.2f), //1
                position + b2Vec2(s * 1.15f, 1.5f),//
                position + b2Vec2(s * 1.3f, 0.1f), //5
                position + b2Vec2(s * 2.2f, 0.1f),  //4
                position + b2Vec2(s * 1.2f, 1.5f),  //3
                position + b2Vec2(s * 1.5f, 1.5f)  //2
                
            };
            bool hit = AttackPolygon(damage, filter, vertices, 6);
            PlaySFXHit(hit, SFX_HIT);
        }
    }
    else if (name == "Attack3")
    {

        // TODO : autoVelocité
        switch (frameID) {     // TODO : Vitesse crédible
        case 0: m_autoVelocity = s * -2.0f; break;
        case 1: m_autoVelocity = s * 2.0f; break;
        case 2: m_autoVelocity = s * 10.0f; break;
        case 3: m_autoVelocity = s * 2.0f; break;
        default: break;
        }

        // TODO : déclenchement de l'attaque avec smash
        if (frameID == 2)
        {
            PlaySFXAttack(SFX_WHOOSH);

            b2Vec2 position = GetPosition();
            position += b2Vec2(s * 0.5f, 1.0f);

            Damage damage;
            damage.amount = 6.f;
            damage.hasEjection = true;

            damage.ejection = b2Vec2(s * 25.0f, 5.0f); // TODO : param?tres suppl?mentaire // TODO : angle d'éjection fonction de la position du joueur




            // TODO : Zone de collision adapt?e
            bool hit = AttackBox(damage, filter, position, 1.85f, 0.7f, 0.f);

        }
    }
}
