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
#include "GUIDeleteEmoji.h"
#include "Loop.h"
#include "GUIPlayScreen.h"
#include "GuiLoadEmoji.h"
#include "GUIMainMenu.h"

/*
	Draws the base delete emoji menu.
*/
void drawDeleteEmojiMenu()
{
	drawLine(0);
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, getEmoji(Dead, Happy)) << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "This is the Emoji Pet Delete Menu") << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "---") << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "All of your saved pets are listed below.") << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	drawLine(8);
	cout << endl;

	setCursorForCenterText(guiWidth);
	int cursorX = getConsoleCursorX();
	int cursorY = getConsoleCursorY();

	if (emojiCount == 0)
	{
		cout << "You currently do not have any Emoji Pets to delete." << endl;
	}
	else
	{
		printAllEmojiNames(cursorX + 1, cursorY, false);
	}

	setCursorPos(cursorX, cursorY + 12);
	cout << "Press ESC to return to the Main Menu." << endl;
}

/*
	Updates the delete emoji menu every tick.
*/
void updateDeleteEmojiMenu()
{
	int cursorX = getConsoleCursorX();
	
	clearScreenPortion(cursorX + ERROR_MESSAGE_X, ERROR_LOAD_EMOJI_MENU_MESSAGE_Y, ERROR_MESSAGE_LENGTH_X, ERROR_MESSAGE_LENGTH_Y);
	cout.flush();
	setCursorPos(cursorX + ERROR_MESSAGE_X, ERROR_LOAD_EMOJI_MENU_MESSAGE_Y);
}

/*
	Handles input for the delete emoji menu.
*/
void handleDeleteEmojiMenu(char input)
{
	if (input == ESC_KEY)
	{
		switchScreen(MainMenu);
		return;
	}

	setCursorForCenterText(guiWidth);
	int cursorX = getConsoleCursorX();
	int cursorY = 10;

	for (int i = 0; i < emojiCount; i++)
	{
		if (input == i + ONE)
		{
			deleteUser(i);
			clearScreenPortion(0, 10, getConsoleWidth(), 10);
			printAllEmojiNames(cursorX + 1, cursorY, true);
			return;
		}
	}

	clearScreenPortion(cursorX + ERROR_MESSAGE_X, ERROR_LOAD_EMOJI_MENU_MESSAGE_Y, ERROR_MESSAGE_LENGTH_X, ERROR_MESSAGE_LENGTH_Y);
	cout.flush();
	setCursorPos(cursorX + ERROR_MESSAGE_X, ERROR_LOAD_EMOJI_MENU_MESSAGE_Y);
	cout << "Please enter a valid menu option!" << endl;
}