#include "DirectMessageBuilder.h"
#include <fstream>
#include "../support/MyLog.h"
#include "../model/Map3D.h"
#include "../model/Candidate.h"
#include "../model/Hypotheses.h"

namespace DirectMsg
{
	using namespace std;
	using namespace Support;

	//	unique_ptr<MyLog> DirectMessageBuilder::lg_(make_unique<MyLog>());
	unique_ptr<MyLog> DirectMessageBuilder::lg_(new MyLog());

	DirectMessageBuilder::DirectMessageBuilder(
		pair<string, shared_ptr<vector<shared_ptr<Model::Hypotheses>>>> mtn_info,
		pair<string, shared_ptr<vector<Model::Detection>>> dect_info,
		pair<string, shared_ptr<vector<Model::Detection>>> can_info,
		pair<string, shared_ptr<Model::Map3D>> map_info
	)
		:mtn_info_(mtn_info),
		 dect_info_(dect_info),
		 can_info_(can_info),
		 map_info_(map_info)
	{
	}

	void DirectMessageBuilder::WriteMsg(int ideal_cells, bool detection_only)
	{
		ofstream map_out(map_info_.first, ios::out | ios::trunc | ios::binary);
		map_info_.second->toBinary(map_out);
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Map message is written into " << map_info_.first;

		ofstream dect_out(dect_info_.first, ios::out | ios::trunc | ios::binary);
		auto dect_num = static_cast<int>(dect_info_.second->size());
		dect_out.write(reinterpret_cast<char*>(&dect_num), sizeof dect_num);
		for_each(dect_info_.second->begin(), dect_info_.second->end(), [&dect_out](Model::Detection const& dect)
		         {
			         dect.toBinary(dect_out);
		         });
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Detection message is written into " << dect_info_.first;

		ofstream can_out(can_info_.first, ios::out | ios::trunc | ios::binary);
		auto can_num = static_cast<int>(can_info_.second->size());
		can_out.write(reinterpret_cast<char*>(&can_num), sizeof can_num);
		for_each(can_info_.second->begin(), can_info_.second->end(), [&can_out](Model::Detection const& can)
		         {
			         can.toBinary(can_out);
		         });
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Candidate message is written to file" << can_info_.first;

		ofstream mtn_out(mtn_info_.first, ios::out | ios::trunc | ios::binary);
		auto mtn_num = static_cast<int>(mtn_info_.second->size());
		mtn_out.write(reinterpret_cast<char*>(&mtn_num), sizeof mtn_num);
		BOOST_LOG_SEV(*lg_, severity_level::debug) << "mtn_num = " << mtn_num;
		for_each(mtn_info_.second->begin(), mtn_info_.second->end(), [&mtn_out](shared_ptr<Model::Hypotheses> const& hyps)
		         {
			         hyps->toBinary(mtn_out);
		         });
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Methane message is written into " << mtn_info_.first;
	}
}