#include <stdio.h>
#include "core/GameSystem.h"
#include <locale>

int main( int argc, char* args[] ) {
	setlocale( LC_ALL, "" );
	GameSystem::GetInstance()->Start( argc, args );
	return 0;
}