#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Support {
	class MyLog;
}

namespace Model {
	class Hypotheses;
	class Map3D;
	struct Detection;
}

namespace DirectMsg {
	class Hypotheses_history;
	class Detections;
	class Cell;
	class Map;

	class DirectMessageBuilder
	{
	public:
		DirectMessageBuilder(
			std::pair<std::string, std::shared_ptr<std::vector<std::shared_ptr<Model::Hypotheses>>>> mtn_info,
			std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> dect_info,
			std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> can_info,
			std::pair<std::string, std::shared_ptr<Model::Map3D>> map_info
			);
		void WriteMsg(int ideal_cells, bool detection_only);

	private:
		std::pair<std::string, std::shared_ptr<std::vector<std::shared_ptr<Model::Hypotheses>>>> mtn_info_;
		std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> dect_info_;
		std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> can_info_;
		std::pair<std::string, std::shared_ptr<Model::Map3D>> map_info_;

		static std::unique_ptr<Support::MyLog> lg_;
	};
}
