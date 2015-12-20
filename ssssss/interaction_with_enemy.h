#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "iostream"
#include <vector>
#include <list>
#include "level.hpp"
#include "anim.hpp"
#include "classes.h"
#include "var.h"
#include "init_anim_and_obj.h"

using namespace sf;

void interaction_with_enemy_clon(PLAYER &Player, AnimationManager &anim2, std::list<Entity*> &entities, std::list<Entity*>::iterator &it, Level &lvl, float &time, float &shootTime_clon)
{
	float distance;

	Entity *enemy = *it;

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (!(Player.getRect().intersects(enemy->getRect())))
		{
			if (Player.getRectAttLeft().intersects(enemy->getRect()) || Player.getRectAttRight().intersects(enemy->getRect()))
			{
				enemy->dx = 0;
				enemy->Health = 0;
			}
		}
		else
		{
			enemy->dx = 0;
			enemy->Health = 0;
		}
	}

	for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
	{
		Entity *bullet = *it2;
		if (bullet->Name == "Bullet")
			if (bullet->life == true)
			{
				if (bullet->getRect().intersects(Player.getRect()))
				{
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						bullet->dx *= -1;
						bullet->repulse = true;
					}
					else
					{
						bullet->life = false;
						Player.Health -= 5;
						Player.hit = true;
					}
				}
				if ((bullet->getRect().intersects((*it)->getRect())) && (bullet->repulse == true))
				{
					bullet->repulse = false;
					bullet->life = false;
					enemy->Health -= 5;
				}
			}
	}

	distance = sqrt((Player.x - (*it)->x)*(Player.x - (*it)->x));

	if ((distance < 100) && ((enemy->y + 50 >= Player.y) && (enemy->y - 65 <= Player.y))) { shootTime_clon += 0.005*time; }

	if ((distance < 100) && ((enemy->y + 50 >= Player.y) && (enemy->y - 65 <= Player.y)))
	{
		if (shootTime_clon > 7)
		{
			(*it)->pos = 1;

			if (Player.x < (*it)->x) {
				(*it)->dir = 0; entities.push_back(new Bullet(anim2, lvl, (*it)->x, (*it)->y + 18, 1));
			}
			else {
				(*it)->dir = 1; entities.push_back(new Bullet(anim2, lvl, (*it)->x, (*it)->y + 18, 0));
			}
			shootTime_clon = 0.0;
			(*it)->dx = 0;
		}
	}
	else
		if ((*it)->pos == 1)
		{
			(*it)->dx = 0.02;
			(*it)->dir = 1;
			(*it)->pos = 0;
			(*it)->timer = 0;
		}
}

void interaction_with_enemy_droid(PLAYER &Player, AnimationManager &anim2, std::list<Entity*> &entities, std::list<Entity*>::iterator &it, Level &lvl, float &time, float &shootTime_droid)
{
	float distance;

	Entity *enemy = *it;

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (!(Player.getRect().intersects(enemy->getRect())))
		{
			if (Player.getRectAttLeft().intersects(enemy->getRect()) || Player.getRectAttRight().intersects(enemy->getRect()))
			{
				enemy->dx = 0;
				enemy->Health -= 15;
			}
		}
		else
		{
			Player.Health -= 5;
			Player.hit = true;
			enemy->dx = 0;
			enemy->Health -= 15;
		}
	}
	else
		if (Player.getRect().intersects(enemy->getRect()) && (!Player.hit))
		{
			Player.Health -= 5;
			Player.hit = true;
		}

	for (std::list<Entity*>::iterator it3 = entities.begin(); it3 != entities.end(); it3++)
	{
		Entity *bullet = *it3;
		if (bullet->Name == "Bullet")
			if (bullet->life == true)
			{
				if (bullet->getRect().intersects(Player.getRect()))
				{
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						bullet->repulse = true;
					}
					else
					{
						bullet->life = false;
						Player.Health -= 5;
						Player.hit = true;
					}
				}
				if ((bullet->getRect().intersects((*it)->getRect())) && (bullet->repulse == true))
				{
					bullet->repulse = false;
					bullet->life = false;
				}
			}
	}

	distance = sqrt((Player.x - (*it)->x)*(Player.x - (*it)->x));

	if ((distance < 100) && ((enemy->y >= Player.y) && (enemy->y - 80 <= Player.y))) { shootTime_droid += 0.005*time; }

	if ((distance < 100) && ((enemy->y >= Player.y) && (enemy->y - 80 <= Player.y)))
	{

		if (shootTime_droid > 4)
		{

			(*it)->pos = 1;

			if (Player.x < (*it)->x) {
				(*it)->dir = 1; entities.push_back(new Bullet(anim2, lvl, (*it)->x, (*it)->y + 18, 1));
			}
			else {
				(*it)->dir = 0; entities.push_back(new Bullet(anim2, lvl, (*it)->x, (*it)->y + 18, 0));
			}
			shootTime_droid = 0.0;
			(*it)->dx = 0;
		}

	}
	else
		if ((*it)->pos == 1)
		{
			(*it)->dx = 0.04;
			(*it)->pos = 0;
			(*it)->timer = 0;
		}
}