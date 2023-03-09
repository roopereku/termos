#include "Table.hh"
#include "Debug.hh"

#include <algorithm>
#include <cmath>

namespace Termos {

Table::Table(size_t columns) : columns(columns)//, columnLongestValues(columns, 0)
{
	DBG_LOG("columns", columns);
}

TableRow& Table::addRow()
{
	DBG_LOG("Add row");
	rows.push_back(TableRow(this, columns));

	render();
	return rows.back();
}

TableRow::TableRow(Table* table, size_t columns) : table(table), cells(columns)
{
}

void Table::onRender(Render& render)
{
	unsigned lineY = 0;
	unsigned cellWidth = getSize().x / columns - 1;

	// Render each row
	for(size_t y = 0; y < rows.size(); y++)
	{
		// Render a row separator
		render.horizontalLine(0, lineY, getSize().x - 2);
		unsigned lineX = 0;

		// Draw each cell
		for(size_t x = 0; x < rows[y].cells.size(); x++)
		{
			// The vertical separator doesn't look good before the first cell
			if(x > 0) render.verticalLine(lineX, lineY, 2);

			// Render the text of each cell
			bool showCursor = x == selected.x && y == selected.y;
			rows[y].cells[x].onRender(render, lineX + 1, lineY + 1, showCursor);

			lineX += cellWidth + 1;
		}

		lineY += 2;
	}

	render.horizontalLine(0, lineY, getSize().x - 2);
}

void Table::onKeyPress(int key)
{
	if(selected.y >= rows.size())
		return;

	rows[selected.y].cells[selected.x].onKeyPress(key);
	render();
}

void Table::onResize()
{
	unsigned cellWidth = getSize().x / columns - 1;

	for(auto& row : rows)
	{
		for(auto& cell : row.cells)
			cell.setMaximumVisible(cellWidth);
	}
}

void Table::onMouseClick(Point at)
{
	if(at.y % 2 == 1)
	{
		// Calculate the width of a single cell including borders
		unsigned cellWidth = (getSize().x + columns) / columns;

		// Transform the point into a coordinate
		selected.x = at.x / cellWidth; 
		selected.y = at.y / 2;

		render();
	}
}

void Table::set(TableRow& row, size_t index, const std::string& value)
{
	if(index >= columns)
		return;

	row.setCell(index, value);
	//columnLongestValues[index] = std::max(columnLongestValues[index], value.size());

	render();
}

const std::string& TableRow::operator[](size_t index)
{
	static std::string notFound;
	return notFound;
}

void TableRow::set(size_t index, const std::string& value)
{
	table->set(*this, index, value);
}

void TableRow::setCell(size_t index, const std::string& value)
{
	if(index < cells.size())
		cells[index] = value;
}

size_t TableRow::columns()
{
	return cells.size();
}

}
