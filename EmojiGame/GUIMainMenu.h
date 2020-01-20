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
#pragma once
#ifndef GUIMAINMENU_H
#define GUIMAINMENU_H

#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

const int TITLE_LENGTH = 100;

const int ERROR_MAIN_MENU_MESSAGE_Y = 16;
const int ERROR_MESSAGE_X = 0;
const int ERROR_MESSAGE_LENGTH_X = 50;
const int ERROR_MESSAGE_LENGTH_Y = 1;

const int TITLE_EMOJI_X = 45;
const int TITLE_EMOJI_Y = 2;
const int TITLE_EMOJI_LENGTH_X = 8;
const int TITLE_EMOJI_LENGTH_Y = 1;


void drawMainMenu();
void handleMainMenuInput(char input);
void updateMainMenu();

#endif