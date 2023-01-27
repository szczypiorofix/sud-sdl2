#include <stdio.h>
#include "core/GameSystem.h"

int main( int argc, char* args[] ) {
	SUD::GameSystem::GetInstance()->Launch( argc, args );
	return 0;
}