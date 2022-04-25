#include "GameStateManager.h"
#include "GameStateList.h"


#include"GameState/Scene1.h"



int GSM_current = 0, GSM_previous = 0, GSM_next = 0;

FP fpLoad = nullptr, fpInitialize = nullptr, fpUpdate = nullptr, fpDraw = nullptr, fpFree = nullptr, fpUnload = nullptr;

void GSM_Initialize(int startingState)
{
	GSM_current = GSM_previous = GSM_next = startingState;
}

void GSM_Update()
{
	switch (GSM_current)
	{
	case GS_LEVEL1:
		fpLoad = scene1_load;
		fpInitialize = scene1_init;
		fpUpdate = scene1_update;
		fpDraw = scene1_draw;
		fpFree = scene1_free;
		fpUnload = scene1_unload;
		break;
	case GS_RESTART:
		break;
	case GS_QUIT:
		break;
	default:
		break;
	}

}
