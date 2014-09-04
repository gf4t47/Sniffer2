#include "CandidateGenerator.h"
#include "../model/Map3D.h"
#include "../math/Gaussian.h"
#include "../support/MyLog.h"

namespace Backward {
	using namespace std;
	using namespace Model;
	using namespace Forward;
	using namespace Support;

	unique_ptr<MyLog> CandidateGenerator::lg_(make_unique<MyLog>());

	CandidateGenerator::CandidateGenerator(const ForwardChecking & forward, const BackwardChecking & backward, const Map3D & map)
		:map_(map),
		infoGain_(forward, backward, map) {
	}


	CandidateGenerator::~CandidateGenerator()
	{
	}

	shared_ptr<vector<Coordinate>> CandidateGenerator::crossLocation(const Coordinate & curPos, const Map3D & map, unit_t distance) const {
		auto ret = make_shared<vector<Coordinate>>();

		Coordinate newCoord1(curPos[0] + distance, curPos[1], curPos[2]);
		ret->push_back(newCoord1);

		Coordinate newCoord2(curPos[0] - distance, curPos[1], curPos[2]);
		ret->push_back(newCoord2);

		Coordinate newCoord3(curPos[0], curPos[1] + distance, curPos[2]);
		ret->push_back(newCoord3);

		Coordinate newCoord4(curPos[0], curPos[1] - distance, curPos[2]);
		ret->push_back(newCoord4);

		return ret;
	}

	shared_ptr<vector<Coordinate>> CandidateGenerator::randomLocation(const Coordinate & curPos, const Map3D & map, unit_t distance) const {
		auto randoms = Math::Gaussian::RandomCoordinate(curPos, distance, 4);
		for_each(randoms->begin(), randoms->end(), [&curPos](Coordinate & coord){coord[2] = curPos[2]; });
		return randoms;
	}

	shared_ptr<vector<Coordinate>> CandidateGenerator::collisionFilter(const Coordinate & curPos, const vector<Coordinate> & coords, const Map3D & map) const{
		auto ret = make_shared<vector<Coordinate>>();
		for (auto const & coord : coords) {
			if (map.insideMap(coord)) {
				ret->push_back(map.calcCollisionByFullPath(curPos, coord)->getCoordinate());
			}
		}

		return ret;
	}

	vector<Candidate> CandidateGenerator::calcCandidates(const Coordinate & curPos, int time_count, unit_t distance, const Hypotheses & hyps) const {
		auto locations = collisionFilter(curPos, *crossLocation(curPos, map_, distance), map_);
		auto gain_vec = infoGain_.calcInforGains(*locations, hyps, time_count);

		vector<Candidate> can_vec;
		for (int i = 0; i < gain_vec.size(); i++) {
			can_vec.push_back(Candidate(locations->at(i), gain_vec[i]));
			BOOST_LOG_SEV(*lg_, severity_level::info) << "Info Gain: " << locations->at(i) << "->" << gain_vec[i];
		}

		return can_vec;
	}

	Candidate CandidateGenerator::calcBestCandidate(const Coordinate & curPos, int time_count, unit_t distance, const Hypotheses & hyps) const{
		auto locations = collisionFilter(curPos, *crossLocation(curPos, map_, distance), map_);
		auto gain_vec = infoGain_.calcInforGains(*locations, hyps, time_count);
		for (int i = 0; i < gain_vec.size(); i++) {
			BOOST_LOG_SEV(*lg_, severity_level::info) << "Info Gain: " << locations->at(i) << "->" << gain_vec[i];
		}
		auto max_socre = max_element(gain_vec.begin(), gain_vec.end());

		while (max_socre == gain_vec.end()) {
			locations = collisionFilter(curPos, *randomLocation(curPos, map_, distance), map_);
			gain_vec = infoGain_.calcInforGains(*locations, hyps, time_count);
			for (int i = 0; i < gain_vec.size(); i++) {
				BOOST_LOG_SEV(*lg_, severity_level::info) << "Info Gain: " << locations->at(i) << "->" << gain_vec[i];
			}
			max_socre = max_element(gain_vec.begin(), gain_vec.end());
		}

		if (*max_socre <= 0) {
			ostringstream ostr;
			ostr << "negative expected information gain = " << *max_socre;
			BOOST_LOG_SEV(*lg_, severity_level::error) << ostr.str();
			throw runtime_error(ostr.str());
		}

		return Candidate((*locations)[std::distance(gain_vec.begin(), max_socre)], *max_socre);
	}
}

