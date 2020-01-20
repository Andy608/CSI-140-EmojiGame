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
#include "GUILoadEmoji.h"
#include "GUIPlayScreen.h"
#include "GUIMainMenu.h"
#include "Loop.h"

/*
	Draws the base load emoji menu.
*/
void drawLoadEmojiMenu()
{
	drawLine(0);
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "This is the Emoji Pet Loader Menu") << endl;
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
		cout << "You currently do not have any Emoji Pets." << endl;
	}
	else
	{
		printAllEmojiNames(cursorX + 1, cursorY, false);
	}

	setCursorPos(cursorX, cursorY + 12);
	cout << "Press ESC to return to the Main Menu." << endl;
}

/*
	Prints all of the emojis saved in the file out in a nice list.
*/
void printAllEmojiNames(int cursorX, int cursorY, bool isDeleting)
{
	for (int i = 0; i < emojiCount; i++)
	{
		if (i >= MAX_SLOT_PER_COLUMN)
		{
			setCursorPos(cursorX + SLOT_OFFSET_X, cursorY + ((i - MAX_SLOT_PER_COLUMN) * 2));
		}
		else
		{
			setCursorPos(cursorX, cursorY + (i * 2));
		}

		if (isDeleting)
		{
			cout << " -  Press " << (i + 1) << " to delete your emoji pet, " << emojiName[i] << endl << endl;
		}
		else
		{
			cout << " -  Press " << (i + 1) << " to go to your emoji pet, " << emojiName[i] << endl << endl;
		}
	}
}

/*
	Updates the load emoji menu every tick.
*/
void updateLoadEmojiMenu()
{
	setCursorForCenterText(guiWidth);
	int cursorX = getConsoleCursorX();
	setCursorPos(cursorX, TITLE_EMOJI_Y);
	clearScreenPortion(cursorX, TITLE_EMOJI_Y, guiWidth, TITLE_EMOJI_LENGTH_Y);
	setCursorForCenterText(guiWidth);
	cout << centerText(guiWidth, getEmoji(Awake, Happy));

	clearScreenPortion(cursorX + ERROR_MESSAGE_X, ERROR_LOAD_EMOJI_MENU_MESSAGE_Y, ERROR_MESSAGE_LENGTH_X, ERROR_MESSAGE_LENGTH_Y);
	cout.flush();
	setCursorPos(cursorX + ERROR_MESSAGE_X, ERROR_LOAD_EMOJI_MENU_MESSAGE_Y);
}

/*
	Handles load emoji menu input.
*/
void handleEmojiLoadMenuInput(char input)
{

	if (input == ESC_KEY)
	{
		switchScreen(MainMenu);
		return;
	}

	for (int i = ONE; i < ONE + emojiCount; i++)
	{
		if (input == i)
		{
			currentEmojiIndex = i - ONE;
			switchScreen(PlayScreen);
			return;
		}
	}

	setCursorForCenterText(guiWidth);
	int cursorX = getConsoleCursorX();

	clearScreenPortion(cursorX + ERROR_MESSAGE_X, ERROR_LOAD_EMOJI_MENU_MESSAGE_Y, ERROR_MESSAGE_LENGTH_X, ERROR_MESSAGE_LENGTH_Y);
	cout.flush();
	setCursorPos(cursorX + ERROR_MESSAGE_X, ERROR_LOAD_EMOJI_MENU_MESSAGE_Y);
	cout << "Please enter a valid menu option!" << endl;
}