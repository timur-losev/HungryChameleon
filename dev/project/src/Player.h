#pragma once

class Player : public has_slots<>
{
public:
	Player();
	~Player();

	int			getScore() const;
	void		setScore(int);
	int			getCash() const;
	void		setCash(int);
	int			getHighScore() const;

	void		dumpSave(bool saveToFile = false);
	void		readSave();

private:
	void		_setHighScore(int);

private:
	int		m_highScore = 0;
	int		m_score = 0;
	int		m_cash = 0;
};
