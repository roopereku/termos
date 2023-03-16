#include <termos/TabSelector.hh>
#include <termos/Debug.hh>

namespace Termos {

TabSelector::TabSelector()
{
	limitMaximumSize(1);
}

void TabSelector::add(const std::string& name)
{
	tabs.emplace_back(name);
	render();
}

void TabSelector::onMouseClick(Point at)
{
	if(tabs.empty())
		return;

	size_t oldSelected = selected;

	unsigned partWidth = (getSize().x - 1) / tabs.size(); 
	selected = at.x / partWidth; 

	if(selected == oldSelected)
		return;

	render();

	if(onSelectTab)
		onSelectTab(selected);
}

void TabSelector::onRender(Render& render)
{
	if(tabs.empty())
		return;

	unsigned partWidth = (getSize().x - 1) / tabs.size(); 

	size_t offset = 0;
	for(size_t i = 0; i < tabs.size(); i++)
	{
		size_t middle = offset + partWidth / 2 - tabs[i].size() / 2;
		render.text(tabs[i], middle, 0, partWidth);

		if(i + 1 < tabs.size())
		{
			offset += partWidth + 1;
			render.verticalLine(offset - 1, 0, 1);
		}
	}
}

}
