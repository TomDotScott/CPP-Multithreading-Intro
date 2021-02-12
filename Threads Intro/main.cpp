#include <iostream>
#include <thread>
#include <vector>

int rand_range(const int min, const int max)
{
	return min + (rand() % (max - min + 1));
}

class Actor
{
public:
	Actor(const int hp, const int attackPoints, const int defensePoints, const int accuracy, std::string name) :
		m_hp(hp),
		m_attack(attackPoints),
		m_defense(defensePoints),
		m_accuracy(accuracy),
		m_name(std::move(name)),
		m_opponent(nullptr)
	{
	}

	virtual ~Actor() = default;

	void Attack() const
	{
		if (m_opponent)
		{
			int randChance = rand_range(0, 100);
			std::cout << randChance << std::endl;
			if (randChance <= m_accuracy)
			{
				std::cout << m_name << " attacks " << m_opponent->m_name << std::endl;
				m_opponent->m_hp -= (m_attack - m_opponent->m_defense);
				std::cout << m_opponent->m_name << " HP: " << m_opponent->GetHP() << std::endl;
			} else
			{
				std::cout << m_name << " missed" << std::endl;
			}
		}
	}

	virtual void Run() = 0;

	int GetHP() const { return m_hp; }

	void SetOpponent(Actor* other)
	{
		m_opponent = other;
	}

private:
	int m_hp;
	int m_attack;
	int m_defense;
	int m_accuracy;
	const std::string m_name;
	Actor* m_opponent;

};


class RolforTheBarbarian : public Actor
{
public:
	RolforTheBarbarian(const int hp, const int attack, const int defense) : Actor(hp, attack, defense, 55, "Rolfor") {}

	void Run() override
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
		Attack();
	}
};

class GuardDanTheGnome : public Actor
{
public:
	GuardDanTheGnome(const int hp, const int attack, const int defense) : Actor(hp, attack, defense, 85, "Dan") {}

	void Run() override
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));
		Attack();
	}
};

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));

	GuardDanTheGnome dan(150, 35, 55);
	RolforTheBarbarian rolf(100, 50, 30);

	dan.SetOpponent(&rolf);
	rolf.SetOpponent(&dan);

	while (dan.GetHP() > 0 && rolf.GetHP() > 0)
	{
		std::thread gd(&GuardDanTheGnome::Run, &dan);
		//std::thread rf(&RolforTheBarbarian::Run, &rolf);

		//rf.join();
		gd.join();
	}

	std::cout << (dan.GetHP() > 0 ? "Dan wins" : "Rolfor wins") << std::endl;

	return 0;
}