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
#include "GUIPlayScreen.h"

DeathType deathType;
bool setAwake = false;
bool setAsleep = false;
bool isDead = false;

/*
	Initializes the newly created emoji to have all the default values.
*/
void initNewEmoji(string name)
{
	emojiName[currentEmojiIndex] = name;
	emojiStatus[currentEmojiIndex] = Awake;
	emojiAge[currentEmojiIndex] = 0;
	emojiHealth[currentEmojiIndex] = Healthy;
	emojiEmotion[currentEmojiIndex] = Happy;
	emojiHunger[currentEmojiIndex] = Full;
	emojiLoveCounter[currentEmojiIndex] = 0;
	emojiSleepCounter[currentEmojiIndex] = 0;

	//Reset values.
	setAwake = false;
	setAsleep = false;
	isDead = false;

	//Writes the emoji to the file upon creation.
	writeToFile();
}

//Draw out the play menu screen.
void drawPlayScreen()
{
	if (getConsoleHeight() < 26)
	{
		doubleSpace = false;
	}

	string name = emojiName[currentEmojiIndex];
	string title = "Here is your pet: " + name;

	drawLine(0);
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, title) << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, getEmoji(getStatusLevel(currentEmojiIndex), getEmotionLevel(currentEmojiIndex))) << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << centerText(guiWidth, "-----------") << endl;
	printEmojiStats();
	setCursorForCenterText(guiWidth); cout << endl;
	drawLine(11);
	setCursorForCenterText(guiWidth); cout << endl;
	setCursorForCenterText(guiWidth); cout << "Money: $" << money << endl;
	if (doubleSpace) cout << endl;
	setCursorForCenterText(guiWidth); cout << " [$" << PLAY_COST << "] Press 1 to play with " << name << "." << endl;
	if (doubleSpace) cout << endl;
	setCursorForCenterText(guiWidth); cout << " [$" << FEED_COST << "] Press 2 to feed " << name << "." << endl;
	if (doubleSpace) cout << endl;
	setCursorForCenterText(guiWidth); cout << " [$" << SLEEP_COST << left << "] Press 3 to put " << name << " to bed." << endl;
	if (doubleSpace) cout << endl;
	setCursorForCenterText(guiWidth); cout << "[$" << MEDICINE_COST << left << "] Press 4 to give " << name << " medicine." << endl << endl;
	if (doubleSpace) cout << endl;
	setCursorForCenterText(guiWidth); cout << "Press ESC or ENTER to save and return to the Main Menu." << endl;
}

/*
	Prints out the emoji stats nicely in the center of the screen.
*/
void printEmojiStats()
{
	string name = emojiName[currentEmojiIndex];
	
	EmojiStatus status = getStatusLevel(currentEmojiIndex);
	
	int age = emojiAge[currentEmojiIndex];
	AgeLevel ageLevel = getAgeLevel(currentEmojiIndex);
	
	int health = emojiHealth[currentEmojiIndex];
	HealthLevel healthLevel = getHealthLevel(currentEmojiIndex);

	int emotion = emojiEmotion[currentEmojiIndex];
	EmotionLevel emotionLevel = getEmotionLevel(currentEmojiIndex);

	int hunger = emojiHunger[currentEmojiIndex];
	HungerLevel hungerLevel = getHungerLevel(currentEmojiIndex);

	string updateInfo =
	name + " is " + emojiStatusToString(status)
		 + " | Age: " + to_string(age) + ", " + ageLevelToString(ageLevel)
		 + " | Health: " + to_string(health) + (health == 0 ? "" : ", ") + healthLevelToString(healthLevel)
		 + " | Emotion: " + to_string(emotion) + (emotion == 0 ? "" : ", ") + emotionLevelToString(emotionLevel)
		 + " | Hunger: " + to_string(hunger) + (hunger == 0 ? "" : ", ") + hungerLevelToString(hungerLevel);

	string updateInfo2;
	if (updateInfo.length() > getConsoleWidth())
	{
		updateInfo = name + " is " + emojiStatusToString(status)
			+ " | Age: " + to_string(age) + ", " + ageLevelToString(ageLevel)
			+ " | Health: " + to_string(health) + (health == 0 ? "" : ", ") + healthLevelToString(healthLevel);
		
		updateInfo2 = " | Emotion: " + to_string(emotion) + (emotion == 0 ? "" : ", ") + emotionLevelToString(emotionLevel)
			+ " | Hunger: " + to_string(hunger) + (hunger == 0 ? "" : ", ") + hungerLevelToString(hungerLevel);
	}

	setCursorPos(0, 0);
	int cursorX = getConsoleCursorX();
	int cursorY = 8;
	int width = getConsoleWidth();
	cout.flush();

	clearScreenPortion(cursorX, cursorY, width, 2);
	setCursorPos(cursorX, cursorY);
	cout << centerText(width, updateInfo);
	setCursorPos(cursorX, cursorY + 1);
	cout << centerText(width, updateInfo2);
}

/*
	Prints out info messages/events about whats happening with your emoji.
*/
void updateInfo(string info)
{
	setCursorPos(0, 0);
	int cursorX = getConsoleCursorX();
	int cursorY = 5;
	int width = getConsoleWidth();
	cout.flush();

	clearScreenPortion(cursorX, cursorY, width, 1);
	cout << centerText(width, info);
}

/*
	Prints out the final death update before screen stops updating.
*/
void setDeathScreen()
{
	printEmojiStats();
	redrawEmoji();
}

/*
	Updates the screen every tick while emoji is alive.
*/
void updatePlayScreen(int ticks)
{
	if (ticks % TICKS_PER_SECOND / 2 == 0)
	{
		clearScreenPortion(ERROR_PLAY_SCREEN_MESSAGE_X, doubleSpace ? ERROR_PLAY_SCREEN_MESSAGE_Y : ERROR_PLAY_SCREEN_MESSAGE_Y - 6, getConsoleWidth(), ERROR_PLAY_SCREEN_MESSAGE_LENGTH_Y);
	}

	if (ticks % TICKS_PER_SECOND == 0)
	{
		setCursorPos(0, 0);
		int cursorX = getConsoleCursorX();
		int cursorY = 6;
		int width = getConsoleWidth();
		cout.flush();

		clearScreenPortion(cursorX, cursorY, width, 1);
	}

	if (ticks % TICKS_PER_SECOND == 0)
	{
		int &loveCounter = emojiLoveCounter[currentEmojiIndex];
		loveCounter++;
	}

	if (getStatusLevel(currentEmojiIndex) == Dead)
	{
		return;
	}

	EmotionLevel emotionLevel = getEmotionLevel(currentEmojiIndex);
	updateStatus(ticks);
	updateEmotion(ticks);

	if ((emotionLevel == Excited && (ticks % (TICKS_PER_SECOND / 5) == 0))
	|| (emotionLevel == Happy && (ticks % (TICKS_PER_SECOND / 2) == 0))
	|| ((emotionLevel == Content || emotionLevel == Bored) && ((ticks % TICKS_PER_SECOND) == 0))
	||  (emotionLevel == Neglected && (ticks % (TICKS_PER_SECOND * 2) == 0))
	||  (emotionLevel == Depressed && (ticks % (TICKS_PER_SECOND * 4) == 0)))
	{
		printEmojiStats();
		redrawEmoji();
	}
}

/*
	Redraws the emoji on the screen for animation.
*/
void redrawEmoji()
{
	EmojiStatus status = getStatusLevel(currentEmojiIndex);
	EmotionLevel emotion = getEmotionLevel(currentEmojiIndex);
	string emoji = getEmoji(status, emotion);

	setCursorForCenterText(guiWidth);
	emoji = centerText(guiWidth, emoji);

	setCursorForCenterText(guiWidth);
	int cursorX = getConsoleCursorX();
	int cursorY = 4;

	clearScreenPortion(cursorX, cursorY, guiWidth, 1);
	setCursorPos(cursorX, cursorY);
	cout << emoji;
}

/*
	Updates the emoji's emotions every tick.
*/
void updateEmotion(int ticks)
{
	EmojiStatus statusLevel = getStatusLevel(currentEmojiIndex);
	AgeLevel ageLevel = getAgeLevel(currentEmojiIndex);
	HealthLevel healthLevel = getHealthLevel(currentEmojiIndex);
	HungerLevel hungerLevel = getHungerLevel(currentEmojiIndex);

	int &emotion = emojiEmotion[currentEmojiIndex];

	if (statusLevel == Dead)
	{
		emotion = DeadEmotion;
		return;
	}

	int &loveCounter = emojiLoveCounter[currentEmojiIndex];

	if (loveCounter > NO_ATTENTION_IN_SECONDS)
	{
		if (ticks % TICKS_PER_SECOND == 0)
		{
			emotion = max(emotion - (rand() % 5 + 1), Depressed);
		}
	}
	else
	{
		EmojiStatus status = getStatusLevel(currentEmojiIndex);

		if ((hungerLevel == Full) && (healthLevel == Healthy) && (ageLevel < Elderly) && (status != Asleep) && (rand() % TICKS_PER_SECOND == 0))
		{
			if (ticks % TICKS_PER_SECOND == 0)
			{
				updateInfo(emojiName[currentEmojiIndex] + " is excited!");
				emotion = Excited;
			}
		}

		if (status == Asleep && emotion == Excited)
		{
			emotion = Happy;
		}

		if (hungerLevel < Hungry || healthLevel < MildlySick || statusLevel == Bored)
		{
			emotion = Content;
		}

		if (hungerLevel < VeryHungry)
		{
			emotion = Neglected;
		}
	}

	//Add money to the player's money if the emoji is happy.
	if (emotion == Excited)
	{
		if (ticks % (TICKS_PER_SECOND / 2) == 0)
		{
			money += 20;
			updateMoney();
		}
	}
	else if (emotion == Happy)
	{
		if (ticks % (TICKS_PER_SECOND / 2)== 0)
		{
			money += 10;
			updateMoney();
		}
	}
	else if (emotion == Content)
	{
		if (ticks % TICKS_PER_SECOND == 0)
		{
			money += 5;
			updateMoney();
		}
	}
	
	if (emotion == Neglected)
	{
		updateInfo(emojiName[currentEmojiIndex] + " feels neglected.");
	}
	else if (emotion == Depressed)
	{
		updateInfo(emojiName[currentEmojiIndex] + " is depressed.");
	}

	if (emotion == DeadEmotion)
	{
		isDead = true;
	}
}

/*
	Updates the status of the emoji (whether it is sleeping, alive, dead, bored, etc)
*/
void updateStatus(int ticks)
{
	int &status = emojiStatus[currentEmojiIndex];
	if (isDead || getHealthLevel(currentEmojiIndex) == DeadSick || getEmotionLevel(currentEmojiIndex) == DeadEmotion || getHungerLevel(currentEmojiIndex) == DeadHungry)
	{
		status = Dead;
		setDead();
		updateInfo(deathTypeToString(deathType));
		return;
	}

	if (setAwake)
	{
		status = Awake;
		setAwake = true;
		setAsleep = false;
	}
	
	if (setAsleep)
	{
		status = Asleep;
		setAsleep = true;
		setAwake = false;
	}

	int &sleepCounter = emojiSleepCounter[currentEmojiIndex];

	if (status == Asleep)
	{
		sleepCounter = max(sleepCounter - 5, 0);
	}
	else
	{
		sleepCounter++;
	}

	if (sleepCounter == 0)
	{
		updateInfo((emojiName[currentEmojiIndex] + " is fully rested!"));
		setAwake = true;
	}
	else
	{
		setAwake = false;
	}

	if ((sleepCounter > SLEEP_DEPRIVED) && rand() % 3 == 0)
	{
		status = Sleepy;
	}

	int &loveCounter = emojiLoveCounter[currentEmojiIndex];

	if (loveCounter > NO_ATTENTION_IN_SECONDS && rand() % 2 == 0)
	{
		status = Bored;
	}
}

/*
	Update the age, health, and hunger of the emoji.
*/
void updateAgeHealthAndHunger()
{

	if (getStatusLevel(currentEmojiIndex) == Dead)
	{
		return;
	}

	int updateAge = rand() % 4;
	int updateHunger = rand() % 2;

	int &hunger = emojiHunger[currentEmojiIndex];
	int &health = emojiHealth[currentEmojiIndex];
	int &age = emojiAge[currentEmojiIndex];
	
	if (updateAge == 0)
	{
		age++;
		if (age - 1 == Baby && age > Baby)
		{
			updateInfo(emojiName[currentEmojiIndex] + " is now a child!");
		}
		else if (age - 1 == Child && age > Child)
		{
			updateInfo(emojiName[currentEmojiIndex] + " is now a teenager!");
		}
		else if (age - 1 == Teen && age > Teen)
		{
			updateInfo(emojiName[currentEmojiIndex] + " is now an adult!");
		}
		else if (age - 1 == Adult && age > Adult)
		{
			updateInfo(emojiName[currentEmojiIndex] + " is now an elder!");
		}
		else if (age - 1 == Elderly && age > Elderly)
		{
			updateInfo(emojiName[currentEmojiIndex] + " is now ancient!");
		}
	}

	int updateHealth = rand() % (health + hunger) != 0 ? (health + hunger) : 1;
	int updateHealth2 = rand() % 5;
	bool dropHealth = (hunger == 0) || (emojiEmotion[currentEmojiIndex] == Depressed);

	if (dropHealth)
	{
		health = max(health - (rand() % 10), 0);
	}

	if (updateHealth < 20 || updateHealth2 == 0)
	{

		if (health > 0)
		{
			health = max(health - rand() % 5, 0);
		}
	}
	
	if (updateHunger == 0)
	{
		if (hunger > 0)
		{
			hunger = max(hunger - rand() % 5, 0);
		}
	}

	if (hunger == Hungry)
	{
		updateInfo(emojiName[currentEmojiIndex] + " is hungry.");
	}
	else if (hunger == VeryHungry)
	{
		updateInfo(emojiName[currentEmojiIndex] + " is very hungry.");
	}
	else if (hunger == Starving)
	{
		updateInfo(emojiName[currentEmojiIndex] + " is starving.");
	}

	AgeLevel ageLevel = getAgeLevel(currentEmojiIndex);

	if (hunger == 0 || health == 0 || (ageLevel > Elderly && rand() % 20 == 0))
	{
		isDead = true;
	}
}

/*
	Update the money gui on the screen.
*/
void updateMoney()
{
	setCursorForCenterText(guiWidth);
	int cursorX = getConsoleCursorX();
	clearScreenPortion(cursorX + 8, 13, 10, 1);
	setCursorPos(cursorX + 8, 13);
	cout << money;
}

/*
	Handles the input from the user every tick.
*/
void handlePlayScreenInput(char input)
{
	switch (input)
	{
	case ESC_KEY: case ENTER_KEY:
	{
		writeToFile();
		switchScreen(MainMenu);
		return;
	}
	}

	if (getStatusLevel(currentEmojiIndex) != Dead)
	{
		switch (input)
		{
		case ONE:
		{
			//Give Emoji attention
			if (money >= PLAY_COST)
			{
				giveEmojiAttention();
				updateMoney();
			}
			else
			{
				prepareConsoleCursorForErrorMessage();
				cout << "You do not have enough money to play with " << emojiName[currentEmojiIndex] << ".";
			}
			return;
		}
		case TWO:
		{
			//Feed emoji
			if (money >= FEED_COST)
			{
				feedEmoji();
				updateMoney();
			}
			else
			{
				prepareConsoleCursorForErrorMessage();
				cout << "You do not have enough money to feed " << emojiName[currentEmojiIndex] << ".";
			}
			return;
		}
		case THREE:
		{
			//Sleep / wake emoji
			//update the text
			EmojiStatus status = getStatusLevel(currentEmojiIndex);

			if (status == Asleep)
			{
				setAwake = true;
			}
			else
			{
				if (money >= SLEEP_COST)
				{
					putEmojiToBed();
					updateMoney();
				}
				else
				{
					prepareConsoleCursorForErrorMessage();
					cout << "You do not have enough money to put " << emojiName[currentEmojiIndex] << " to bed.";
				}
			}
			return;
		}
		case FOUR:
		{
			//Give emoji medicine
			if (money > MEDICINE_COST)
			{
				healEmoji();
				updateMoney();
			}
			else
			{
				prepareConsoleCursorForErrorMessage();
				cout << "You do not have enough money to give " << emojiName[currentEmojiIndex] << " medicine.";
			}
			return;
		}
		}
	}
	else
	{
		prepareConsoleCursorForErrorMessage();
		cout << "Game Over! Your emoji is dead." << endl;
		return;
	}

	prepareConsoleCursorForErrorMessage();
	cout << "Please enter a valid menu option!" << endl;
}

/*
	Set the cursor to desired position for the error message.
*/
void prepareConsoleCursorForErrorMessage()
{
	setCursorForCenterText(guiWidth);
	int cursorX = getConsoleCursorX();

	clearScreenPortion(cursorX + ERROR_PLAY_SCREEN_MESSAGE_X, doubleSpace ? ERROR_PLAY_SCREEN_MESSAGE_Y : ERROR_PLAY_SCREEN_MESSAGE_Y - 6, ERROR_PLAY_SCREEN_MESSAGE_LENGTH_X, ERROR_PLAY_SCREEN_MESSAGE_LENGTH_Y);
	cout.flush();
	setCursorPos(cursorX + ERROR_PLAY_SCREEN_MESSAGE_X, doubleSpace ? ERROR_PLAY_SCREEN_MESSAGE_Y : ERROR_PLAY_SCREEN_MESSAGE_Y - 6);
}

/*
	Return the emoji status from index.
*/
EmojiStatus getStatusLevel(int emojiIndex)
{
	switch (emojiStatus[emojiIndex])
	{
	case 0: return Dead;
	case 1: return Awake;
	case 2: return Bored;
	case 3: return Sleepy;
	case 4: return Asleep;
	}
}

/*
Returns the age of the emoji.
*/
AgeLevel getAgeLevel(int emojiIndex)
{
	int age = emojiAge[emojiIndex];
	if (age > Elderly) return Ancient;
	else if (age > Adult) return Elderly;
	else if (age > Teen) return Adult;
	else if (age > Child) return Teen;
	else if (age > Baby) return Child;
	else return Baby;
}

/*
Returns the health of the emoji.
*/
HealthLevel getHealthLevel(int emojiIndex)
{
	int health = emojiHealth[emojiIndex];
	if (health > MildlySick) return Healthy;
	else if (health > ModeratelySick) return MildlySick;
	else if (health > SuperSick) return ModeratelySick;
	else if (health > DeathlySick) return SuperSick;
	else if (health > DeadSick) return DeathlySick;
	else return DeadSick;
}

/*
Returns the hunger of the emoji.
*/
HungerLevel getHungerLevel(int emojiIndex)
{
	int hunger = emojiHunger[emojiIndex];
	if (hunger > Hungry) return Full;
	else if (hunger > VeryHungry) return Hungry;
	else if (hunger > Starving) return VeryHungry;
	else if (hunger > DeadHungry) return Starving;
	else DeadHungry;
}

/*
Returns the emotion of the emoji.
*/
EmotionLevel getEmotionLevel(int emojiIndex)
{
	int emotion = emojiEmotion[emojiIndex];
	if (emotion > Happy) return Excited;
	else if (emotion > Content) return Happy;
	else if (emotion > Neglected) return Content;
	else if (emotion > Depressed) return Neglected;
	else if (emotion > DeadEmotion) return Depressed;
	else return DeadEmotion;
}

/*
Returns the amount of money the player has.
*/
int getMoney()
{
	return money;
}

/*
	Clears a select area of the console. This is better then clearing the whole screen because this does not flicker as much.
*/
void clearScreenPortion(short startX, short startY, short lengthX, short lengthY)
{

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

	if (!GetConsoleScreenBufferInfo(windowHandle, &bufferInfo))
	{
		return;
	}

	string clear;
	clear.assign(lengthX, ' ');

	for (int i = 0; i < lengthY; i++)
	{
		setCursorPos(startX, startY + i);
		cout << clear;
		cout.flush();
	}

}

/*
	Clears the whole console.
*/
void clearScreen()
{
	system("CLS");
}

/*
	Sets the cursor position in the console.
*/
void setCursorPos(short x, short y)
{
	cout.flush();
	COORD coord = { x, y };
	SetConsoleCursorPosition(windowHandle, coord);
}

/*
	Looks at the emoji's emotion and status levels and decides what face to return.
*/
string getEmoji(EmojiStatus status, EmotionLevel emotion)
{
	string emojiFace;

	if (status == Dead)
	{
		return deadLenny;
	}
	else if (status != Asleep)
	{
		//0 = Excited, 1 = Happy, 2 = Content
		if (emotion > Content)
		{
			int faceType = rand() % 4;
			switch (faceType)
			{
			case 0: emojiFace = happyRandomEmoji[rand() % ANIMATION_LENGTH]; break;
			default: emojiFace = happyEmoji[rand() % ANIMATION_LENGTH]; break;
			}

			return wiggleEmoji(emojiFace);
		}
		else if (emotion == Content)
		{
			emojiFace = contentEmoji[rand() % ANIMATION_LENGTH];
			return wiggleEmoji(emojiFace);
		}
		else
		{
			int faceType = rand() % 4;
			switch (faceType)
			{
			case 0: emojiFace = sadRandomEmoji[rand() % ANIMATION_LENGTH]; break;
			default: emojiFace = sadEmoji[rand() % ANIMATION_LENGTH]; break;
			}

			return emojiFace;
		}
	}
	else
	{
		if (emotion < Content)
		{
			emojiFace = sleepingDepressedEmoji[rand() % ANIMATION_LENGTH];
		}
		else
		{
			emojiFace = sleepingEmoji[rand() % ANIMATION_LENGTH];
		}

		return emojiFace;
	}
}

string wiggleEmoji(string emojiFace)
{
	int randSpace = rand() % ANIMATION_LENGTH;
	switch (randSpace)
	{
	case 1: emojiFace = " " + emojiFace;
	case 2: emojiFace = emojiFace + " ";
	}

	return emojiFace;
}

/*
	Sets the emoji to dead.
	Sets the death type to what killed it.
*/
void setDead()
{
	emojiStatus[currentEmojiIndex] = Dead;

	if (getHungerLevel(currentEmojiIndex) == DeadHungry)
	{
		deathType = HungerRelated;
	}
	else if (getHealthLevel(currentEmojiIndex) == DeadSick)
	{
		deathType = HealthRelated;
	}
	else if (getEmotionLevel(currentEmojiIndex) == DeadEmotion)
	{
		deathType = EmotionRelated;
	}
	else
	{
		deathType = AgeRelated;
	}

	setDeathScreen();
}

/*
	Puts emoji to sleep.
*/
void putEmojiToBed()
{
	money -= SLEEP_COST;
	int &loveCounter = emojiLoveCounter[currentEmojiIndex];
	loveCounter = 0;
	int &emotion = emojiEmotion[currentEmojiIndex];
	emotion = min(emotion + SLEEP_EMOTION_INCREASE, MAX_EMOTION - 1);
	int &health = emojiHealth[currentEmojiIndex];
	health = min(health + (HEALTH_INCREASE / 2), MAX_HEALTH);
	setAsleep = true;
}

/*
	Gives emoji attention.
*/
void giveEmojiAttention()
{
	money -= PLAY_COST;
	int &loveCounter = emojiLoveCounter[currentEmojiIndex];
	loveCounter = 0;
	int &emotion = emojiEmotion[currentEmojiIndex];
	emotion = min(emotion + PLAY_EMOTION_INCREASE, MAX_EMOTION - 1);
}

/*
	Feeds the emoji.
*/
void feedEmoji()
{
	int &hunger = emojiHunger[currentEmojiIndex];

	if (hunger == Full)
	{
		prepareConsoleCursorForErrorMessage();
		cout << "Your emoji is full!" << endl;
		return;
	}

	money -= FEED_COST;
	int &loveCounter = emojiLoveCounter[currentEmojiIndex];
	loveCounter = 0;
	int &emotion = emojiEmotion[currentEmojiIndex];
	emotion = min(emotion + FEED_EMOTION_INCREASE, MAX_EMOTION - 1);
	hunger = min(hunger + FEED_INCREASE, MAX_HUNGER);
}

//Heals the emoji.
void healEmoji()
{
	int &health = emojiHealth[currentEmojiIndex];

	if (health == Full)
	{
		prepareConsoleCursorForErrorMessage();
		cout << "Your emoji already has full health!" << endl;
		return;
	}

	money -= MEDICINE_COST;
	int &loveCounter = emojiLoveCounter[currentEmojiIndex];
	loveCounter = 0;
	int &emotion = emojiEmotion[currentEmojiIndex];
	emotion = min(emotion + MEDICINE_EMOTION_INCREASE, MAX_EMOTION - 1);
	health = min(health + HEALTH_INCREASE, MAX_HEALTH);
}

/*
	Returns the emoji status as a string.
*/
string emojiStatusToString(EmojiStatus status)
{
	switch (status)
	{
	case Dead: return "Dead";
	case Awake: return "Awake";
	case Bored: return "Bored";
	case Sleepy: return "Sleepy";
	case Asleep: return "Sleeping";
	}

	return "UNKNOWN EMOJI STATUS";
}

/*
	Returns the age level as a string.
*/
string ageLevelToString(AgeLevel ageLevel)
{
	switch (ageLevel)
	{
	case Baby: return "Baby";
	case Child: return "Child";
	case Teen: return "Teen";
	case Adult: return "Adult";
	case Elderly: return "Elderly";
	case Ancient: return "Ancient";
	}

	return "UNKNOWN AGE LEVEL";
}

/*
	Returns the health level as a string.
*/
string healthLevelToString(HealthLevel healthLevel)
{
	switch (healthLevel)
	{
	case Healthy: return "Healthy";
	case MildlySick: return "Mildly Sick";
	case ModeratelySick: return "Sick";
	case SuperSick: return "Very Sick";
	case DeathlySick: return "Deathly Sick";
	case DeadSick: return "";
	}

	return "UNKNOWN HEALTH LEVEL";
}

/*
	Returns the emotion level as a string.
*/
string emotionLevelToString(EmotionLevel emotionLevel)
{
	switch (emotionLevel)
	{
	case Excited: return "Excited";
	case Happy: return "Happy";
	case Content: return "Content";
	case Neglected: return "Neglected";
	case Depressed: return "Depressed";
	case DeadEmotion: return "";
	}

	return "UNKNOWN EMOTION LEVEL";
}

/*
	Returns the hunger level as a string.
*/
string hungerLevelToString(HungerLevel hungerLevel)
{
	switch (hungerLevel)
	{
	case Full: return "Full";
	case Hungry: return "Hungry";
	case VeryHungry: return "Very Hungry";
	case Starving: return "Starving";
	case DeadHungry: return "";
	}

	return "UNKNOWN HUNGER LEVEL";
}

/*
	Returns the dealth type as a string.
*/
string deathTypeToString(DeathType deathType)
{
	string name = emojiName[currentEmojiIndex];
	switch (deathType)
	{
	case AgeRelated: return name + " died of old age.";
	case HungerRelated: return name + " died from starvation.";
	case HealthRelated: return name + " died from sickness.";
	case EmotionRelated: return name + " died from neglect.";
	}

	return "UNKNOWN DEATH TYPE";
}