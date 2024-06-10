/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "FireWarrior.h"

FireWarrior::FireWarrior(Scene *scene, const PlayerConfig *config, PlayerStats *stats) :
    Player(scene, config, stats)
{
    SetName("FireWarrior");
    AssetManager *assets = scene->GetAssetManager();

    SpriteSheet *spriteSheet = nullptr;
    SpriteGroup *spriteGroup = nullptr;
    SpriteAnim *anim = nullptr;

    spriteSheet = assets->GetSpriteSheet(SHEET_FIRE_WARRIOR);

    // Animation "Idle"
    spriteGroup = spriteSheet->GetGroup("Idle");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Idle", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

    // TODO : Animation "Run"
    
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

    // Animation AttackAir
    spriteGroup = spriteSheet->GetGroup("AttackAir");
    AssertNew(spriteGroup); 
    anim = m_animator.CreateAnimation("AttackAir", spriteGroup);
    anim->SetCycleCount(1); 
    anim->SetFPS(attackFPS); 

  //ici l
     
    spriteGroup = spriteSheet->GetGroup("Roll");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Roll", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(15.f);

    // farAttack
    spriteGroup = spriteSheet->GetGroup("CastSpell");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("CastSpell", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(15.f);




    // TODO : Anmisation "Defend"

    // TODO : Anmisation "TakeHit"

    spriteGroup = spriteSheet->GetGroup("TakeHit");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("TakeHit", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(15.f);

    // TODO : Décommenter pour lancer l'animation initiale
    m_animator.PlayAnimation("Idle"); 

    // Physique
    m_accAir = 30.f;
    m_accGround = 60.f;
    m_maxSpeed = 10; // TODO : adapter

    // Render
    m_renderShift.Set(0.7f, 0.f);
}

FireWarrior::~FireWarrior()
{
}

void FireWarrior::Start()
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
    box.SetAsBox(0.6f, .85f, b2Vec2(-0.02f, 1.2), 0.f); //ici pour le rest

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


    //creation du projectile

    b2CircleShape fireball;
    fireball.m_p = b2Vec2(1, 1);
    fireball.m_radius = 1.f;

    fixtureDef.shape = &fireball;
    fixtureDef.density = 0.f;
    fixtureDef.friction = 0.f;
    fixtureDef.restitution = 0.f;
    fixtureDef.filter.categoryBits =  CATEGORY_PROJECTILE;
    fixtureDef.filter.maskBits = m_config->otherTeamMask;

}

void FireWarrior::OnStateChanged(Player::State state, Player::State prevState)
{
    Player::OnStateChanged(state, prevState);

    switch (state) // TODO : décommenter, compléter
    {
    case State::IDLE:        m_animator.PlayAnimation("Idle");  printf("Is Idle\n");       break;
    case State::RUN:         m_animator.PlayAnimation("Run");   printf("Is Running\n");        break;
    case State::ATTACK:      m_animator.PlayAnimation("Attack1"); printf("Is Attacking\n");      break;
    case State::JUMP:        m_animator.PlayAnimation("JumpUp");   printf("Is  Jumping\n");   break;
    case State::ROLLING:     m_animator.PlayAnimation("Roll");   printf("Is  Rolling\n");   break;
    case State::ATTACK_AIR:  m_animator.PlayAnimation("AttackAir");   printf("Is  Attacking in Air\n");   break;
    case State::FAR_ATTACK:  m_animator.PlayAnimation("CastSpell");   printf("Is  fireBalling\n");   break;
    case State::LAUNCHED:    m_animator.PlayAnimation("Roll");   printf("Is  launched\n");   break;





    // TODO : Gérer d'autres animations
    default:
        break;
    }
}

void FireWarrior::OnAnimationEnd(Animation *which, const std::string &name)
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
    
 if (name == "Roll")
    {
        m_delayLockRoll = 2;
        SetState(Player::State::IDLE);

    }
    else if (name == "AttackAir")
    {
       
            SetState(Player::State::IDLE);
            LockAttack(0.1f);
        
    }
    
}

void FireWarrior::OnFrameChanged(Animation *which, const std::string &name, int frameID)
{
    if (m_scene->GetUpdateMode() == Scene::UpdateMode::STEP_BY_STEP && GetPlayerID() == 0)
    {
        std::cout << "[OnFrameChanged] "
            << "Animation = " << name << ", "
            << "FrameID = " << frameID << std::endl;
    }

    m_autoVelocity = 0.f;

    QueryFilter filter(m_config->otherTeamMask | CATEGORY_ITEM);

    const float lockTime = -1.f;
    float s = m_facingRight ? 1.f : -1.f;

    if (name == "Attack1")
    {
        switch (frameID)
        {
            // TODO : Vitesse crédible
        case 0: m_autoVelocity = s * 1.0f; break;
        case 1: m_autoVelocity = s * 3.0f; break;
        case 2: m_autoVelocity = s * 3.0f; break;
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
            position += b2Vec2(s * 1.f, 1.f); 

            Damage damage;
            damage.amount = 3.f;


            // TODO : Verrouillage pour la victime

            damage.lockAttackTime = 10.5f * ATTACK_FRAME_TIME;

            // TODO : adapter la zone d'attaque
            bool hit = AttackCircle(damage, filter, position, 1.f) ;

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

            b2Vec2 vertices[6] = { // C'est cadeau
                position + b2Vec2(s * -0.4f, 2.6f),
                position + b2Vec2(s * 1.15f, 1.5f),
                position + b2Vec2(s * 1.0f, 0.5f),
                position + b2Vec2(s * 2.f, 0.5f),
                position + b2Vec2(s * 2.f, 1.5f),
                position + b2Vec2(s * 0.9f, 2.3f)
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
        default: break; }

        // TODO : déclenchement de l'attaque avec smash
        if (frameID == 2)
        {
            PlaySFXAttack(SFX_WHOOSH);

            b2Vec2 position = GetPosition();
            position += b2Vec2(s * 1.7f, 1.0f);

            Damage damage;
            damage.amount = 6.f;

            damage.hasEjection = true;

            damage.ejection = b2Vec2(s *8.0f, 8.f); // TODO : param�tres suppl�mentaire // TODO : angle d'éjection fonction de la position du joueur
          
            //damage.ejection = GetPosition; // TODO : param�tres suppl�mentaire // TODO : angle d'éjection fonction de la position du joueur

            // TODO : Zone de collision adapt�e
            bool hit = AttackBox(damage, filter, position, 0.8f, 0.1f, 0.f);

        }
        
        }
        else if (name == "Roll")
        {
            printf("ici \n");
            switch (frameID)
            {
            case 0: m_autoVelocity = s *  2.0f; break;
            case 2: m_autoVelocity = s * 6.0f; break;
            case 4: m_autoVelocity = s * 4.0f; break;
            case 6: m_autoVelocity = s * 2.0f; break;
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
                position += b2Vec2(s * 0.75f, 1.2f);

                Damage damage;
                damage.amount = 5.f;


                // TODO : Verrouillage pour la victime

                damage.lockAttackTime = 10.5f * ATTACK_FRAME_TIME;

                // TODO : adapter la zone d'attaque
                bool hit = AttackCircle(damage, filter, position, 1.f);

                PlaySFXHit(hit, SFX_HIT);
            }
            }
    // TODO : D'autres évènement sur frames ?
}
