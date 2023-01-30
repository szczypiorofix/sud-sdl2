#include <stdio.h>
#include "core/GameSystem.h"
#include <locale>

int main( int argc, char* args[] ) {
	setlocale( LC_ALL, "" );
	SUD::GameSystem::GetInstance()->Launch( argc, args );
	return 0;
}