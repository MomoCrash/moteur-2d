#include "pch.h"
#include "Inventory.h"

void Inventory::OnStart()
{
	items =
	{
		Item{ ItemList::SWORD, 0, 1, false, EBonus::EFFICIENCY, EMalus::FASTSPEED },
		Item{ ItemList::ARMOR, 0, 1, false, EBonus::SLOWSPEED, EMalus::SMALLERCIRCLE},
		Item{ ItemList::AXE, 0, 1, false, EBonus::EFFICIENCY, EMalus::DECREASEHP },
		Item{ ItemList::PICKAXE, 0, 1, false, EBonus::EFFICIENCY, EMalus::FASTSPEED },
		Item{ ItemList::PENDANTIF, 0, 1, false, EBonus::INCREASEHP, EMalus::SMALLERCIRCLE},
		Item{ ItemList::ROLLER, 0, 1, false, EBonus::NONE_BONUS, EMalus::FASTSPEED },

		Item{ ItemList::HEALTH_POTION, 0, 5, false, EBonus::NONE_BONUS, EMalus::NONE_MALUS },

		Item{ ItemList::WOOD1, 0, 20, false, EBonus::NONE_BONUS, EMalus::NONE_MALUS },
		Item{ ItemList::WOOD2, 0, 20, false, EBonus::NONE_BONUS, EMalus::NONE_MALUS },
		Item{ ItemList::WOOD3, 0, 20, false, EBonus::NONE_BONUS, EMalus::NONE_MALUS },
		Item{ ItemList::STONE1, 0, 20, false, EBonus::NONE_BONUS, EMalus::NONE_MALUS },
		Item{ ItemList::STONE2, 0, 20, false, EBonus::NONE_BONUS, EMalus::NONE_MALUS },
		Item{ ItemList::STONE3, 0, 20, false, EBonus::NONE_BONUS, EMalus::NONE_MALUS },
	};
}

void Inventory::OnUpdate()
{

}

void Inventory::AddItemCount(int id, unsigned int amount)
{
	if (id < 0 || id >= items.size())
	{
		CONSOLE_OUTPUT(L"The id: " << id << L" is not in the range of the inventory" << std::endl);
		return;
	}

	Item& item = items[id];
	if (item.actualCount + amount <= item.maxCount)
	{
		item.actualCount += amount;
	}
	else
	{
		item.actualCount = item.maxCount;
	}

	UpdateItemState(id);
	CONSOLE_OUTPUT(L"The item: " << item.id << L" increased, new quantity = " << item.actualCount << std::endl);
}

void Inventory::RemoveItemCount(int id, unsigned int amount)
{
	if (id < 0 || id >= items.size())
	{
		CONSOLE_OUTPUT(L"The id: " << id << L" is not in the range of the inventory" << std::endl);
		return;
	}

	Item& item = items[id];
	if (item.actualCount >= amount)
	{
		item.actualCount -= amount;
	}
	else
	{
		item.actualCount = 0;
	}

	UpdateItemState(id);
	CONSOLE_OUTPUT(L"The item: " << item.id << L" decreased, new quantity = " << item.actualCount << std::endl);
}

void Inventory::UpdateItemState(int id)
{
	if (id < 0 || id >= items.size()) 
	{
		return;
	}

	items[id].isActive = (items[id].actualCount > 0);
}

unsigned int Inventory::GetItemCount(int id)
{
	if (id < 0 || id >= items.size())
	{
		CONSOLE_OUTPUT(L"The id: " << id << L" is not in the range of the inventory" << std::endl);
		return 0;
	}

	return items[id].actualCount;
}

void Inventory::DisplayInventory()
{
	CONSOLE_OUTPUT(L"===== INVENTORY START =====" << std::endl);

	for (const Item& item : items)
	{
		if (item.actualCount > 0)
		{
			CONSOLE_OUTPUT(L"Item ID: " << item.id << std::endl);
			CONSOLE_OUTPUT(L"Actual Count: " << item.actualCount << std::endl);
			CONSOLE_OUTPUT(L"Max Count: " << item.maxCount << std::endl);
			CONSOLE_OUTPUT(L"Is Active: " << (item.isActive ? L"Yes" : L"No") << std::endl);
			CONSOLE_OUTPUT(L"Bonus: " << item.bonus << std::endl);
			CONSOLE_OUTPUT(L"Malus: " << item.malus << std::endl);
			CONSOLE_OUTPUT(L"----------------------" << std::endl);
		}
	}
	CONSOLE_OUTPUT(L"===== INVENTORY END =====" << std::endl);
}
