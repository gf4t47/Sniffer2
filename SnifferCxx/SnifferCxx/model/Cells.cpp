//
//  Cells.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Cells.h"
#include "../support/MyLog.h"
#include <fstream>
#include <sstream>
#include <memory>

namespace Model
{
	using namespace std;
	using namespace Support;

	//	unique_ptr<MyLog> Cells::lg_(make_unique<MyLog>());
	unique_ptr<MyLog> Cells::lg_(new MyLog());

	shared_ptr<Cell> Cells::getCell(const Coordinate& pos) const
	{
		auto find_ret = find(pos);
		if (find_ret == this->end())
		{
			return nullptr;
		}

		return make_shared<Cell>(find_ret->second);
	}

	shared_ptr<Cell> Cells::getCell(coord_item_t x, coord_item_t y, coord_item_t z) const
	{
		return getCell(Coordinate(x, y, z));
	}

	bool Cells::updateCell(const Cell& cell)
	{
		(*this)[cell.getCoordinate()] = cell;
		return true;
	}

	//************************************
	// Method:    mergeCellsByAddMethane : merge two set of cells by add the methane in the same location.
	// FullName:  Model::Cells::mergeCellsByAddMethane
	// Access:    public 
	// Returns:   bool : true merge successfully, otherwise false
	// Qualifier:
	// Parameter: const Cells & cells
	//************************************
	bool Cells::mergeCellsByAddMethane(const Cells& cells)
	{
		for (auto oth_entry : cells)
		{
			auto find_ret = find(oth_entry.first);
			if (find_ret == end())
			{
				updateCell(oth_entry.second);
			}
			else
			{
				if (find_ret->second == oth_entry.second)
				{
					auto original_methane = find_ret->second.getMethane();
					auto new_methane = oth_entry.second.getMethane();
					find_ret->second.setMethane(original_methane + new_methane);
				}
				else
				{
					ostringstream ostr;
					ostr << "two cells to be merged are not same: " << endl;
					ostr << "cell1 = ";
					ostr << find_ret->second << endl;
					ostr << "cell2 = ";
					ostr << oth_entry.second << endl;

					BOOST_LOG_SEV(*lg_, severity_level::error) << ostr.str();
					throw invalid_argument(ostr.str());
				}
			}
		}

		return true;
	}

	ofstream& Cells::toBinary(ofstream& fs) const
	{
		auto cell_num = static_cast<int>(size());
		fs.write(reinterpret_cast<char*>(&cell_num), sizeof cell_num);
		BOOST_LOG_SEV(*lg_, severity_level::detail) << "cell_num=" << cell_num;
		for_each(this->begin(), this->end(), [&fs](const value_type& val_pair)
		         {
			         BOOST_LOG_SEV(*lg_, severity_level::detail) << val_pair.second;
			         val_pair.second.toBinary(fs, false);
		         });

		return fs;
	}
}