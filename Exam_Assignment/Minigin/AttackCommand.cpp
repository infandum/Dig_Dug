#include "MiniginPCH.h"
#include "AttackCommand.h"
#include "GameObject.h"
void dae::AttackCommand::Execute(GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	//if(m_KeyDown == SDL_KEYDOWN){
	//
	std::cout << gameObject.GetName() << ">> ATTACKS!!" << std::endl;
	//}

}