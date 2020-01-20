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
#ifndef GUIPLAYSCREEN_H
#define GUIPLAYSCREEN_H

#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include "Loop.h"
using namespace std;

const int EMOJI_SIZE = 9;
const int ANIMATION_LENGTH = 3;

//Used when emoji is happy
const string happyEmoji[] = { "(^-^)", "( ^-^)", "(^-^ )" };
const string happyRandomEmoji[] = { "(^.^)", "( ^.^)", "(^.^ )" };

//Used when emoji is content
const string contentEmoji[] = { "(^_^)", "( ^_^)", "(^_^ )" };

//Used when emoji is sad / sick
const string sadEmoji[] = { "(-_-)", "( -_-)", "(-_- )" };
const string sadRandomEmoji[] = { "(-.-)", "( -.-)", "(-.- )" };

//Used when emoji is happy and sleeping
const string sleepingEmoji[] = { "(-.-) zZz", "( -.-) zZz", "(-.- ) zZz" };

//Used when emoji is sad and sleeping
const string sleepingDepressedEmoji[] = { "(_._) zZz", "( _._) zZz", "(_._ ) zZz" };

const string deadLenny = "(X _ X)";

const HANDLE windowHandle = GetStdHandle(STD_OUTPUT_HANDLE);
const int MAX_INPUT_LENGTH = 512;
const int ENTER_KEY = 13;
const int TAB_KEY = 9;
const int ESC_KEY = 27;
const int BACKSPACE_KEY = 8;

const int ERROR_PLAY_SCREEN_MESSAGE_Y = 27;
const int ERROR_PLAY_SCREEN_MESSAGE_X = 0;
const int ERROR_PLAY_SCREEN_MESSAGE_LENGTH_X = 50;
const int ERROR_PLAY_SCREEN_MESSAGE_LENGTH_Y = 1;

const int PLAY_EMOTION_INCREASE = 10;
const int FEED_EMOTION_INCREASE = 5;
const int MEDICINE_EMOTION_INCREASE = 20;
const int SLEEP_EMOTION_INCREASE = 5;
const int MAX_EMOTION = 100;

const int NO_ATTENTION_IN_SECONDS = 30;

const int PLAY_COST = 50;
const int FEED_COST = 50;
const int MEDICINE_COST = 200;
const int SLEEP_COST = 50;

const int FEED_INCREASE = 10;
const int MAX_HUNGER = 100;

const int HEALTH_INCREASE = 20;
const int MAX_HEALTH = 100;

const int SLEEP_DEPRIVED = 30 * TICKS_PER_SECOND;

const enum Keys { ONE = 49, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };

//General Status
const enum EmojiStatus { Dead, Awake, Bored, Sleepy, Asleep };

//Numnbers in age
//Baby			= 0 - 5
//Child			= 6 - 12
//Teen			= 13 - 17
//Adult			= 18 - 64
//Elderly		= 65 - 89
//Ancient		= 90+
enum AgeLevel { Baby = 5, Child = 12, Teen = 17, Adult = 64, Elderly = 89, Ancient };

//Health level.
//Healthy			= 91 - 100
//MildlySick		= 81 - 90
//ModeratelySick	= 51 - 80
//SuperSick			= 21 - 50
//DealthlySick		=  1 - 20
//DeadSick			=  0
enum HealthLevel { Healthy = 100, MildlySick = 90, ModeratelySick = 80, SuperSick = 50, DeathlySick = 20, DeadSick = 0};

//Dictates the speed at which the emoji changes
//Excited			= 5 ticks	 / second
//Happy				= 2 ticks	 / second
//Moderate			= 1 tick	 / second
//Bored				= 1 ticks	 / second
//Neglected			= 0.5 tick	 / second
//Depressed			= 0.25 ticks / second

//Excited			= 100
//Happy				= 81 - 99
//Content			= 61 - 80
//Neglected			= 21 - 60
//Depressed			=  1 - 20
//DeadEmotion		=  0
enum EmotionLevel { Excited = 100, Happy = 99, Content = 80, Neglected = 60, Depressed = 20, DeadEmotion = 0 };

//Hunger level.
//NotHungry			= 81 - 100
//Hungry			= 51 - 80
//VeryHungry		= 21 - 50
//Starving			=  0 - 20
enum HungerLevel { Full = 100, Hungry = 80, VeryHungry = 50, Starving = 20, DeadHungry = 0 };

enum DeathType { AgeRelated, HungerRelated, HealthRelated, EmotionRelated };

string wiggleEmoji(string emojiFace);
string getEmoji(EmojiStatus status, EmotionLevel emotion);
EmojiStatus getStatusLevel(int emojiIndex);
AgeLevel getAgeLevel(int emojiIndex);
HealthLevel getHealthLevel(int emojiIndex);
EmotionLevel getEmotionLevel(int emojiIndex);
HungerLevel getHungerLevel(int emojiIndex);

void initNewEmoji(string name);
void drawPlayScreen();
void printEmojiStats();
void updateInfo(string info);
void setDeathScreen();
void updatePlayScreen(int ticks);
void redrawEmoji();
void updateEmotion(int ticks);
void updateStatus(int ticks);
void updateAgeHealthAndHunger();
void updateMoney();
void handlePlayScreenInput(char input);
void prepareConsoleCursorForErrorMessage();
EmojiStatus getStatusLevel(int emojiIndex);
AgeLevel getAgeLevel(int emojiIndex);
HealthLevel getHealthLevel(int emojiIndex);
HungerLevel getHungerLevel(int emojiIndex);
EmotionLevel getEmotionLevel(int emojiIndex);
int getMoney();
void clearScreenPortion(short startX, short startY, short lengthX, short lengthY);
void clearScreen();
void setCursorPos(short x, short y);
string getEmoji(EmojiStatus status, EmotionLevel emotion);
string wiggleEmoji(string emojiFace);
void setDead();
void putEmojiToBed();
void giveEmojiAttention();
void feedEmoji();
void healEmoji();
string emojiStatusToString(EmojiStatus status);
string ageLevelToString(AgeLevel ageLevel);
string healthLevelToString(HealthLevel healthLevel);
string emotionLevelToString(EmotionLevel emotionLevel);
string hungerLevelToString(HungerLevel hungerLevel);
string deathTypeToString(DeathType deathType);

#endif