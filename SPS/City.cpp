/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "City.h"

City::City(Scene* scene) :
    Terrain(scene, LAYER_TERRAIN)
{
    SetName("City");
    InitTiles();
    SetScale(16.f / 24.f);
}

City::~City()   
{
}

void City::Start()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0.f, 0.f);
    bodyDef.angle = 0.f;

    CreateBody(&bodyDef);

    const float scale = GetScale();
    b2ChainShape chain;
    b2Vec2 vertices[12] = { };
    vertices[0].Set(10.5f, -8.f);
    vertices[1].Set(10.5f, 0.f);
    vertices[2].Set(0.f, 0.f);
    vertices[3].Set(-10.5f, 0.f);
    vertices[4].Set(-10.5f, -8.f);
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

void City::InitTiles()
{
    AssetManager* assets = m_scene->GetAssetManager();
    SpriteSheet* spriteSheet = assets->GetSpriteSheet(SHHET_TILESET_CITY);
    AssertNew(spriteSheet);

    SpriteGroup* floor = spriteSheet->GetGroup("Floor");
    AssertNew(floor);
    SpriteGroup* lWall = spriteSheet->GetGroup("LWall");
    AssertNew(lWall);
    SpriteGroup* rWall = spriteSheet->GetGroup("RWall");
    AssertNew(rWall);
  


    Tile tile;
    const float pixelsPerUnit = 16.f;


    // Bord gauche
    tile.Reset(pixelsPerUnit);
    tile.SetSprite(lWall, 0);
    tile.position.Set(-11.f, 0.5f);
    AddTile(tile);

   

    // Sol
    for (int i = 0; i < 9; i++)
    {
        float x = (float)(-10.f + 2 * i);

        tile.Reset(pixelsPerUnit);
        tile.SetSprite(floor, 0);
        tile.position.Set(x, 0.5f);
        AddTile(tile);
    }

    // Bord droit
    tile.Reset(pixelsPerUnit);
    tile.SetSprite(rWall, 0);
    tile.position.Set(+9.f, 0.5f);
    AddTile(tile);


//    // Décoration
    SpriteGroup* sucre1 = spriteSheet->GetGroup("Sucre1");
    AssertNew(floor);


    SpriteGroup* sucre2 = spriteSheet->GetGroup("Sucre2");
    AssertNew(floor);

    SpriteGroup* bougieB = spriteSheet->GetGroup("Bougie1");
    AssertNew(floor);   

    SpriteGroup* bougieR = spriteSheet->GetGroup("Bougie2");
    AssertNew(floor);

    tile.Reset(pixelsPerUnit);
    tile.SetSprite(sucre1, 0);
    tile.position.Set(1.f, 0.3f);
    tile.anchor = Anchor::SOUTH;
    AddTile(tile);

    tile.Reset(pixelsPerUnit);  
    tile.SetSprite(sucre2, 0);  
    tile.position.Set(1.3f, 1.8f);
    tile.anchor = Anchor::SOUTH;    
    AddTile(tile);  

    tile.Reset(pixelsPerUnit);
    tile.SetSprite(bougieB, 1);
    tile.position.Set(-8.f, 0.4f);
    tile.anchor = Anchor::SOUTH;
    AddTile(tile);

    tile.Reset(pixelsPerUnit);
    tile.SetSprite(bougieR, 0);
    tile.position.Set(8.f, 0.4f);
    tile.flip = SDL_FLIP_HORIZONTAL;
    tile.anchor = Anchor::SOUTH;
    AddTile(tile);
    /*
    tile.Reset(pixelsPerUnit);
    tile.SetSprite(plant, 1);
    tile.position.Set(+6.f, 0.f);
    tile.flip = SDL_FLIP_HORIZONTAL;
    tile.anchor = Anchor::SOUTH;
    AddTile(tile);*/
}
