#pragma once

#include "../model/Candidate.h"
#include "InformationGain.h"

namespace Support {
	class MyLog;
}

namespace Backward {
	class CandidateGenerator
	{
	public:
		CandidateGenerator(const Forward::ForwardChecking & forward, const BackwardChecking & backward, const Model::Map3D & map);
		virtual ~CandidateGenerator();

		Model::Candidate generateCandidate(const Model::Coordinate & curPos, int time_count, Model::unit_t distance, const Model::Hypotheses & hyps) const;

	private:
		std::shared_ptr<std::vector<Model::Coordinate>> crossLocation(const Model::Coordinate & curPos, const Model::Map3D & map, Model::unit_t distance) const;
		std::shared_ptr<std::vector<Model::Coordinate>> randomLocation(const Model::Coordinate & curPos, const Model::Map3D & map, Model::unit_t distance) const;
		std::shared_ptr<std::vector<Model::Coordinate>> collisionFilter(const Model::Coordinate & curPos, const std::vector<Model::Coordinate> & coords, const Model::Map3D & map) const;

	private:
		const Model::Map3D & map_;
		InformationGain infoGain_;
		static std::unique_ptr<Support::MyLog> lg_;
	};

}

