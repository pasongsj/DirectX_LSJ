#include "PrecompileHeader.h"
#include "HildaBergBossController.h"

HildaBergBossController::HildaBergBossController() 
{
}

HildaBergBossController::~HildaBergBossController() 
{
}

void HildaBergBossController::Start()
{

}

void HildaBergBossController::Update(float _DeltaTime) 
{
	if (nullptr == Boss)
	{
		switch (Phase)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		default:
			break;
		}
	}
}