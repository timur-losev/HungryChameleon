#include "Precompiled.h"
#include "Player.h"
#include "SaveController.h"
#include "GameDelegate.h"
#include "EventController.h"

Player::Player()
{
	SharedEventController::Instance().gameFinishedWithScore.connect(this, &Player::_onGameFinished);
	SharedEventController::Instance().gameStartedWithLevel.connect(this, &Player::_onGameStarted);
}

Player::~Player()
{
	if (m_storyProgress)
		m_storyProgress->release();
}

void Player::dumpSave(bool saveToFile /*= false*/)
{
	SaveController& sc = *GameDelegate::getSaveController();
	sc.setIntValue(SaveKeys::HighScore, getHighScore());
	sc.setIntValue(SaveKeys::Cash, getCash());
	sc.setDictValue(SaveKeys::MapProgress, m_storyProgress);
	sc.setStringValue(SaveKeys::TokenPosition, m_tokenMapPosition);
	if (saveToFile)
	{
		GameDelegate::getSaveController()->save();
	}
}

void Player::readSave()
{
	SaveController& sc = *GameDelegate::getSaveController();
	_setHighScore(sc.getIntValue(SaveKeys::HighScore));
	setCash(sc.getIntValue(SaveKeys::Cash));

	m_tokenMapPosition = sc.getStringValue(SaveKeys::TokenPosition);
	m_storyProgress = sc.getDictValue(SaveKeys::MapProgress);
	m_storyProgress->retain();
	if (m_storyProgress->count() == 0 || m_tokenMapPosition.empty())
	{
		_initStoryProgress();
	}
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

CCDictionary* Player::getStoryProgress()
{
	return m_storyProgress;
}

const std::string& Player::getTokenMapPositionName()
{
	return m_tokenMapPosition;
}

void Player::setTokenMapPositionName(const std::string& value)
{
	m_tokenMapPosition = std::string(value);
}

void Player::_initStoryProgress()
{
	m_storyProgress->setObject(CCString::create("1"), "pos_1");
	m_tokenMapPosition = std::string("pos_1");
}

void Player::_onGameFinished(int score)
{
	std::stringstream ss;
	std::string base("pos_");
	ss << base;
	ss << 1 + atoi(getTokenMapPositionName().substr(base.length()).c_str());
	getStoryProgress()->setObject(CCString::create("1"), ss.str());
	setTokenMapPositionName(ss.str());
	dumpSave(true);
}

void Player::_onGameStarted(const std::string& level)
{
	setTokenMapPositionName(level);
}
