#pragma once
#include "CCollisionHandler.h"
#include <vector>
#include "CObject.h"
#include "CPlayer.h"

class CPhysics
{
public:
    std::vector<CObject*> m_PhysicsObjects; // Holds all objects to apply physics on
    std::vector<CObject*> m_CollisionObjects; // Holds all objects to collide with

    CPlayer* m_TrackedPlayer;

    CPhysics();
    ~CPhysics();

    void SetTrackedPlayer(CPlayer* _Player);
    CPlayer* GetTrackedPlayer();

    void CollisionIntergration(std::vector<CObject*> _Objects);
    void MovementIntergration(std::vector<CObject*> _Objects);

    void EmptyPhysics();
};