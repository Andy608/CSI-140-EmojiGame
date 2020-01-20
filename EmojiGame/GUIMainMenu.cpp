/*
Author:			Andrew Rimpici
Class:			CSI-140-07
Assignment:		Final Project
Date Assigned:	11/30/2016
Due Date:		12/9/2016

Description:	An emoji pet simulator program where you take care of your emoji's and keeping
them alive.
Certification of Authenticity: I certify that this is entirely my own work, except where I have
given fully-documented references to the work of others. I understand the definition
and consequences of plagiarism and acknowledge that the assessor of this assignment may,
for the purpose of assessing this assignment:
-   Reproduce this assignment and provide a copy to another member of academic staff; and/or
-   Communicate a copy of this assignment to a plagiarism checking service (which may then retain
a copy of this assignment on its database for the purpose of future plagiarism checking)
*/
#include "GUIMainMenu.h";
#include "GUIPlayScreen.h"
#include "GUILoadEmoji.h"
#include "Loop.h"

int cursorX = 0;

/*
	Draws the base main menu
*/
void drawMainMenu()
{
	drawLine(0);
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "Welcome to the Emoji Pet Simulator!") << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	drawLine(6);
									   cout << endl;
	setCursorForCenterText(guiWidth); cout << "Press 1 to create a new Emoji Pet!" << endl << endl;
	setCursorForCenterText(guiWidth); cout << "Press 2 if you are visiting an Emoji Pet." << endl << endl;
	setCursorForCenterText(guiWidth); cout << "Press 3 if you are removing an Emoji Pet." << endl << endl;
	setCursorForCenterText(guiWidth); cout << "Press ESC to exit the Emoji Pet Simulator." << endl;
}

/*
	Updates the main menu every tick.
*/
void updateMainMenu()
{
	setCursorForCenterText(guiWidth);
	cursorX = getConsoleCursorX();
	setCursorPos(cursorX, TITLE_EMOJI_Y);
	clearScreenPortion(cursorX, TITLE_EMOJI_Y, guiWidth, TITLE_EMOJI_LENGTH_Y);
	setCursorForCenterText(guiWidth);
	cout << centerText(guiWidth, getEmoji(Awake, Happy));

	clearScreenPortion(cursorX + ERROR_MESSAGE_X, ERROR_MAIN_MENU_MESSAGE_Y, ERROR_MESSAGE_LENGTH_X, ERROR_MESSAGE_LENGTH_Y);
	cout.flush();
	setCursorPos(cursorX + ERROR_MESSAGE_X, ERROR_MAIN_MENU_MESSAGE_Y);
}

/*
	Handles input for main menu.
*/
void handleMainMenuInput(char input)
{
	if (input == ESC_KEY)
	{
		quitGame();
	}
	else if (input == ONE)
	{
		if (emojiCount < MAX_SAVES)
		{
			switchScreen(CreateEmojiMenu);
		}
		else
		{
			switchScreen(FullEmojiListMenu);
		}
	}
	else if (input == TWO)
	{
		switchScreen(LoadEmojiMenu);
	}
	else if (input == THREE)
	{
		switchScreen(DeleteEmojiMenu);
	}
	else
	{
		setCursorForCenterText(guiWidth);
		cursorX = getConsoleCursorX();
		clearScreenPortion(cursorX + ERROR_MESSAGE_X, ERROR_MAIN_MENU_MESSAGE_Y, ERROR_MESSAGE_LENGTH_X, ERROR_MESSAGE_LENGTH_Y);
		cout.flush();
		setCursorPos(cursorX + ERROR_MESSAGE_X, ERROR_MAIN_MENU_MESSAGE_Y);
		cout << "Please enter a valid menu option!" << endl;
	}
}