#pragma once

#include <string>



namespace Events {

	typedef struct UIEvent {
		int id;
		const char* name;
	} UIEvent;



	enum EVENT_TYPE {
		ON_CLICK,
		ON_MOUSE_BUTTON_DOWN,
		ON_MOUSE_BUTTON_UP
	};



	class UIEvents {

	public:

		UIEvents( void );
		UIEvents( UIEvent uiEvent );
		~UIEvents();
		void OnClickCallback( UIEvent event );


	private:
		UIEvent uiEvent;

	};

}

