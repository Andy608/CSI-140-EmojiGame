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
#include "GUICreateEmoji.h"
#include "GUIPlayScreen.h"
#include "GUIMainMenu.h"

string potentialName;
const string NAME_DISPLAY = "_ _ _ _ _ _ _ _ _";
/*
	Draw the base create emoji menu.
*/
void drawCreateEmojiMenu()
{
	drawLine(0);
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "Let\'s create your new Emoji Pet") << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "---") << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	drawLine(6);

	cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "Here is your pet!") << endl;
	cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, getEmoji(Awake, Happy)) << endl;
	cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "What would you like to name them?") << endl;
	cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, NAME_DISPLAY) << endl;

	setCursorPos(0, 20);
	setCursorForCenterText(guiWidth); cout << "Press Enter to continue, or ESC to return to the Main Menu." << endl;
}

/*
	Handles the create emoji menu input.
*/
void handleCreateEmojiMenuInput(char input)
{
	if (input == ESC_KEY)
	{
		switchScreen(MainMenu);
		potentialName = "";
	}
	else if (input == ENTER_KEY)
	{
		currentEmojiIndex = emojiCount++;
		initNewEmoji(potentialName);
		potentialName = "";
		switchScreen(PlayScreen);
	}
	else
	{
		setCursorForCenterText(guiWidth);
		int cursorX = ((getConsoleWidth() - NAME_DISPLAY.length() - getConsoleCursorX()) / 2);

		if (input == BACKSPACE_KEY)
		{
			if (potentialName.length() > 0)
			{
				potentialName.pop_back();
				setCursorPos(cursorX + ((potentialName.length() + 1) * 2), 14);
				cout << "_";
			}
		}
		else if (potentialName.length() < 9) //Override line in console to character.
		{
			potentialName = potentialName + input;
			setCursorPos(cursorX+ (potentialName.length() * 2), 14);
			cout << input;
		}
		cout.flush();
	}
}