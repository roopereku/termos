#ifndef TERMOS_TABLE_HH
#define TERMOS_TABLE_HH

#include "Widget.hh"
#include "EditableString.hh"

#include <string>
#include <vector>

namespace Termos {

class Table;
class TableRow
{
public:
	TableRow(TableRow&& rhs) = default;

	const std::string& operator[](size_t index);
	void set(size_t index, const std::string& value);
	size_t columns();

	friend class Table;

private:
	TableRow(Table* table, size_t columns);
	void setCell(size_t index, const std::string& value);

	Table* table;
	std::vector <EditableString> cells;
};

class Table : public Widget
{
public:
	Table(size_t columns);

	void onRender(Render& render) override;
	void onMouseClick(Point at) override;
	void onKeyPress(int key) override;
	void onResize() override;

	TableRow& addRow();
	void set(TableRow& row, size_t index, const std::string& value);

private:
	size_t columns;
	Point selected;

	//std::vector <size_t> columnLongestValues;
	std::vector <TableRow> rows;
};
}

#endif
