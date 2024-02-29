#include "DxLib.h"
#include "GameMaster.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	GM = new GameMaster();
	GM->Run();
	delete GM;

	return 0;
}