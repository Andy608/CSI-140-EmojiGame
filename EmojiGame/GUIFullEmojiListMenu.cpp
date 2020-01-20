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
#include "Loop.h"
#include "GuiPlayScreen.h"
#include "GUIMainMenu.h"
#include "GUIFullEmojiListMenu.h"

/*
	Draws the base full emoji list menu.
*/
void drawFullEmojiListMenu()
{
	drawLine(0);
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "Uh oh! You can't create anymore Emoji Pets.") << endl;
	setCursorForCenterText(guiWidth); cout << endl;

	string errorMessage = "You need to delete a previous Emoji Pet before you can create a new one.";
	string errorMessage2;
	bool twoLines = errorMessage.length() > guiWidth;
	if (twoLines)
	{
		errorMessage = "You need to delete a previous Emoji Pet";
		errorMessage2 = "before you can create a new one.";
	}

	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, errorMessage) << endl;
	if (twoLines) setCursorForCenterText(guiWidth); cout << centerText(guiWidth, errorMessage2) << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	drawLine(8);
	cout << endl;

	setCursorForCenterText(guiWidth);
	int cursorX = getConsoleCursorX();
	int cursorY = getConsoleCursorY();

	setCursorPos(cursorX, cursorY + 9);
	cout << "Press any key to return to the Main Menu." << endl;
}

/*
	Updates the full emoji list menu every tick.
*/
void updateFullEmojiListMenu()
{
	setCursorForCenterText(guiWidth);
	int cursorX = getConsoleCursorX();
	setCursorPos(cursorX, TITLE_EMOJI_Y);
	clearScreenPortion(cursorX, TITLE_EMOJI_Y, guiWidth, TITLE_EMOJI_LENGTH_Y);
	setCursorForCenterText(guiWidth);
	cout << centerText(guiWidth, getEmoji(Awake, Depressed));

	clearScreenPortion(cursorX + ERROR_MESSAGE_X, ERROR_MAIN_MENU_MESSAGE_Y, ERROR_MESSAGE_LENGTH_X, ERROR_MESSAGE_LENGTH_Y);
	cout.flush();
	setCursorPos(cursorX + ERROR_MESSAGE_X, ERROR_MAIN_MENU_MESSAGE_Y);
}

/*
	Handles the input for the full emoji list menu.
*/
void handleFullEmojiListMenu(char input)
{
	switchScreen(MainMenu);
}