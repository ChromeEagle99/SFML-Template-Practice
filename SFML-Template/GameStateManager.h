#pragma once

typedef void(*FP)(void);

extern int GSM_current, GSM_previous, GSM_next;

extern FP fpLoad, fpInitialize, fpUpdate, fpDraw, fpFree, fpUnload;

void GSM_Initialize(int startingState);
void GSM_Update();
