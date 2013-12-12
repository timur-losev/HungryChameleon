#pragma once

class Player : public has_slots<>
{
public:
	Player();
	~Player();

	int					getScore() const;
	void				setScore(int);
	int					getCash() const;
	void				setCash(int);
	int					getHighScore() const;

	void				dumpSave(bool saveToFile = false);
	void				readSave();

	CCDictionary*		getStoryProgress(); // accessor/mutator
	const std::string&	getTokenMapPositionName();
	void				setTokenMapPositionName(const std::string&);

private:
	void				_setHighScore(int);
	void				_initStoryProgress();
	void				_onGameFinished(int score);
	void				_onGameStarted(const std::string& level);

private:
	int					m_highScore = 0;
	int					m_score = 0;
	int					m_cash = 0;
	CCDictionary*		m_storyProgress = nullptr;
	std::string			m_tokenMapPosition;
};
