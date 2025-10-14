#include "Player.h"

int Player::p_num = 1;

void Player::set_figure(char c)
{
	if (c != 'x' && c != 'o')
		throw ExceptionErrorFigureType("[Error msg] \'x\' or \'o\'... please repeat", c);

	this->player_figure = c;
};

char Player::get_figure() const { return this->player_figure; }
const std::string& Player::get_name() const { return this->name; }
en_Player_Type Player::get_player_type() const { return this->player_type; }
bool Player::get_win_flag() const { return this->win_flag; }
void Player::set_win_flag(bool flag) { this->win_flag = flag; }
int Player::get_score() const { return this->score; }
void Player::inc_score() { this->score += 1; }