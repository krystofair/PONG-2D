# GAME PONG 2D

## Configuration


Solution Explorer(right mouse button)->properties
1. Configuration:  All
	Configuration Properties->C/C++->Additional Include Directories->{sfml_inlcude_folder e.g. D:\SFML-2.5.1\include}->Apply
	Configuration Properties->Linker->Additional Library Directories->{sfml_lib_folder e.g. D:\SFML-2.5.1\lib}->Apply
2. Configuration:  Debug
	Configuration Properties->Linker->Input->Additional Dependencies->Edit->
		{paste:
			sfml-audio-d.lib
			sfml-graphics-d.lib
			sfml-main-d.lib
			sfml-network-d.lib
			sfml-system-d.lib
			sfml-window-d.lib
		}->OK->Apply
3. Configuration:  Release
	Configuration Properties->Linker->Input->Edit->
		{paste:
			sfml-audio.lib
			sfml-graphics.lib
			sfml-main.lib
			sfml-network.lib
			sfml-system.lib
			sfml-window.lib
		}->OK->Apply

4. Configuration:  All
	Configuration Properties->Linker->System->SubSystem->{Windows (/SUBSYSTEM:WINDOWS)}->OK
