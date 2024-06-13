/*
  Copyright (c) Arnaud BANNIER and Nicolas BODIN.
  Licensed under the MIT License.
  See LICENSE.md in the project root for license information.
*/

#include "PlayerAI.h"
#include "StageManager.h"


PlayerAI::PlayerAI(Player *player) :
    m_player(player), m_input(), m_target(nullptr), m_delayBeforeCheck(0)
{
    m_scene = m_player->m_scene;
    m_player->m_maxSpeed = 6.f;

    m_stageBox.lowerBound = b2Vec2(-8.0f, 0.0f);
    m_stageBox.upperBound = b2Vec2(+8.0f, 2.0f);
}

PlayerAI::~PlayerAI()
{
}

void PlayerAI::FixedUpdate()
{
    b2Body *body = m_player->GetBody();
    b2Vec2 position = m_player->GetPosition();
    b2Vec2 velocity = m_player->GetVelocity();
   
    m_input.jumpPressed = false;
    m_input.attackPressed = false;
    m_input.attackDown = false;
    m_input.goDownDown = false;

    ChooseTarget();
    if (m_target == nullptr) return;

    

    m_player->AddFixedUpdateDelay(&m_delayBeforeCheck); 
    if (m_delayBeforeCheck > 0)
        return;

    
    b2Vec2 targetPosition = m_target->GetPosition();
    b2Vec2 dist = ((targetPosition ) - position);
    
    if (dist.y > 0.3f  && velocity.y <= 4.f)
        {
            m_input.jumpPressed = true;
            m_input.goDownDown = false; 
        }
    if (dist.y < .8f && IsOverVoid() == true && m_player->m_isGrounded == true)
    {
        m_input.jumpPressed = false;
        m_input.goDownDown = true;
    }

    printf("dist x %f  et is grounded %d\n ", dist.x, m_player->m_isGrounded);

    if (dist.x > 0.5 || dist.x <0.5)
    {
        if (dist.x > 0.5)
        {
            m_input.axisX = 1.f;
        }
        else if (dist.x < 0.5)
        {
            m_input.axisX = -1.f;

        }
        
    }
   
   
    m_delayBeforeCheck = 0.2;
   
    
    

    
}


void PlayerAI::OnStateChanged(Player::State state, Player::State prevState)
{
    

}

bool PlayerAI::IsOverVoid()
{
    b2Vec2 position = m_player->GetPosition();

    if (position.x > -8 && position.x < 8)
        return true;
    else
        return false;

}


bool PlayerAI::IsInDanger() const
{
    b2Vec2 position = m_player->GetPosition();

    bool inDanger = false;
    if (position.x > m_stageBox.upperBound.x)
    {
        inDanger = true;
    }
    else if (position.x < m_stageBox.lowerBound.x)
    {
        m_player->m_hDirection = 1.0f;
        inDanger = true;
    }
    return inDanger;
}

void PlayerAI::ChooseTarget()
{
    StageManager *stageManager = StageManager::GetFromScene(m_scene);
    m_target = stageManager->GetPlayer(0);
}

//void PlayerAI::ComeBack()
//{
//    b2Vec2 position = m_player->GetPosition();
//    b2Vec2 velocity = m_player->GetVelocity();
//
//    if (position.x > m_stageBox.upperBound.x)
//    {
//        m_input.axisX = -1.0f;
//    }
//    else if (position.x < m_stageBox.lowerBound.x)
//    {
//        m_input.axisX = 1.0f;
//    }
//    else
//    {
//        m_input.axisX = 0.0f;
//    }
//
//    if (velocity.y < 0.0f && position.y < m_stageBox.lowerBound.y + 1.0f)
//    {
//        m_input.jumpPressed = true;
//    }
//
//    if (velocity.y > 0.0f)
//    {
//        m_input.jumpDown = true;
//    }
//}
