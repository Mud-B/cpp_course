#include "advanturer.h"
#include "room.h"
#include<windows.h> 

int main() {
	Advanturer player();
	GeneralRoom g();
	g.enterEvent(player);
}