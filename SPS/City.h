#pragma once
/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#pragma once

#include "Terrain.h"

class City : public Terrain
{
public:
    City(Scene* scene);
    virtual ~City();

    virtual void Start() override;

protected:
    void InitTiles();
};
