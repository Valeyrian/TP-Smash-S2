/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "Bomb.h"
#include "Player.h"

Bomb::Bomb(Scene* scene) :
    Damager(scene, LAYER_TERRAIN), m_used(false)
{
    SetName("Bomb");

    AssetManager* assets = scene->GetAssetManager();
    SpriteSheet* spriteSheet = assets->GetSpriteSheet(SHEET_ITEM_BOMB);
    SpriteGroup* spriteGroup = nullptr;
    SpriteAnim* anim = nullptr;

    
    spriteGroup = spriteSheet->GetGroup("Bomb");
    AssertNew(spriteGroup);
    anim = m_animator.CreateAnimation("Bomb", spriteGroup);
    anim->SetCycleCount(1);
    anim->SetFPS(15.f);
   

    timeBeforeExplode = 0;
    m_animator.PlayAnimation("Bomb");

    // TODO : charger l'animation et la lancer
}

Bomb::~Bomb()
{
}

void Bomb::Start()
{
    b2World& world = m_scene->GetWorld();
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = GetStartPosition();
    bodyDef.fixedRotation = false;
    bodyDef.allowSleep = true;
    bodyDef.angularDamping = 0.05f;
    bodyDef.linearDamping = 0.05f;

    b2Body* body = CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    b2Vec2 points[] = {
        b2Vec2(+0.35f, -0.85f),
        b2Vec2(+0.35f, -0.10f),
        b2Vec2(+0.15f, +0.35f),
        b2Vec2(-0.15f, +0.35f),
        b2Vec2(-0.30f, -0.10f),
        b2Vec2(-0.20f, -0.85f)
    };
    b2PolygonShape polygon;
    polygon.Set(points, 6);

    fixtureDef.shape = &polygon;
    fixtureDef.density = 0.1f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.f;
    fixtureDef.filter.categoryBits = CATEGORY_ITEM;
    fixtureDef.filter.maskBits = CATEGORY_TERRAIN;

    // Ajout d'une box en bas pour modifier le centre de gravité
    b2Fixture* fixture = CreateFixture(&fixtureDef);
    b2PolygonShape box;
    box.SetAsBox(0.3f, 0.1f, b2Vec2(.1f, -0.75f), 0.f);

    fixtureDef.shape = &box;
    fixtureDef.density = 4.f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.f;
    fixtureDef.filter.categoryBits = CATEGORY_ITEM;
    fixtureDef.filter.maskBits = CATEGORY_TERRAIN;

    fixture = CreateFixture(&fixtureDef);
    
    timeBeforeExplode = 3.9f*60;
}

void Bomb::Render()
{
    Camera* camera = m_scene->GetActiveCamera();
    b2Body* body = GetBody();

    if (body == nullptr) return;

    // TODO : decommenter  pour afficher la Bomb
    const float angle = body->GetAngle() / b2_pi * 180.f;
    SDL_Texture* texture = m_animator.GetTexture();
    if (texture)
    {
        const SDL_Rect* src = m_animator.GetSourceRect();
        b2Vec2 position = GetInterpolatedPosition();
        SDL_FRect rect = { 0 };
        camera->WorldToView(position, src, 22.f, rect);
        RenderCopyExF(
            g_renderer, texture, src, &rect, Anchor::CENTER,
            -angle, b2Vec2(0.5f, 0.5f), SDL_FLIP_NONE
        );
    }
}

void Bomb::FixedUpdate()
{
    m_animator.Update(m_scene->GetDelta());
    if (timeBeforeExplode > 0)
        timeBeforeExplode--;
    else
    {
        Explode();
        
    }

}

bool Bomb::TakeDamage(const Damage& damage, Damager* damager)
{

   // Damage damage;
    if (m_used) return false;

    Player* player = dynamic_cast<Player*>(damager);
    if (player)
    { 
        b2Vec2 playerpos = player->GetPosition();
        b2Body* BodyBombe = GetBody();
        b2Vec2 bombposition = GetPosition();
        b2Vec2 ejctionpos = b2Vec2(0, 0); 
        
        float playerposx = playerpos.x;
        float playerposy = playerpos.y;
        float bombposx = bombposition.x;
        float bombposy = bombposition.y;
        

        float s = 0;
        if ((bombposition.x - playerposx) > 0)
            s = 1;
        else
            s = -1;
        BodyBombe->SetLinearVelocity(b2Vec2(8 * s, 2));
   
        



    }
   // b2Vec2 damagerposition = damager;
   // if (  )
    

   
}

void Bomb::Explode()
{
    Damage damage;  

    b2Vec2 bombposition = GetPosition();
    QueryFilter filter(CATEGORY_ALL_TEAMS); 

   
    damage.amount = 12.f;
    damage.isfromBomb = true;
    damage.bombCenter = bombposition;
    damage.ejection = b2Vec2(8.0f, 5.0f);
    bool hit = AttackCircle(damage, filter, bombposition, 0.8f);
    
    
    Delete();

}