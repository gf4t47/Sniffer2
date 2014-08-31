#include "DirectMessageBuilder.h"
#include <fstream>
#include "../support/MyLog.h"
#include "../model/Map3D.h"
#include "../model/Candidate.h"
#include "../model/Hypotheses.h"

namespace DirectMsg {
	using namespace std;
	using namespace Support;

	unique_ptr<MyLog> DirectMessageBuilder::lg_(make_unique<MyLog>());

	DirectMessageBuilder::DirectMessageBuilder(
		std::pair<std::string, std::shared_ptr<std::vector<std::shared_ptr<Model::Hypotheses>>>> mtn_info,
		std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> dect_info,
		std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> can_info,
		std::pair<std::string, std::shared_ptr<Model::Map3D>> map_info
		)
	:mtn_info_(mtn_info),
	dect_info_(dect_info),
	can_info_(can_info),
	map_info_(map_info) {
	}


	DirectMessageBuilder::~DirectMessageBuilder() {
	}

	void DirectMessageBuilder::WriteMsg(int ideal_cells, bool detection_only) {
		ofstream map_out(map_info_.first, ios::out | ios::trunc | ios::binary);
		map_out << *map_info_.second;
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Map message is written into " << map_info_.first;

		ofstream dect_out(dect_info_.first, ios::out | ios::trunc | ios::binary);
		dect_out << static_cast<int>(dect_info_.second->size());
		for (auto const & dect : *dect_info_.second) {
			dect_out << dect;
		}
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Detection message is written into " << dect_info_.first;

		ofstream can_out(can_info_.first, ios::out | ios::binary);
		can_out << 2 << "tyy" << static_cast<int>(can_info_.second->size());
		for (auto const & can : *can_info_.second) {
			can_out << can;
		}
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Candidate message is written to file" << can_info_.first;

		ofstream mtn_out(mtn_info_.first, ios::out | ios::trunc | ios::binary);
		mtn_out << static_cast<int>(mtn_info_.second->size());
		for (auto hyps : *mtn_info_.second) {
			mtn_out << *hyps;
		}
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Methane message is written into " << mtn_info_.first;
	}
}