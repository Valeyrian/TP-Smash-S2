/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#pragma once

#include "Terrain.h"

class PlatformG : public Terrain
{
public:
    PlatformG(Scene* scene);
    virtual ~PlatformG();

    virtual void Start() override;

protected:
    void InitTiles();
};
