/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "PlatformG.h"
#include "PlatformD.h"
#include "Player.h"

PlatformD::PlatformD(Scene* scene, int layer, b2Vec2 StartPos) :
    Terrain(scene, layer), m_bodies(),
    m_angleTarget(0.f), m_angleMaxSpeed(100.f), m_angleSmoothTime(1.f),
    m_positionTarget(b2Vec2_zero), m_positionMaxSpeed(100.f), m_positionSmoothTime(1.f), m_DeplacementState(1), m_TimePhaseOne(-1)
{
    SetName("PlatformD");
    InitTiles();
    SetScale(8.f / 24.f); //16 /24
    m_startPosD = StartPos;  
    SetOneWay(true);
}


PlatformD::~PlatformD()
{
}

void PlatformD::Start()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;

    bodyDef.position.Set(m_startPosD.x, m_startPosD.y);
    m_initPosD = m_startPosD;
    bodyDef.angle = 0.f;

    CreateBody(&bodyDef);

    const float scale = GetScale();
    b2ChainShape chain;
    b2Vec2 vertices[12] = { };
    vertices[0].Set(16.5f, -2.f);
    vertices[1].Set(16.5f, 0.f);
    vertices[2].Set(0.f, 0.f);
    vertices[3].Set(-5.5f, 0.f);
    vertices[4].Set(-5.5f, -2.f);
    for (int i = 0; i < 5; i++)
        vertices[i] *= scale;

    chain.CreateLoop(vertices, 5);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &chain;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.f;
    fixtureDef.filter.categoryBits = CATEGORY_TERRAIN;

    b2Fixture* fixture = CreateFixture(&fixtureDef);
    AssertNew(fixture);
}


void PlatformD::InitTiles()
{
    AssetManager* assets = m_scene->GetAssetManager();
    SpriteSheet* spriteSheet = assets->GetSpriteSheet(SHEET_TILESET_ROCKY);
    AssertNew(spriteSheet);

    SpriteGroup* floor = spriteSheet->GetGroup("Floor");
    AssertNew(floor);
    SpriteGroup* lWall = spriteSheet->GetGroup("LWall");
    AssertNew(lWall);
    SpriteGroup* rWall = spriteSheet->GetGroup("RWall");
    AssertNew(rWall);
    SpriteGroup* ground = spriteSheet->GetGroup("Ground");
    AssertNew(ground);

    Tile tile;
    const float pixelsPerUnit = 16.f;


    // Bord gauche
    tile.Reset(pixelsPerUnit);
    tile.SetSprite(lWall, 0);
    tile.position.Set(-6.f, 0.5f); // -11
    AddTile(tile);

 
    // Sol
    for (int i = 0; i <11; i++) //i <10
    {
        float x = (float)(-5.f + 2* i);

        tile.Reset(pixelsPerUnit);
        tile.SetSprite(floor, 0);
        tile.position.Set(x, 0.5f);
        AddTile(tile);
    }

    // Bord droit
    tile.Reset(pixelsPerUnit);
    tile.SetSprite(rWall, 0);
    tile.position.Set(+17.f, 0.5f);//10
    AddTile(tile);


    // Décoration
    SpriteGroup* crystal = spriteSheet->GetGroup("Crystal");
    AssertNew(floor);
    SpriteGroup* plant = spriteSheet->GetGroup("Plant");
    AssertNew(plant);

    tile.Reset(pixelsPerUnit);
    tile.SetSprite(crystal, 0);
    tile.position.Set(2.6f, 0.3f);
    tile.anchor = Anchor::SOUTH;
    AddTile(tile);


    tile.Reset(pixelsPerUnit);
    tile.SetSprite(plant, 0);
    tile.position.Set(-2.6f, 0.f);
    tile.flip = SDL_FLIP_HORIZONTAL;
    tile.anchor = Anchor::SOUTH;
    AddTile(tile);

}

void PlatformD::PlatformDeplacement() 
{
    //printf("timePhaseOne %f \n", m_TimePhaseOne);
    if (m_DeplacementState == 0) //en mouvement
        return;
    else if (m_DeplacementState == 1) //phase 1
    {
        m_DeplacementState = 0;
        SetTargetPosition(b2Vec2(15, 6),10,15);
        m_DeplacementState =2;//rajout d'un timer
        m_TimePhaseOne = 8 *60;
    }
    else if (m_DeplacementState == 2 && m_TimePhaseOne == 0) //phase 2
    {
        m_DeplacementState = 0;   
        SetTargetPosition(b2Vec2(-2 ,10.5), 10, 25);
        m_TimePhaseOne = 30 * 60;
        m_DeplacementState = 3;

    }
    else if (m_DeplacementState == 3 && m_TimePhaseOne == 0) //phase 2
    {
        m_DeplacementState = 0; 
        SetTargetPosition(b2Vec2(-19, 6), 10, 25); 
        m_TimePhaseOne = 30 * 60;   
        m_DeplacementState = 4;

    }

    else if (m_DeplacementState == 4 && m_TimePhaseOne == 0) //phase 2
    {
        m_DeplacementState = 0;
        SetTargetPosition(b2Vec2(-19, -2), 3, 25);
        m_TimePhaseOne = 10 * 60;
        m_DeplacementState = 5;


    }
    else if (m_DeplacementState == 5 && m_TimePhaseOne == 0) //phase 1
    {
        m_DeplacementState = 0;
        SetTargetPosition(b2Vec2(-10, 6), 10, 15);
        m_DeplacementState = 6;//rajout d'un timer
        m_TimePhaseOne = 8 * 60;

    }
    else if (m_DeplacementState == 6 && m_TimePhaseOne == 0) //phase 2
    {
        m_DeplacementState = 0;
        SetTargetPosition(b2Vec2(-2, 5.5), 10, 25);
        m_TimePhaseOne = 30 * 60;
        m_DeplacementState = 7;

    }
    else if (m_DeplacementState == 7 && m_TimePhaseOne == 0) //phase 2
    {
        m_DeplacementState = 0;
        SetTargetPosition(b2Vec2(15, 6), 6, 25);
        m_TimePhaseOne = 8 * 60;
        m_DeplacementState = 8;

    }

    else if (m_DeplacementState == 8 && m_TimePhaseOne == 0) //phase 2
    {
        m_DeplacementState = 0;
        SetTargetPosition(b2Vec2(15, -2), 10, 25);
        m_TimePhaseOne = 8 * 60;
        m_DeplacementState = 9;

        
    }
    else if (m_DeplacementState == 9 && m_TimePhaseOne == 0) //phase 2
    {
        m_DeplacementState = 1;
        

    }

    
}

void PlatformD::FixedUpdate()
{
    Terrain::FixedUpdate();

    b2Body *body = GetBody();
    if (body == nullptr) return;

    b2Vec2 velocity = GetVelocity();
    b2Vec2 position = GetPosition();

    m_TimePhaseOne--;
   // printf("timePhasseOne : %f \n", m_TimePhaseOne); 
    float targetDist = (m_positionTarget - position).Length();
    if (fabsf(targetDist) > 0.01f)
    {
        float speed = velocity.Length();

        Math::SmoothDamp(
            0.f, targetDist, speed,
            m_positionSmoothTime, m_positionMaxSpeed, m_scene->GetDelta()
        );
        velocity = speed / targetDist * (m_positionTarget - position);
        body->SetLinearVelocity(velocity);
    }
    else
    {
        body->SetLinearVelocity(b2Vec2_zero);
    }

    float angle = body->GetAngle();
    float angularVelocity = body->GetAngularVelocity();

    if (fabsf(angle - m_angleTarget) > 0.005f)
    {
        Math::SmoothDamp(
            angle, m_angleTarget, angularVelocity,
            m_positionSmoothTime, m_positionMaxSpeed, m_scene->GetDelta()
        );
        body->SetAngularVelocity(angularVelocity);
    }
    else
    {
        body->SetAngularVelocity(0.f);
    }

    ApplyExternalVelocity();
    PlatformDeplacement();


}

void PlatformD::SetTargetPosition(b2Vec2 position, float smoothTime, float maxSpeed) 
{
    m_positionTarget = position;    
    m_positionSmoothTime = smoothTime;  
    m_positionMaxSpeed = maxSpeed;  
} 

void PlatformD::SetTargetAngle(float angle, float smoothTime, float maxSpeed)
{
    m_angleTarget = angle;
    m_angleSmoothTime = smoothTime;
    m_angleMaxSpeed = maxSpeed;
} 

void PlatformD::ApplyExternalVelocity()
{
    if (GetBody() == nullptr) return;

    b2Vec2 extVelocity = GetVelocity();
    extVelocity.y *= 0.5f;

    for (GameBody *gameBody : m_bodies)
    {
        if (m_scene->Contains(gameBody) == false) continue;

        Player *player = dynamic_cast<Player *>(gameBody);
        if (player)
        {
            player->AddExternalVelocity(extVelocity);
        }
    }

    m_bodies.clear();
}

const std::set<GameBody *> &PlatformD::GetBodies() const
{
    return m_bodies;
}
