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


    // TODO : Animations Attack2 et Attack3 et Attack 4

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

    spriteGroup = spriteSheet->GetGroup("Attack4");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Attack4", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(attackFPS);

    
    spriteGroup = spriteSheet->GetGroup("Slide");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Slide", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(15.f);

    // Animation AttackAir
    spriteGroup = spriteSheet->GetGroup("AttackAir");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("AttackAir", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(attackFPS);

    // Smash
    spriteGroup = spriteSheet->GetGroup("SmashStart");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("SmashStart", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(attackFPS);

    spriteGroup = spriteSheet->GetGroup("SmashHold");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("SmashHold", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(attackFPS);

    spriteGroup = spriteSheet->GetGroup("SmashRelease");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("SmashRelease", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(attackFPS);

     m_animator.PlayAnimation("Idle");


    // Physique
    m_accAir = 30.f;
    m_accGround = 60.f;
    m_maxSpeed = 8.f;
    m_countSmash = 1.f;
    m_delayAnimationLight = 1;

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
    fixtureDef.density = 1.f; //1
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
    fixtureDef.density = 2.f;//2
    fixtureDef.friction = 0.2f; //0.2
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
    case State::IDLE:        m_animator.PlayAnimation("Idle");  printf("Is Idle\n");                        break;
    case State::RUN:         m_animator.PlayAnimation("Run");   printf("Is Running\n");                     break;
    case State::ATTACK:      m_animator.PlayAnimation("Attack1"); printf("Is Attacking\n");                 break;
    case State::JUMP:        m_animator.PlayAnimation("JumpUp");   printf("Is  Jumping\n");                 break;
    case State::ROLLING:     m_animator.PlayAnimation("Slide");   printf("Is  Sliding (=rolling)\n");       break;
    case State::ATTACK_AIR:  m_animator.PlayAnimation("AttackAir");   printf("Is  Attacking in Air\n");     break;
    case State::SMASH_START:    m_animator.PlayAnimation("SmashStart"); printf("start smash\n");            break;
    case State::SMASH_HOLD:     m_animator.PlayAnimation("SmashHold"); printf("hold smash\n");              break;
    case State::SMASH_RELEASE:  m_animator.PlayAnimation("SmashRelease"); printf("smashiiing hold\n");      break;
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
        if (GetPlayerInput().attackDown) 
        {
            m_animator.PlayAnimation("Attack4");

        }
        else 
        {
            SetState(Player::State::IDLE); 
            LockAttack(0.1f); 
        }
    }

    else if (name == "Attack4")
    {

        SetState(Player::State::IDLE);
        LockAttack(0.25f);

    }


    if (name == "Slide")
    {
        m_delayLockRoll = 1;
        SetState(Player::State::IDLE);

    }
    else if (name == "AttackAir")
    {

        SetState(Player::State::IDLE);
        LockAttack(0.1f);

    }
    else if (name == "SmashStart")
    {
        if (GetPlayerInput().smashDown)
        {
            m_animator.PlayAnimation("SmashHold");

        }
        else
        {
            m_animator.PlayAnimation("SmashHold");
        }
    }

    else if (name == "SmashHold")
    {
        if (GetPlayerInput().smashDown)
        {
            m_animator.PlayAnimation("SmashHold");
            m_countSmash += 0.05f;
            m_delayLock = 1;
            m_delayAnimationLight++;
            if (m_delayAnimationLight % 34 == 2)
                SmashParticleLight();
        }
        else
        {
            m_animator.PlayAnimation("SmashRelease");
            m_delayLock = 1;
        }
    }
    else if (name == "SmashRelease")
    {

        SetState(Player::State::IDLE);
        LockAttack(0.5f);
        m_countSmash = 1;
        m_delayLock = 0.5;
        m_delayAnimationLight = 1;
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

            damage.hasEjection = true;

            damage.ejection = b2Vec2(s * 2.0f, 1.0f); // TODO : param?tres suppl?mentaire // TODO : angle d'éjection fonction de la position du joueur




            // TODO : Verrouillage pour la victime
     //       damage.lockAttackTime = 10.5f * ATTACK_FRAME_TIME;

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

            b2Vec2 vertices[] = { 
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
        case 1: m_autoVelocity = s * 6.0f; break;
        case 2: m_autoVelocity = s * 4.0f; break;
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
            //damage.hasEjection = true;

            //damage.ejection = b2Vec2(s * 25.0f, 5.0f); // TODO : param?tres suppl?mentaire // TODO : angle d'éjection fonction de la position du joueur




            // TODO : Zone de collision adapt?e
            bool hit = AttackBox(damage, filter, position, 1.85f, 0.7f, 0.f);

        }

    }

    else if (name == "Attack4")
    {

        // TODO : autoVelocité
        switch (frameID) {     // TODO : Vitesse crédible
        case 0: m_autoVelocity = s * -2.0f; break;
        case 1: m_autoVelocity = s * 1.0f; break;
        case 2: m_autoVelocity = s * 4.0f; break;
        case 3: m_autoVelocity = s * 0.0f; break;
        case 4: m_autoVelocity = s * -1.0f; break;
        case 5: m_autoVelocity = s * 0.0f; break;
        case 6: m_autoVelocity = s * 2.0f; break;
        case 9: m_autoVelocity = s * 1.0f; break;



        default: break;
        }

        // TODO : déclenchement de l'attaque avec smash
        if (frameID == 2)
        {
            PlaySFXAttack(SFX_WHOOSH);

            b2Vec2 position = GetPosition();
            position += b2Vec2(s * 1.5f, 1.17f);

            Damage damage;
            damage.amount = 2.f;

            damage.hasEjection = true;

            damage.ejection = b2Vec2(s * 2.0f, 1.0f);

            // TODO : Zone de collision adapt?e
            bool hit = AttackBox(damage, filter, position, 1.2f, 0.4f, 0.f);
        }

        if (frameID == 6)
        {
            PlaySFXAttack(SFX_WHOOSH);

            b2Vec2 position = GetPosition();
            position += b2Vec2(s * 1.55f, 0.9f);

            Damage damage;
            damage.amount = 2.f;

            damage.hasEjection = true;

            damage.ejection = b2Vec2(s * 2.0f, 1.0f);

            // TODO : Zone de collision adapt?e
            bool hit = AttackBox(damage, filter, position, 1.2f, 0.4f, 0.f);
        }
        if (frameID == 9)
        {
            PlaySFXAttack(SFX_WHOOSH);

            b2Vec2 position = GetPosition();
            position += b2Vec2(s * 1.55f, 1.2f);

            Damage damage;
            damage.amount = 1.f;

            damage.hasEjection = true;

            damage.ejection = b2Vec2(s * 2.0f, 1.0f);

            // TODO : Zone de collision adapt?e
            bool hit = AttackBox(damage, filter, position, 1.2f, 0.4f, 0.f);
        }
        if (frameID == 10)
        {
            PlaySFXAttack(SFX_WHOOSH);

            b2Vec2 position = GetPosition();
            position += b2Vec2(s * 1.55f, 1.17f);;

            Damage damage;
            damage.amount = 1.f;
            damage.hasEjection = true;

            damage.ejection = b2Vec2(s * 4.0f, 1.0f);



            // TODO : Zone de collision adapt?e
            bool hit = AttackBox(damage, filter, position, 1.2f, 0.4f, 0.f);
        }
        

     }


    else if (name == "Slide")
    {
        printf("ici \n");
        switch (frameID)
        {
        case 0: m_autoVelocity = s * 4.0f; break;
        case 1: m_autoVelocity = s * 4.0f; break;
        case 2: m_autoVelocity = s * 6.0f; break;
        case 3: m_autoVelocity = s * 8.0f; break;
        case 4: m_autoVelocity = s * 8.0f; break;
        case 5: m_autoVelocity = s * 6.0f; break;
        case 6: m_autoVelocity = s * 4.0f; break;
        case 7: m_autoVelocity = s * 4.0f; break;
        default:
            break;
        }

        }
    else if (name == "AttackAir")
    {


        if (frameID == 1)
        {
            PlaySFXAttack(SFX_WHOOSH);
        }
        if (frameID == 2)
        {
            // TODO : apdapter le centre de l'attaque
            b2Vec2 position = GetPosition();
            position += b2Vec2(s * 0.f, 1.08f);

            Damage damage;
            damage.amount = 5.f;

            damage.hasEjection = true;

            damage.ejection = b2Vec2(s * 4.0f, 5.0f);

            // TODO : Verrouillage pour la victime

            damage.lockAttackTime = 10.5f * ATTACK_FRAME_TIME;

            // TODO : adapter la zone d'attaque
            bool hit = AttackBox(damage, filter, position, 1.8f, 0.6f, 0.f);

            PlaySFXHit(hit, SFX_HIT);
        }
    }
    else if (name == "SmashRelease")
    {
        b2Vec2 position = GetPosition();
        position += b2Vec2(s * 0.2f, 2.f);

        Damage damage;
        damage.amount = 4.f * m_countSmash;

        // TODO : Verrouillage pour la victime

        damage.lockAttackTime = 10.5f * ATTACK_FRAME_TIME;

        if (frameID == 1)
        {
           
        }
        if (frameID == 2)
        {
            
        }if (frameID == 3)
        {
            
        }if (frameID == 4)
        {
            
        }if (frameID == 5)
        {
            
        }if (frameID == 6)
        {
            
        }if (frameID == 7)
        {
            
        }if (frameID == 8)
        {
            
        }if (frameID == 9)
        {
            
        }
        if (frameID == 10)
        {
            PlaySFXAttack(SFX_WHOOSH);
            position -= b2Vec2(0.f, 0.15f);


            bool hit = AttackBox(damage, filter, position, 1.2f, 1.8f, 0.f);
        }
        if (frameID == 11)
        {
            PlaySFXAttack(SFX_WHOOSH);
            position -= b2Vec2(0.f, 0.2f);
            damage.hasEjection = true;

            damage.ejection = b2Vec2(s * 8.0f, 5.f);

            bool hit = AttackBox(damage, filter, position, 1.2f, 1.8f, 0.f);

            
        }

    }
}

void Player::SmashParticleLight()
{
    AssetManager* assets = m_scene->GetAssetManager();
    SpriteSheet* spriteSheet = assets->GetSpriteSheet(SHEET_VFX_SMASHLIGHT);
    AssertNew(spriteSheet);
    SpriteGroup* spriteGroup = spriteSheet->GetGroup("SmashPreparationLight");
    AssertNew(spriteGroup);

    b2Vec2 position = GetPosition();

    position.x += 0.f;
    position.y += 3.8f;
    //position.x += Random::RangeF(-0.2f, 0.2f);
    //position.y += Random::RangeF(-0.2f, 0.2f);

    Particle* particle = m_scene->GetParticleSystem(LAYER_PARTICLES)
        ->EmitParticle(spriteGroup, position, 40.f);

    SpriteAnim* anim = particle->GetSpriteAnimation();
    anim->SetFPS(15.f);
    anim->SetCycleCount(1);

    particle->SetLifetimeFromAnim();
    particle->SetOpacity(0.8f);
    //particle->SetFlip(SDL_FLIP_HORIZONTAL);
    //particle->SetAngularVelocity(180.f);
}



