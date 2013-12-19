#include "Precompiled.h"
#include "Player.h"
#include "SaveController.h"
#include "GameDelegate.h"
#include "EventController.h"
#include "LevelSettingsController.h"

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
	sc.setHighScore(getHighScore());
	sc.setCash(getCash());
	sc.setMapProgress(m_storyProgress);
	sc.setChipPosition(m_tokenMapPosition);
}

void Player::readSave()
{
	SaveController& sc = *GameDelegate::getSaveController();
	_setHighScore(sc.getHighScore());
	setCash(sc.getCash());

	m_tokenMapPosition = sc.getChipPosition();
	m_storyProgress = sc.getMapProgress();
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
	m_storyProgress->setObject(CCString::create("1"), GameDelegate::getLevelSettingsController()->getStartingPoint());
	m_tokenMapPosition = GameDelegate::getLevelSettingsController()->getStartingPoint();
}

void Player::_onGameFinished(int score)
{
	const LevelSettings& setting = GameDelegate::getLevelSettingsController()->getSettingsForPoint(getTokenMapPositionName());
	getStoryProgress()->setObject(CCString::create("1"), setting.nextPosition);
	setTokenMapPositionName(setting.nextPosition);
	dumpSave(true);
}

void Player::_onGameStarted(const std::string& level)
{
	setTokenMapPositionName(level);
}
