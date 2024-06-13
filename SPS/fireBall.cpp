/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "fireBall.h"
#include "Player.h"
#include "StageManager.h"



fireBall::fireBall(Scene* scene, int s, int playerID) :
    Damager(scene, LAYER_TERRAIN), m_used(false)
{     b2Fixture *m_bodyFixture;


    SetPlayerID(playerID);
    AssetManager* assets = scene->GetAssetManager();
    SpriteSheet* spriteSheet = assets->GetSpriteSheet(SHEET_FIREBALL);
    SpriteGroup* spriteGroup = nullptr;
    SpriteAnim* anim = nullptr;
    sens = s;


    spriteGroup = spriteSheet->GetGroup("fireBall");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("fireBall", spriteGroup);
    anim->SetCycleCount(-1);
    anim->SetFPS(15.f);

   m_animator.PlayAnimation("fireBall");

    // TODO : charger l'animation et la lancer
}

fireBall::~fireBall()
{
}

void fireBall::Start()
{

    b2Fixture* m_bodyFixture;

    b2World& world = m_scene->GetWorld();
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = GetStartPosition();
    bodyDef.position.y += 0.5;
    bodyDef.fixedRotation = false;
    bodyDef.allowSleep = true;
    bodyDef.angularDamping = 0.05f;
    bodyDef.linearDamping = 0.05f;

    b2Body* body = CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;


    b2CircleShape circle;
    circle.m_p = b2Vec2(0.0f, 0.f); //ici pour le cercle
    circle.m_radius = .25f; // 0.5

    fixtureDef.shape = &circle;
    fixtureDef.density = 2.f;
    fixtureDef.friction = 1.f;
    fixtureDef.restitution = 0.5f;
    fixtureDef.filter.maskBits = CATEGORY_PROJECTILE;
    fixtureDef.filter.maskBits = CATEGORY_ALL_TEAMS;

    m_bodyFixture = CreateFixture(&fixtureDef);

    
}

void fireBall::Render()
{
    Camera* camera = m_scene->GetActiveCamera();
    b2Body* body = GetBody();

    if (body == nullptr) return;

    // TODO : decommenter  pour afficher la Bomb
    const float angle = body->GetAngle() / b2_pi * 180.f;
    SDL_Texture* texture = m_animator.GetTexture();
    if (sens == 1 && texture)
    {
        const SDL_Rect* rect = m_animator.GetSourceRect();
        b2Vec2 position = GetInterpolatedPosition();
        SDL_FRect frect = { 0 };
        camera->WorldToView(position, rect, 22.f, frect);
        RenderCopyExF(
            g_renderer, texture, rect, &frect, Anchor::CENTER,
            -angle, b2Vec2(0.f, 0.f), SDL_FLIP_NONE
        );
    }
    else if (sens == -1 && texture)
    {
        const SDL_Rect* rect = m_animator.GetSourceRect();
        b2Vec2 position = GetInterpolatedPosition();
        SDL_FRect frect = { 0 };
        camera->WorldToView(position, rect, 22.f, frect);
        RenderCopyExF(
            g_renderer, texture, rect, &frect, Anchor::CENTER,
            -angle, b2Vec2(0.f, 0.f), SDL_FLIP_HORIZONTAL
        );
    }
}

void fireBall::FixedUpdate()
{
    //printf("in fireeeeeeeeee\n");

    b2Body* body = GetBody();
    b2Vec2 velocity = body->GetLinearVelocity();
    b2Vec2 position = body->GetPosition();


    body->SetLinearVelocity(b2Vec2(sens * 20.f, 0.f));
}







void fireBall::PlaySFXAttak(SoundID  sound)
{
    AssetManager* assets = m_scene->GetAssetManager();
    float volume = Random::RangeF(0.5f, 0.8f);

    assets->SetSoundVolume(sound, volume);
    assets->PlaySoundFX(sound);
}

void fireBall::OnCollisionEnter(GameCollision& collision)
{
   
    
    Player* player = dynamic_cast<Player*>(collision.gameBody);
    if (player)
    {
        
        Damage damage;
        damage.amount = 6.f;
        damage.hasEjection = (true);
        damage.ejection = b2Vec2(sens*2, 2);

        player->TakeDamage(damage, this);
        
        Delete();

    }
    



}