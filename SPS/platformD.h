#pragma once
/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#pragma once

#include "Terrain.h"

class PlatformD : public Terrain
{
public:
    PlatformD(Scene* scene);
    virtual ~PlatformD();

    virtual void Start() override;

protected:
    void InitTiles();
};
