#include "CMovementIntergration.h"

void CMovementIntergration::Movement(std::vector<CEnemy*> _Enemies)
{
	for (int i = 0; i < _Enemies.size(); i++)
	{
		//ACTUALLY Move on the x
		_Enemies[i]->GetShape().move(_Enemies[i]->GetVelocity().x * _Enemies[i]->GetSpeed() * CTimeKeeper::getInstance().m_DeltaTme, 0);

		//ACTUALLY move on the Y
		_Enemies[i]->GetShape().move(0, _Enemies[i]->GetVelocity().y * _Enemies[i]->GetSpeed() * CTimeKeeper::getInstance().m_DeltaTme);
	}
}
