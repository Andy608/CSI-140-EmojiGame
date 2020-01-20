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
#ifndef LOOP_H
#define LOOP_H

#include <iostream>
#include <string>
#include <conio.h>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;

const int MAX_SAVES = 9;
extern int guiWidth;
const int TICKS_PER_SECOND = 60;
const int SECONDS_PER_MINUTE = 60;
const double TIME_SLICE = 1 / (double)TICKS_PER_SECOND;
const enum Screen { MainMenu, LoadEmojiMenu, CreateEmojiMenu, FullEmojiListMenu, DeleteEmojiMenu, PlayScreen };

extern int emojiCount;
extern int currentEmojiIndex;
extern int money;
extern int secondCounter;
extern int minuteCounter;
extern bool doubleSpace;

//name of emoji
extern string emojiName[];

//0 = dead, 1 = awake, 2 = asleep
extern int emojiStatus[];

//age
extern int emojiAge[];

//value between 0 - 100
extern int emojiHealth[];

//value between 0 - 100
extern int emojiEmotion[];

//value between 0 - 100
extern int emojiHunger[];

//stores int of seconds since last played with, fed, or given medicine
extern int emojiLoveCounter[];

//stores int of seconds since last slept.
extern int emojiSleepCounter[];

void loop();
void update();
void getInput();
void render();
void quitGame();
void switchScreen(Screen);
void showCursor(bool show);
int getConsoleCursorX();
int getConsoleCursorY();
int getConsoleWidth();
int getConsoleHeight();
void setCursorForCenterText(int width);
void drawLine(int lineHeight);
void deleteUser(int userIndex);
void writeToFile();
void readFromFile();
string centerText(int width, string text);

#endif