/*****************************************************************************
* Program name: Buttons.exe
* Version:	1.0.0
* Developer:    Yaron Meister
* Date:         2021-09-17 17:10:27
*****************************************************************************/

Description:
	This program logs the activity of desired toggle buttons (ON/OFF)	

Executable instructions:
	1. Edit the "runButtonsLog.bat" file with the desired buttons to log (Add their indeces after the program's name, separated with spaces)
	   Valid indeces are 0:9.
	2. Run "runButtonsLog.bat".
	3. The buttons are controlled by the digits on the keyboard. Every press on one of them is a toggle of the relevant button's id.
	4. To stop the program - Press 'Q'.
	5. Activity log is shown in the file "ButtonsLog.txt".
	6. Observe the file "ErrorsLog.txt" in unexpected behavior.

Known bugs:
	1. Adding the same button id N times, cause N same logs. will be resolved next version.

/* End of document */