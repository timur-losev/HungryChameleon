#include "Precompiled.h"
#include "Player.h"
#include "SaveController.h"
#include "GameDelegate.h"
#include "EventController.h"

Player::Player()
{
	
}

Player::~Player()
{

}

void Player::dumpSave(bool saveToFile /*= false*/)
{
	SaveController& sc = *GameDelegate::getSaveController();
	sc.SetIntValue(SaveKeys::HighScore, getHighScore());
	sc.SetIntValue(SaveKeys::Cash, getCash());
	if (saveToFile)
	{
		GameDelegate::getSaveController()->save();
	}
}

void Player::readSave()
{
	SaveController& sc = *GameDelegate::getSaveController();
	_setHighScore(sc.GetIntValue(SaveKeys::HighScore));
	setCash(sc.GetIntValue(SaveKeys::Cash));
}

int Player::getScore() const
{
	return m_score;
}

void Player::setScore(int value)
{
	if (value > getHighScore())
	{
		SharedEventController::Instance().playerHighScoreChanged(getHighScore(), value);
		_setHighScore(value);
	}
	m_score = value;
}

int Player::getCash() const
{
	return m_cash;
}

void Player::setCash(int value)
{
	m_cash = value;
}

int Player::getHighScore() const
{
	return m_highScore;
}

void Player::_setHighScore(int value)
{
	m_highScore = value;
}