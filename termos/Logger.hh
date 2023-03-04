#ifndef TERMOS_LOGGER_HH
#define TERMOS_LOGGER_HH

#include "Widget.hh"

#include <sstream>
#include <vector>
#include <string>

namespace Termos {
class Logger : public Widget
{
public:
	Logger() {}
	void onRender(Render& render) override;

	template <typename T>
	void add(const T& first)
	{
		ss << first;
		logs.emplace_back(ss.str());

		ss.str("");
		render();
	}

	template <typename T, typename... Args>
	void add(const T& first, Args&& ...args)
	{
		ss << first << ' ';
		add(args...);
	}

private:
	std::stringstream ss;
	std::vector <std::string> logs;
};
}

#endif
