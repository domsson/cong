#ifndef CONG_MENUITEM_HPP
#define CONG_MENUITEM_HPP

#include <vector>
#include "SpriteText.hpp"

namespace Cong
{

class MenuItem: public SpriteText
{

public:

	static const std::string DEFAULT_SEPARATOR;
	static const std::string DEFAULT_OPTION_PREFIX;
	static const std::string DEFAULT_OPTION_SUFFIX;

	MenuItem(const CharMap &charMap);

	int addOption(const std::string &option);
	std::string getOption(int i) const;
	std::string getSelectedOption() const;
	int getSelectedOptionIndex() const;
	int getOptionIndex(const std::string &label) const;
	
	void setLabel(const std::string &label);
	void setSeparator(const std::string &separator);
	void setOptioPrefix(const std::string &prefix);
	void setOptionSuffix(const std::string &suffix);

	std::string getLabel() const;
	std::string getSeparator() const;
	std::string getOptioPrefix() const;
	std::string getOptionSuffix() const;

	bool hasOptions() const;

	void nextOption();
	void prevOption();
	void showOption(int i);
	void showOption(const std::string &label);

protected:

	void setTextWithOption(const std::string &label, const std::string &option);
	void updateText();

private:

	std::string label;

	std::vector<std::string> options;
	int selectedOption;

	std::string separator;
	std::string optionPrefix;
	std::string optionSuffix;

};

}

#endif
