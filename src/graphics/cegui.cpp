/*
 *  This file is part of Experiental.
 *
 *  Experiental is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Experiental is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Experiental.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cegui.h"
#include <string>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

const std::string & CEGUIInstallBasePath = "/usr" ;

// Input management: from SDL to CEGUI.

void GUI::handle_mouse_down( Uint8 button )
{

  switch ( button )
  {

  case SDL_BUTTON_LEFT:
	CEGUI::System::getSingleton().injectMouseButtonDown( CEGUI::LeftButton ) ;
	break ;

  case SDL_BUTTON_MIDDLE:
	CEGUI::System::getSingleton().injectMouseButtonDown( CEGUI::MiddleButton ) ;
	break ;

  case SDL_BUTTON_RIGHT:
	CEGUI::System::getSingleton().injectMouseButtonDown( CEGUI::RightButton) ;
	break ;

  case SDL_BUTTON_WHEELDOWN:
	CEGUI::System::getSingleton().injectMouseWheelChange( -1 ) ;
	break ;

  case SDL_BUTTON_WHEELUP:
	CEGUI::System::getSingleton().injectMouseWheelChange( +1 ) ;
	break ;

  default:
//	cout << "handle_mouse_down ignored '" << static_cast<int>( button )
//		 << "'" << endl ;
	break ;

  }

}


void GUI::handle_mouse_up( Uint8 button )
{

  switch ( button )
  {

  case SDL_BUTTON_LEFT:
	CEGUI::System::getSingleton().injectMouseButtonUp( CEGUI::LeftButton ) ;
	break ;

  case SDL_BUTTON_MIDDLE:
	CEGUI::System::getSingleton().injectMouseButtonUp( CEGUI::MiddleButton ) ;
	break ;

  case SDL_BUTTON_RIGHT:
	CEGUI::System::getSingleton().injectMouseButtonUp( CEGUI::RightButton ) ;
	break ;

  case SDL_BUTTON_WHEELDOWN:
	break ;

  case SDL_BUTTON_WHEELUP:
	break ;

  default:
//	cout << "handle_mouse_up ignored '" << static_cast<int>( button )
//		 << "'" << endl ;
	break ;

  }

}



void GUI::inject_input( bool & must_quit )
{

  SDL_Event e ;

  // Go through all available events:
  while ( SDL_PollEvent( &e ) )
  {

	// Route according to the event type:
	switch( e.type )
	{

	// Mouse section:

	case SDL_MOUSEMOTION:
	  // We inject the mouse position directly here:
	  CEGUI::System::getSingleton().injectMousePosition(
		static_cast<float>( e.motion.x ), static_cast<float>( e.motion.y ) ) ;
	  break ;

	case SDL_MOUSEBUTTONDOWN:
	  handle_mouse_down( e.button.button ) ;
	  break ;

	case SDL_MOUSEBUTTONUP:
	  handle_mouse_up( e.button.button ) ;
	  break ;

	// Keyboard section:

	case SDL_KEYDOWN:

	  CEGUI::System::getSingleton().injectKeyDown(e.key.keysym.scancode) ;

	  /*
	   * Managing the character is more difficult, we have to use a translated
	   * unicode value:
	   *
	   */

	  if ( (e.key.keysym.unicode & 0xFF80) == 0 )
	  {
		CEGUI::System::getSingleton().injectChar(
		  e.key.keysym.unicode & 0x7F ) ;
	  }
	  break ;

	case SDL_KEYUP:
	  CEGUI::System::getSingleton().injectKeyUp( e.key.keysym.scancode ) ;
	  break ;

	// A WM quit event occured:
	case SDL_QUIT:
	  must_quit = true ;
	  break ;

	case SDL_VIDEORESIZE:
	  CEGUI::System::getSingleton().notifyDisplaySizeChanged(
		CEGUI::Size( e.resize.w, e.resize.h ) ) ;
	  break ;

	}

  }

}



void GUI::inject_time_pulse( double & last_time_pulse )
{

  // Get current "run-time" in seconds:
  double current_time_pulse = 0.001 * SDL_GetTicks() ;

  // Inject the time that passed since the last call:
  CEGUI::System::getSingleton().injectTimePulse( static_cast<float>(
	  current_time_pulse - last_time_pulse ) ) ;

  // Records the new time as the last time:
  last_time_pulse = current_time_pulse ;

}

void GUI::render_gui()
{

  // Clears the colour buffer:
  //glClear( GL_COLOR_BUFFER_BIT ) ;

  // Renders the GUI:
  CEGUI::System::getSingleton().renderGUI() ;

  // Updates the screen:
  //SDL_GL_SwapBuffers() ;

}

void GUI::set_CEGUI_paths()
{

	// Initialises the required directories for the DefaultResourceProvider:

	CEGUI::DefaultResourceProvider & defaultResProvider =
		* static_cast<CEGUI::DefaultResourceProvider*>
			( CEGUI::System::getSingleton().getResourceProvider() ) ;

	const std::string CEGUIInstallSharePath = CEGUIInstallBasePath
	  + "/share/CEGUI/" ;

	// For each resource type, sets a corresponding resource group directory:

//	cout << "Using scheme directory '" << CEGUIInstallSharePath + "schemes/"
//		 << "'" << endl ;

	defaultResProvider.setResourceGroupDirectory( "schemes",
	  CEGUIInstallSharePath + "schemes/" ) ;

	defaultResProvider.setResourceGroupDirectory( "imagesets",
	  CEGUIInstallSharePath + "imagesets/" ) ;

	defaultResProvider.setResourceGroupDirectory( "fonts",
	  CEGUIInstallSharePath + "fonts/" ) ;

	defaultResProvider.setResourceGroupDirectory( "layouts",
	  CEGUIInstallSharePath + "layouts/" ) ;

	defaultResProvider.setResourceGroupDirectory( "looknfeels",
	  CEGUIInstallSharePath + "looknfeel/" ) ;

	defaultResProvider.setResourceGroupDirectory( "lua_scripts",
	  CEGUIInstallSharePath + "lua_scripts/" ) ;

	defaultResProvider.setResourceGroupDirectory( "schemas",
	  CEGUIInstallSharePath + "xml_schemas/" ) ;

	defaultResProvider.setResourceGroupDirectory( "animations",
	  CEGUIInstallSharePath + "animations/" ) ;

	// Sets the default resource groups to be used:
	CEGUI::Imageset::setDefaultResourceGroup( "imagesets" ) ;
	CEGUI::Font::setDefaultResourceGroup( "fonts" ) ;
	CEGUI::Scheme::setDefaultResourceGroup( "schemes" ) ;
	CEGUI::WidgetLookManager::setDefaultResourceGroup( "looknfeels" ) ;
	CEGUI::WindowManager::setDefaultResourceGroup( "layouts" ) ;
	CEGUI::ScriptModule::setDefaultResourceGroup( "lua_scripts" ) ;
	CEGUI::AnimationManager::setDefaultResourceGroup( "animations" ) ;

	// Set-up default group for validation schemas:
	CEGUI::XMLParser * parser = CEGUI::System::getSingleton().getXMLParser() ;
	if ( parser->isPropertyPresent( "SchemaDefaultResourceGroup" ) )
		parser->setProperty( "SchemaDefaultResourceGroup", "schemas" ) ;

}

CEGUI::WindowManager & GUI::init_CEGUI(SDL_Surface & surface)
{

//  cout << " - initializing CEGUI" << endl ;

  CEGUI::OpenGLRenderer::bootstrapSystem() ;

  set_CEGUI_paths() ;

  CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" ) ;

  CEGUI::System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" ) ;

  return CEGUI::WindowManager::getSingleton() ;

}



void GUI::create_gui( CEGUI::WindowManager & winManager )
{

//  cout << " - creating the GUI" << endl ;

  CEGUI::DefaultWindow & rootWin = * static_cast<CEGUI::DefaultWindow*>(winManager.createWindow( "DefaultWindow", "Root" ) ) ;

  CEGUI::System::getSingleton().setGUISheet( &rootWin ) ;

  CEGUI::FrameWindow & myWin = * static_cast<CEGUI::FrameWindow*>( winManager.createWindow("TaharezLook/FrameWindow", "Demo Window" ) ) ;

  rootWin.addChildWindow( &myWin ) ;

  myWin.setPosition( CEGUI::UVector2( cegui_reldim(0.25f), cegui_reldim(0.25f) ) ) ;
  myWin.setSize( CEGUI::UVector2( cegui_reldim(0.5f), cegui_reldim(0.5f) ) ) ;

  myWin.setMaxSize( CEGUI::UVector2( cegui_reldim(1.0f), cegui_reldim(1.0f) ) ) ;
  myWin.setMinSize( CEGUI::UVector2( cegui_reldim(0.1f), cegui_reldim(0.1f) ) ) ;

  myWin.setText( "Hello World! This is a minimal SDL+OpenGL+CEGUI test." ) ;

}
