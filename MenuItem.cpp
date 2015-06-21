#include "MenuItem.hpp"

namespace Cong
{

	const std::string MenuItem::DEFAULT_SEPARATOR = ": ";
	const std::string MenuItem::DEFAULT_OPTION_PREFIX = "< ";
	const std::string MenuItem::DEFAULT_OPTION_SUFFIX = " >";

	MenuItem::MenuItem(const CharMap &charMap)
	: SpriteText(charMap), selectedOption(-1), separator(DEFAULT_SEPARATOR),
	  optionPrefix(DEFAULT_OPTION_PREFIX), optionSuffix(DEFAULT_OPTION_SUFFIX)
	{
		// Do nothing
	}

	int MenuItem::addOption(const std::string &option)
	{
		// Add new option to the options
		options.push_back(option);

		// Determine index of the new option
		int optionIndex = options.size() - 1;

		// If this was is the first and only option, select and display it
		if (optionIndex == 0)
		{
			selectedOption = optionIndex;
			updateText();
		}

		// Return index of new option so caller can reference it later
		return optionIndex;
	}

	std::string MenuItem::getOption(int i) const
	{
		if (i < 0 || i >= options.size())
		{
			return ""; // Indicates that there is no option at index i
		}

		return options.at(i);
	}

	std::string MenuItem::getSelectedOption() const
	{
		if (selectedOption == -1)
		{
			return ""; // Indicates that there is no option yet
		}

		return options.at(selectedOption);
	}

	int MenuItem::getSelectedOptionIndex() const
	{
		return selectedOption;
	}

	int MenuItem::getOptionIndex(const std::string &label) const
	{
		for (int i=0; i<options.size(); ++i)
		{
			if (options.at(i) == label)
			{
				return i;
			}
		}

		// Not found
		return -1;
	}

	bool MenuItem::hasOptions() const
	{
		return options.size() > 0;
	}

	void MenuItem::nextOption()
	{
		int numOptions = options.size();

		// If there are no options, we can't select the next one
		if (numOptions == 0)
		{
			return;
		}

		// If we're already at the end, jump to the first option
		if (++selectedOption >= options.size())
		{
			selectedOption = 0;
		}

		updateText();
	}

	void MenuItem::prevOption()
	{
		int numOptions = options.size();

		// If there are no options, we can't select the previous one
		if (numOptions == 0)
		{
			return;
		}

		// If we're already at the beginning, jump to the last option
		if (--selectedOption < 0)
		{
			selectedOption = numOptions - 1;
		}

		updateText();
	}

	void MenuItem::showOption(int i)
	{
		if (i >= 0 && i < options.size())
		{
			selectedOption = i;
			updateText();
		}
	}

	void MenuItem::showOption(const std::string &label)
	{
		int optionIndex = getOptionIndex(label);
	
		if (optionIndex != -1)
		{
			showOption(optionIndex);
		}
	}

	void MenuItem::updateText()
	{
		if (selectedOption == -1)
		{
			setText(label);
		}
		else
		{
			setTextWithOption(label, options.at(selectedOption));
		}
	}

	void MenuItem::setTextWithOption(const std::string &label, const std::string &option)
	{
		this->label = label; // Can't use setLabel() as it will call updateText(), which calls this function!
		setText(label + separator + optionPrefix + option + optionSuffix);		
	}

	void MenuItem::setLabel(const std::string &label)
	{
		this->label = label;
		updateText();
	}

	std::string MenuItem::getLabel() const
	{
		return label;
	}

	void MenuItem::setSeparator(const std::string &separator)
	{
		this->separator = separator;
		updateText();
	}

	void MenuItem::setOptioPrefix(const std::string &prefix)
	{
		optionPrefix = prefix;
		updateText();
	}

	void MenuItem::setOptionSuffix(const std::string &suffix)
	{
		optionSuffix = suffix;
		updateText();
	}

	std::string MenuItem::getSeparator() const
	{
		return separator;
	}

	std::string MenuItem::getOptioPrefix() const
	{
		return optionPrefix;
	}

	std::string MenuItem::getOptionSuffix() const
	{
		return optionSuffix;
	}

}
