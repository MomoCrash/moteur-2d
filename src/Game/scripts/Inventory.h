#ifndef INVENTORY_INCLUDE
#define INVENTORY_INCLUDE


#include "scripts/Script.h"

#include <array>

enum EBonus
{
	NONE_BONUS,
	SLOWSPEED,
	BIGGERCIRCLE,
	EFFICIENCY,
	INCREASEHP,

	COUNT_BONUS

};

enum EMalus
{
	NONE_MALUS,
	FASTSPEED,
	SMALLERCIRCLE,
	INEFFICIENCY,
	DECREASEHP,

	COUNT_MALUS
};

enum ItemList
{
	SWORD,
	ARMOR,
	AXE,
	PICKAXE,
	PENDANTIF,
	ROLLER,
	HEALTH_POTION,
	WOOD1,
	WOOD2,
	WOOD3,
	STONE1,
	STONE2,
	STONE3,

	COUNT_ITEM
};

struct Item 
{
	unsigned int id;
	unsigned int actualCount = 0;
	unsigned int maxCount = 0;
	bool isActive = false;
	EBonus bonus = NONE_BONUS;
	EMalus malus = NONE_MALUS;
};

class Inventory : public IScript
{
public:
	Inventory() = default;
	~Inventory() = default;

	void OnStart() override;
	void OnUpdate() override;

	void AddItemCount(int id, unsigned int amount);
	void RemoveItemCount(int id, unsigned int amount);

	unsigned int GetItemCount(int id);

	void DisplayInventory();

private:
	void UpdateItemState(int id);

private:
	std::array<Item, COUNT_ITEM> items;
};


#endif // !INVENTORY_INCLUDE