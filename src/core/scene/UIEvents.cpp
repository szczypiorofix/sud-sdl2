#include "UIEvents.h"



Events::UIEvents::UIEvents( void ) {
	uiEvent = { 0, "default_event" };
}

Events::UIEvents::UIEvents( UIEvent uiEvent ) {
	this->uiEvent = uiEvent;
}


Events::UIEvents::~UIEvents() {

}

void Events::UIEvents::OnClickCallback( UIEvent event ) {
	printf("Event: %i, %s\n", this->uiEvent.id, this->uiEvent.name);
	//printf("UIEvents::OnClickCallback()\n");
}
