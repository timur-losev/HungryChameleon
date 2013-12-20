@echo off
rem while running monitors any changes in leaderboard directory and sinchonizes them
python ftp_sync.py -l leaderboard -m
pause