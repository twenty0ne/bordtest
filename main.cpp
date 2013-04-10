
#include <stdio.h>
#include "Macro.h"
#include "define.h"
#include "GameMain.h"

int main()
{

#if TEST_PRINT_LOG
	printf("==========================================\n");
	printf("Game Start\n");
#endif

	theGameApp.Init();

	while(1)
	{
		theGameApp.Update(0.1);
	}

	return 0;
}