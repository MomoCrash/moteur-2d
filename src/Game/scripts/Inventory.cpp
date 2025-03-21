#include "pch.h"
#include "Inventory.h"

void Inventory::OnStart()
{
	items =
	{
		Item{ Material::SWORD, 0, 1, false, {}, {} },
		Item{ Material::ARMOR, 0, 1, false, {}, {} },
		Item{ Material::AXE, 0, 1, false, {}, {} },
		Item{ Material::PICKAXE, 0, 1, false, {}, {} },
		Item{ Material::PENDANTIF, 0, 1, false, {}, {} },
		Item{ Material::ROLLER, 0, 1, false, {}, {} },
		Item{ Material::HEALTH_POTION, 0, 5,false, {}, {} },
		Item{ Material::WOOD1, 0, 20, false, {}, {} },
		Item{ Material::WOOD2, 0, 20, false, {}, {} },
		Item{ Material::WOOD3, 0, 20, false, {}, {} },
		Item{ Material::STONE1, 0, 20, false, {}, {} },
		Item{ Material::STONE2, 0, 20, false, {}, {} },
		Item{ Material::STONE3, 0, 20, false, {}, {} },
	};
	DisplayInventory();
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
			CONSOLE_OUTPUT(L"----------------------" << std::endl);
		}
	}
	CONSOLE_OUTPUT(L"===== INVENTORY END =====" << std::endl);
}
