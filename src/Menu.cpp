#include "Menu.hpp"
#include "CharMap.hpp"

namespace Cong
{

	const int Menu::DEFAULT_ITEM_SCALE = 4;
	const int Menu::DEFAULT_ITEM_MARGIN = 32;

	const sf::Color Menu::DEFAULT_ITEM_COLOR = sf::Color::White;
	const sf::Color Menu::DEFAULT_SELECT_COLOR = sf::Color(200, 170, 60);
	const sf::Color Menu::DEFAULT_INACTIVE_COLOR = sf::Color(175, 175, 175);

	Menu::Menu()
	: charMap(nullptr), currentItem(-1), anchor(Anchor::TOP_CENTER)
	{
		setValuesToDefaults();
	}

	Menu::Menu(const CharMap &charMap)
	: charMap(&charMap), currentItem(-1), anchor(Anchor::TOP_CENTER)
	{
		setValuesToDefaults();
	}

	void Menu::setCharMap(const CharMap &charMap)
	{
		this->charMap = &charMap;
		positionItems();
	}

	void Menu::setValuesToDefaults()
	{
		itemScale = DEFAULT_ITEM_SCALE;
		itemMargin = DEFAULT_ITEM_MARGIN;

		itemColor = DEFAULT_ITEM_COLOR;
		selectColor = DEFAULT_SELECT_COLOR;
		inactiveColor = DEFAULT_INACTIVE_COLOR;
	}

	int Menu::addItem(const std::string &label, int itemScale)
	{
		if (charMap == nullptr)
		{
			std::cerr << "Warning: tried to add menu item when no CharMap is set." << std::endl;
			return -1;
		}

		// Create and tweak the new menu item
		MenuItem newItem(*charMap);
		newItem.setScale(sf::Vector2f(itemScale, itemScale));
		newItem.setAnchor(Anchor::TOP_CENTER);
		newItem.setLabel(label);

		addItem(newItem);
	}

	int Menu::addItem(const std::string &label, const std::string options[], int numOptions)
	{
		if (charMap == nullptr)
		{
			std::cerr << "Warning: tried to add menu item when no CharMap is set." << std::endl;
			return -1;
		}

		// Create and tweak the new menu item
		MenuItem newItem(*charMap);
		newItem.setScale(sf::Vector2f(itemScale, itemScale));
		newItem.setAnchor(Anchor::TOP_CENTER);
		newItem.setLabel(label);

		for (int i=0; i<numOptions; ++i)
		{
			newItem.addOption(options[i]);
		}

		addItem(newItem);
	}

	int Menu::addItem(const MenuItem &item)
	{
		// Insert the new item into the collection
		items.push_back(item);

		// Calculate the index of the new item within the collection
		int itemNum = items.size() - 1;

		// It this is the first item, 'select' (highlight/hover) it
		if (itemNum == 0)
		{
			setCurrentItem(itemNum);
		}

		// Update the origin (the new item might be wider than all others)
		updateOrigin();

		// Reposition all items based on the (maybe) updated origin
		positionItems();

		// Return the index of the new item so the caller can refer to it later
		return itemNum;
	}

	void Menu::setAnchor(Anchor anchor)
	{
		this->anchor = anchor;
		updateOrigin();
	}

	void Menu::updateOrigin()
	{
		switch (anchor)
		{
			case Anchor::TOP_LEFT:
				setOrigin(0.0, 0.0);
				break;
			case Anchor::TOP_CENTER:
				setOrigin(getWidth() * 0.5, 0.0);
				break;
			case Anchor::TOP_RIGHT:
				setOrigin(getWidth(), 0.0);
				break;
			case Anchor::CENTER_LEFT:
				setOrigin(0.0, getHeight() * 0.5);
				break;
			case Anchor::CENTER_CENTER:
				setOrigin(getWidth() * 0.5, getHeight() * 0.5);
				break;
			case Anchor::CENTER_RIGHT:
				setOrigin(getWidth(), getHeight() * 0.5);
				break;
			case Anchor::BOTTOM_LEFT:
				setOrigin(0.0, getHeight());
				break;
			case Anchor::BOTTOM_CENTER:
				setOrigin(getWidth() * 0.5, getHeight());
				break;
			case Anchor::BOTTOM_RIGHT:
				setOrigin(getWidth(), getHeight());
				break;			
		}
	}

	MenuItem& Menu::getItem(int i)
	{
		// TODO: Crashes if i is out of bounds, but can't return nullptr. What to do?
		return items.at(i);
	}

	int Menu::getCurrentItem() const
	{
		return currentItem;
	}

	void Menu::positionItems()
	{
		for (int i=0; i<items.size(); ++i)
		{
			positionItem(i);
		}
	}

	void Menu::positionItem(int i)
	{
		float x = getOrigin().x;
		float y = 0;

		y = (i == 0) ? 0 : items.at(i-1).getPosition().y + items.at(i-1).getHeight() + itemMargin;
		items.at(i).setPosition(x, y);
	}

	int Menu::findWidestItem() const
	{
		int indexOfWidest = -1;
		int widthOfWidest = 0;
		int currentWidth = 0;

		for (int i=0; i<items.size(); ++i)
		{
			// Using getUnscaledWidth() to save the additional multiplication in getWidth()
			currentWidth = items.at(i).getUnscaledWidth();
			if (currentWidth > widthOfWidest)
			{
				indexOfWidest = i;
				widthOfWidest = currentWidth;
			}
		}
		return indexOfWidest;
	}

	float Menu::getWidth() const
	{
		int indexOfWidest = findWidestItem();
		if (indexOfWidest == -1)
		{
			return 0;
		}
		return items.at(indexOfWidest).getWidth();
	}

	float Menu::getHeight() const
	{
		int numItems = items.size();
		if (numItems == 0)
		{
			return 0;
		}
		return (numItems * items.at(0).getHeight()) + ((numItems - 1) * itemMargin);
	}

	void Menu::scaleItems()
	{
		for (int i=0; i<items.size(); ++i)
		{
			items.at(i).setScale(itemScale, itemScale);
		}
	}

	void Menu::styleItems()
	{
		for (int i=0; i<items.size(); ++i)
		{
			items.at(i).setColor(itemColor);
		}
	}

	void Menu::setItemScale(int scale)
	{
		itemScale = scale;
		scaleItems();
		positionItems();
	}

	void Menu::setItemMargin(int margin)
	{
		itemMargin = margin;
		positionItems();
	}

	void Menu::setItemColor(const sf::Color &color)
	{
		itemColor = color;
	}

	void Menu::setSelectColor(const sf::Color &color)
	{
		selectColor = color;
	}

	void Menu::setInactiveColor(const sf::Color &color)
	{
		inactiveColor = color;
	}

	/**
	 * Modifies the appearance of the given menu item in order to indicate
	 * that it is the currently selected item. Override in child classes to
	 * define a custom 'selected' style for menu items.
	 */
	void Menu::selectItem(int i)
	{
		items.at(i).setColor(selectColor);
	}

	/**
	 * Modifies the appearance of the given menu item in order to indicate
	 * that it is not currently selected. Override in child classes to define
	 * a custom 'unselected' style for the menu items.
	 */
	void Menu::deselectItem(int i)
	{
		items.at(i).setColor(itemColor);
	}

	/**
	 * Deselects the currently selected menu item and selects the given item.
	 */
	void Menu::setCurrentItem(int i)
	{
		// Do nothing if item <i> is already the currently selected item
		if (i == currentItem)
		{
			std::cerr << "Warning: tried to select the currently selected menu item." << std::endl;
			return;
		}

		// Do nothing it <i> refers to a non-existing menu item
		if (!itemExists(i))
		{
			std::cerr << "Warning: tried to select the non-existing menu item #" << i << "." << std::endl;
			return;
		}

		// Do nothing if the item to be selected is disabled
		if (!items.at(i).isEnabled())
		{
			std::cerr << "Warning: tried to select a deactivated menu item." << std::endl;
			return;
		}

		// Deselect the currently selected item, if any
		if (currentItem != -1)
		{
			deselectItem(currentItem);
			currentItem = -1;
		}

		selectItem(i);
		currentItem = i;
	}


	void Menu::enableItem(int i)
	{
		if (itemExists(i))
		{
			items.at(i).setEnabled(true);
			items.at(i).setColor(itemColor);
		}
	}

	void Menu::disableItem(int i)
	{
		// If we're trying to disable the currently selected item, select the next available item
		if (i == currentItem)
		{
			// Let's find the next available menu item, if any
			int j = findNextItem();

			// If no other is available, then we can't disable the current one, that would be weird
			if (j == -1)
			{
				std::cerr << "Warning: tried to disable the only available menu item." << std::endl;
				return;
			}

			setCurrentItem(j);
		}

		items.at(i).setEnabled(false);
		items.at(i).setColor(inactiveColor);
	}

	bool Menu::itemExists(int i) const
	{
		return (i >= 0 && i < items.size());
	}
	
	void Menu::selectNextItem()
	{
		int i = findNextItem();
		if (i == -1) // There is no next item available
		{
			std::cerr << "Warning: tried to select next menu item when there is none available." << std::endl;
			return;
		}

		setCurrentItem(i);	
	}
	
	int Menu::findNextItem(int current, int checked) const
	{
		if (current == -1)
		{
			current = currentItem;
		}

		// Did we already make a full circle without success?
		if (checked >= items.size() - 1)
		{
			return -1;
		}

		int next = (current + 1 >= items.size()) ? 0 : current + 1; // Roll over if need be

		if (items.at(next).isEnabled())
		{
			return next;
		}

		return findNextItem(next, ++checked);
	}

	void Menu::selectPrevItem()
	{
		int i = findPrevItem();
		if (i == -1) // There is no previous item available
		{
			std::cerr << "Warning: tried to select previous menu item when there is none available." << std::endl;
			return;
		}

		setCurrentItem(i);
	}

	int Menu::findPrevItem(int current, int checked) const
	{
		if (current == -1)
		{
			current = currentItem;
		}

		// Did we already make a full circle without success?
		if (checked >= items.size() - 1)
		{
			return -1;
		}

		int prev = (current - 1 < 0) ? items.size() - 1 : current - 1; // Roll over if need be

		if (items.at(prev).isEnabled())
		{
			return prev;
		}

		return findPrevItem(prev, ++checked);
	}

	void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		for (int i=0; i<items.size(); ++i)
		{		
			target.draw(items.at(i), states);
		}
	}

}
