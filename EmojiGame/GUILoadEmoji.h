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
#ifndef GUILOADEMOJI_H
#define GUILOADEMOJI_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int FILE_ATTRIBUTES = 5;
const int ERROR_LOAD_EMOJI_MENU_MESSAGE_Y = 24;
const int MAX_SLOT_PER_COLUMN = 5;
const int SLOT_OFFSET_X = 51;
const string EMOJI_FILE = "emoji.txt";

void drawLoadEmojiMenu();
void printAllEmojiNames(int cursorX, int cursorY, bool isDeleting);
void updateLoadEmojiMenu();
void handleEmojiLoadMenuInput(char input);

#endif