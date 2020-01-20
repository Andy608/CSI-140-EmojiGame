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
#include "GUIPlayScreen.h"
#include "GUIMainMenu.h"
#include "GUILoadEmoji.h"
#include "GUICreateEmoji.h"
#include "GUIFullEmojiListMenu.h"
#include "GUIDeleteEmoji.h"

int ticks;
int frames;
int secondCounter = 0;
int minuteCounter = 0;
bool isDebug;
bool isRunning;
bool doubleSpace = true;

int emojiCount = 0;
int currentEmojiIndex;
int money = 1000;

string emojiName[MAX_SAVES];
int emojiStatus[MAX_SAVES];
int emojiAge[MAX_SAVES];
int emojiHealth[MAX_SAVES];
int emojiEmotion[MAX_SAVES];
int emojiHunger[MAX_SAVES];
int emojiLoveCounter[MAX_SAVES];
int emojiSleepCounter[MAX_SAVES];

Screen currentScreen;

/*
	The main game loop for the emoji game.
	All main logic is controlled from here.
*/
void loop()
{
	double lastTime;
	double currentTime;
	double deltaTime;
	double accumulatedTime = 0;
	isDebug = false;
	isRunning = true;
	switchScreen(MainMenu);
	readFromFile();

	lastTime = chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now().time_since_epoch()).count();

	while (isRunning)
	{
		currentTime = chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now().time_since_epoch()).count();
		deltaTime = (currentTime - lastTime) / 1000000000.0;
		lastTime = currentTime;
		accumulatedTime += deltaTime;

		while (accumulatedTime >= TIME_SLICE)
		{
			accumulatedTime -= TIME_SLICE;
			update();
			render();
			getInput();
		}
	}
	//Save the game when the user exits.
	writeToFile();
}

/*
	Called every tick. 60 ticks per second.
*/
void update()
{
	ticks++;
	if (ticks % TICKS_PER_SECOND == 0)
	{
		if (isDebug)
		{
			cout << "Seconds: " << secondCounter << " | Ticks: " << ticks << " | Frames: " << frames << endl;
		}

		//Ticks needs to extend to 4 seconds because I use it up to 4 seconds in PlayScreen file.
		if (ticks % TICKS_PER_SECOND * 4 == 0)
		{
			ticks = 0;
		}
		frames = 0;
		secondCounter++;

		if (secondCounter % SECONDS_PER_MINUTE == 0)
		{
			if (isDebug)
			{
				cout << "Minutes: " << minuteCounter << endl;
			}

			minuteCounter++;
			secondCounter = 0;
		}
		else if (secondCounter % (SECONDS_PER_MINUTE / 10) == 0)
		{
			if (currentScreen == PlayScreen)
			{
				updateAgeHealthAndHunger();
			}
		}
	}
}


char buffer[MAX_INPUT_LENGTH];
int point = 0;

/*
	Handle input every tick.
*/
void getInput()
{
	//While a key is pressed
	while (_kbhit()) {

		//Get the character that was pressed.
		char input = _getch();

		if (point > MAX_INPUT_LENGTH - 1)
		{
			point = MAX_INPUT_LENGTH - 1;
		}
		
		//Depending on which screen, handle the input differently.
		if (currentScreen == MainMenu)
		{
			handleMainMenuInput(input);
		}
		else if (currentScreen == LoadEmojiMenu)
		{
			handleEmojiLoadMenuInput(input);
		}
		else if (currentScreen == CreateEmojiMenu)
		{
			handleCreateEmojiMenuInput(input);
		}
		else if (currentScreen == FullEmojiListMenu)
		{
			handleFullEmojiListMenu(input);
		}
		else if (currentScreen == DeleteEmojiMenu)
		{
			handleDeleteEmojiMenu(input);
		}
		else if (currentScreen == PlayScreen)
		{
			handlePlayScreenInput(input);
		}
	}
}

/*
	Render the screen every tick.
*/
void render()
{
	frames++;

	if (!isDebug)
	{
		if (currentScreen == MainMenu)
		{
			if (ticks % (TICKS_PER_SECOND / 2) == 0)	//Render main menu at 2 ticks per second.
			{
				updateMainMenu();
			}
		}
		else if (currentScreen == LoadEmojiMenu)
		{
			if (ticks % (TICKS_PER_SECOND / 2) == 0)	//Render load emoji menu at 2 ticks per second.
			{
				updateLoadEmojiMenu();
			}
		}
		else if (currentScreen == FullEmojiListMenu)	//Render full emoji menu at 2 ticks per second.
		{
			if (ticks % (TICKS_PER_SECOND / 2) == 0)
			{
				updateFullEmojiListMenu();
			}
		}
		else if (currentScreen == DeleteEmojiMenu)		//Render delete emoji at 2 ticks per second.
		{
			if (ticks % (TICKS_PER_SECOND / 2) == 0)
			{
				updateDeleteEmojiMenu();
			}
		}
		else if (currentScreen == PlayScreen)			//Render play screen at varying ticks per second depending on emoji emotion.
		{
			updatePlayScreen(ticks);
		}
	}
}

/*
	Take in new screen.
	Draw new screen.
*/
void switchScreen(Screen newScreen)
{
	clearScreen();
	currentScreen = newScreen;
	switch (currentScreen)
	{
	case MainMenu:
	{
		drawMainMenu();
		updateMainMenu();
		break;
	}
	case LoadEmojiMenu: 
	{
		drawLoadEmojiMenu();
		updateLoadEmojiMenu();
		break;
	}
	case CreateEmojiMenu:
	{
		drawCreateEmojiMenu();
		break;
	}
	case FullEmojiListMenu:
	{
		drawFullEmojiListMenu();
		updateFullEmojiListMenu();
		break;
	}
	case DeleteEmojiMenu:
	{
		drawDeleteEmojiMenu();
		updateDeleteEmojiMenu();
		break;
	}
	case PlayScreen:
	{
		drawPlayScreen();
		updatePlayScreen(ticks);
		break;
	}
	}
}

/*
	Set running to false so the game loop exits.
*/
void quitGame()
{
	isRunning = false;
}

/*
	Set whether cursor to show or not.
*/
void showCursor(bool show)
{
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(windowHandle, &cursorInfo);
	cursorInfo.bVisible = show;
	SetConsoleCursorInfo(windowHandle, &cursorInfo);
}

/*
	Returns the console cursor x position.
*/
int getConsoleCursorX()
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo))
	{
		return -1;
	}
	return bufferInfo.dwCursorPosition.X;
}

/*
	Returns the console cursor y position.
*/
int getConsoleCursorY()
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	COORD result;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo))
	{
		return -1;
	}
	return bufferInfo.dwCursorPosition.Y;
}

/*
	Returns the console width.
*/
int getConsoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	return columns;
}

/*
	Returns the console height.
*/
int getConsoleHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return rows;
}

/*
	Sets the cursor to the correct position to draw in the center of the screen depending on the width entered.
*/
void setCursorForCenterText(int width)
{
	setCursorPos((getConsoleWidth() - width) / 2, getConsoleCursorY());
}

/*
	Sets the cursor to the correct position to draw the given string at the center of the width entered.
*/
string centerText(int width, string text)
{
	if (width < text.length())
	{
		return "TEXT IS TOO LONG FOR CENTERING";
	}

	string space;
	space.assign(((width - text.length()) / 2), ' ');
	text = space + text + space;

	if (text.length() < width)
	{
		text = text + " ";
	}
	else if (text.length() > width)
	{
		text.pop_back();
	}

	return text;
}

/*
	Draws a line across the screen at the given line height.
*/
void drawLine(int lineHeight)
{
	int width = getConsoleWidth();
	string line;
	line.assign(width, '=');

	setCursorPos(0, lineHeight);
	cout << line << endl;
}

/*
	Deletes a user from the arrays and shifts all the other entries down by one index.
*/
void deleteUser(int userIndex)
{
	if (userIndex < 0) userIndex = 0;
	else if (userIndex >= MAX_SAVES) userIndex = MAX_SAVES - 1;

	for (int i = 0; i < MAX_SAVES - 1; i++)
	{
		if (i >= userIndex)
		{
			emojiName[i] = emojiName[i + 1];
			emojiStatus[i] = emojiStatus[i + 1];
			emojiAge[i] = emojiAge[i + 1];
			emojiHealth[i] = emojiHealth[i + 1];
			emojiEmotion[i] = emojiEmotion[i + 1];
			emojiHunger[i] = emojiHunger[i + 1];
			emojiLoveCounter[i] = emojiLoveCounter[i + 1];
			emojiSleepCounter[i] = emojiSleepCounter[i + 1];
		}
	}

	emojiCount--;
}

/*
	Writes all of the data to a file for storage.
*/
void writeToFile()
{
	ofstream write;
	write.open(EMOJI_FILE);

	if (write)
	{
		write << money;
		for (int i = 0; i < emojiCount; i++)
		{
			write << endl << emojiName[i];
			write << endl << emojiStatus[i];
			write << endl << emojiAge[i];
			write << endl << emojiHealth[i];
			write << endl << emojiEmotion[i];
			write << endl << emojiHunger[i];
			write << endl << emojiLoveCounter[i];
			write << endl << emojiSleepCounter[i];
		}
	}

	write.close();
}

/*
	Reads all of the data from the file.
*/
void readFromFile()
{
	ifstream read;
	read.open(EMOJI_FILE, fstream::in | fstream::out | fstream::app);
	read >> money;

	//If the file is not created, create it.
	if (!read)
	{
		read.open(EMOJI_FILE, fstream::in | fstream::out | fstream::trunc);
	}

	//While we are not at the end of the file, continue to read info.
	while (!read.eof())
	{
		read >> emojiName[emojiCount];
		read >> emojiStatus[emojiCount];
		read >> emojiAge[emojiCount];
		read >> emojiHealth[emojiCount];
		read >> emojiEmotion[emojiCount];
		read >> emojiHunger[emojiCount];
		read >> emojiLoveCounter[emojiCount];
		read >> emojiSleepCounter[emojiCount];
		emojiCount++;
	}

	read.close();
}