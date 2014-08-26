//
//  DetectionInitializer.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 8/11/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "DetectionInitializer.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include "../model/Candidate.h"
#include "../model/Map3D.h"

namespace Initializer {
	using namespace std;
	using namespace Model;
	using namespace RunMode;
	using boost::property_tree::ptree;

	const auto PI = boost::math::constants::pi<double>();

	unordered_map<string, execute_mode> DetectionInitializer::String2Mode =
	{
		{"single", execute_mode::single},
		{"asyn", execute_mode::asyn_event},
		{"multithread", execute_mode::multi_thread}
	};

	DetectionInitializer::DetectionInitializer(string cfg_file, const Map3D & map)
		:map_(map) {
		try {
			parseJson(cfg_file);
		}
		catch (exception & e) {
			if (!parseText(cfg_file)) {
				throw e;
			}
		}

		for (int i = 0; i < dects_->size(); i++) {
			BOOST_LOG_SEV(lg_, severity_level::info) << "load detection" << i << " = " << dects_->at(i);
		}
	}

	shared_ptr<vector<Detection>> DetectionInitializer::parseJsonNode(const string & nodeName, const boost::property_tree::ptree & pt) const{
		const string strTime = "time";
		const string strDect = "dect";
		const string strLocation = "location";
		const string strConcentration = "concentration";
		const string strRepeat = "repeat";
		const string strWind = "wind";

		using boost::lexical_cast;

		auto ret_vec = make_shared<vector<Detection>>();
		auto node = pt.get_child_optional(nodeName);
		if (!node) {
			return ret_vec;
		}

		for (auto dect_node : *node) {
			auto dect = dect_node.second;
			Detection detection;

			detection.time_ = dect.get<int>(strTime);

			auto node_wind = dect.get_child_optional(strWind);
			if (node_wind) {
				detection.wv_ = WindVector();
				transform(node_wind->begin(), node_wind->end(), (*detection.wv_).begin(), [](ptree::value_type & v){return lexical_cast<wv_item_t>(v.second.data()); });
			}

			for (auto leak_node : dect.get_child(strDect)) {
				auto leak = leak_node.second;

				Candidate detected;
				auto location = leak.get_child(strLocation);
				transform(location.begin(), location.end(), detected.location_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data()); });
				auto concentration_node = leak.get_optional<mtn_t>(strConcentration);
				if (concentration_node) {
					detected.concentration_ = *concentration_node;
				}

				detection.detected_.push_back(detected);
			}

			auto repeat = dect.get_optional<size_t>(strRepeat);
			if (repeat) {
				for (auto i = 0; i < *repeat; i++) {
					ret_vec->push_back(detection);
				}
			}
		}

		return ret_vec;
	}

	bool DetectionInitializer::parseJson(string json_file) {
		const string strDetection = "detection";
		const string strCandidate = "candidate";
		const string strRunMode = "runmode";
		const string strAuto = "automovement";
		const string strDistance = "distance";
		const string strThreshold = "threshold";
		const string strTime = "time";

		ptree pt;
		read_json(json_file, pt);

		mode_ = String2Mode[pt.get<string>(strRunMode)];

		dects_ = parseJsonNode(strDetection, pt);

		can_ = parseJsonNode(strCandidate, pt);

		auto auto_node = pt.get_child_optional(strAuto);
		if (auto_node) {
			auto_movement_ = make_shared<AutoMovement>();
			auto_movement_->time_ = auto_node->get<int>(strTime);
			auto_movement_->threshold_ = auto_node->get<double>(strThreshold);
			auto_movement_->distance_ = auto_node->get<unit_t>(strDistance);
		}

		return true;
	}

	WindVector DetectionInitializer::transDirectionSpeed2Vector(int wind_direct, double wind_speed) {
		auto x = wind_speed * sin(wind_direct * PI / 180.0);
		auto y = wind_speed * cos(wind_direct * PI / 180.0);
		auto z = 0;

		return WindVector(x, y, z);
	}

	//************************************
	// Method:    transLonLat2Coordinate
	// FullName:  Initializer::DetectionInitializer::transLonLat2Coordinate
	// Access:    public static 
	// Returns:   Model::Coordinate
	// Qualifier:
	// Parameter: double lat
	// Parameter: double lon
	// Converts lat/long to UTM coords.  Equations from USGS Bulletin 1532 
	// East Longitudes are positive, West longitudes are negative. 
	// North latitudes are positive, South latitudes are negative
	// Lat and Long are in decimal degrees
	// Written by Chuck Gantz- chuck.gantz@globalstar.com
	//************************************
	WindVector DetectionInitializer::transLonLat2Coordinate(double lat, double lon) {
		double k0 = 0.9996;
		double a = 6378137;          // equatorial radius
		double eccSqrd = 0.00669438;       // square of eccentricity
		double latRad = lat*PI / 180.0;
		double lonTmp = (lon + 180) - (int)((lon + 180) / 360) * 360 - 180; // -180.0 .. 179.9; Ensure lon between -180.0 & 179.9
		double lonRad = lonTmp*PI / 180.0;
		int zoneNum = (int)((lonTmp + 180) / 6) + 1;


		if (lat >= 56.0 && lat < 64.0 && lonTmp >= 3.0 && lonTmp < 12.0)
			zoneNum = 32;
		if (lat >= 72.0 && lat < 84.0)	// Special zones for Svalbard  
		{
			if (lonTmp >= 0.0  && lonTmp < 9.0) zoneNum = 31;
			else if (lonTmp >= 9.0  && lonTmp < 21.0) zoneNum = 33;
			else if (lonTmp >= 21.0 && lonTmp < 33.0) zoneNum = 35;
			else if (lonTmp >= 33.0 && lonTmp < 42.0) zoneNum = 37;
		}
		auto lonOrigin = (zoneNum - 1) * 6 - 180 + 3;  //+3 puts origin in middle of zone
		auto lonOrgRad = lonOrigin*PI / 180.0;


		//compute UTM Zone from the latitude and longitude
		//sprintf(UTMZone, "%d%c", ZoneNumber, UTMLetterDesignator(Lat));
		auto eccPrimeSqrd = (eccSqrd) / (1 - eccSqrd);

		auto N = a / sqrt(1 - eccSqrd*sin(latRad)*sin(latRad));
		auto T = tan(latRad)*tan(latRad);
		auto C = eccPrimeSqrd*cos(latRad)*cos(latRad);
		auto A = cos(latRad)*(lonRad - lonOrgRad);

		auto M = a*((1 - eccSqrd / 4 - 3 * eccSqrd*eccSqrd / 64 - 5 * eccSqrd*eccSqrd*eccSqrd / 256)*latRad
			- (3 * eccSqrd / 8 + 3 * eccSqrd*eccSqrd / 32 + 45 * eccSqrd*eccSqrd*eccSqrd / 1024)*sin(2 * latRad)
			+ (15 * eccSqrd*eccSqrd / 256 + 45 * eccSqrd*eccSqrd*eccSqrd / 1024)*sin(4 * latRad)
			- (35 * eccSqrd*eccSqrd*eccSqrd / 3072)*sin(6 * latRad));

		auto easting = (double)(k0*N*(A + (1 - T + C)*A*A*A / 6
			+ (5 - 18 * T + T*T + 72 * C - 58 * eccPrimeSqrd)*A*A*A*A*A / 120)
			+ 500000.0);

		auto northing = (double)(k0*(M + N*tan(latRad)*(A*A / 2 + (5 - T + 9 * C + 4 * C*C)*A*A*A*A / 24
			+ (61 - 58 * T + T*T + 600 * C - 330 * eccPrimeSqrd)*A*A*A*A*A*A / 720)));
		if (lat < 0) {
			northing += 10000000.0; //10000000 meter offset for southern hemisphere
		}

		return WindVector(easting, northing, 0);

	}

	shared_ptr<vector<Detection>> DetectionInitializer::transStringTable2Struct(const std::vector<std::vector<string>> & strTable) const{
		const int initial_time = 3000; //milliseconds
		using boost::lexical_cast;

		auto ret_vec = make_shared<vector<Detection>>();

		boost::optional<int> last_time;
		//ofstream ofs("temp.txt");
		for (auto const & strVec : strTable) {
			Detection dect;

			auto cur_time = lexical_cast<int>(strVec[0]);
			if (last_time) {
				dect.time_ = cur_time - *last_time;
			}
			else {
				dect.time_ = initial_time;
			}
			last_time = cur_time;

			auto wind_direct = lexical_cast<int>(strVec[3]);
			auto wind_speed = lexical_cast<double>(strVec[4]);
			auto wind = transDirectionSpeed2Vector(wind_direct, wind_speed);
			dect.wv_ = wind;

			auto lon = lexical_cast<double>(strVec[5]); //x
			auto lat = lexical_cast<double>(strVec[6]); //y
			auto location = map_.locateIndex(transLonLat2Coordinate(lat, lon));
			//ofs << location << endl;
			auto mtn = lexical_cast<double>(strVec[1]) * 1000000;
			dect.detected_.push_back(Candidate(location, mtn));

			ret_vec->push_back(dect);
		}

		return ret_vec;
	}

	bool DetectionInitializer::parseText(string text_file) {
		ifstream ifs(text_file, ios::in);
		if (!ifs.is_open()) {
			ostringstream ostr;
			ostr << "can not open cfg file " << text_file;
			throw invalid_argument(ostr.str());
		}

		string line;
		vector<vector<string>> strTable;
		while (getline(ifs, line)) {
			vector<string> strVec;
			istringstream istr(line);

			string item;
			while (istr >> item){
				strVec.push_back(item);
			}

			strTable.push_back(strVec);
		}

		dects_ = transStringTable2Struct(strTable);
		mode_ = RunMode::execute_mode::asyn_event;

		return dects_ != nullptr;
	}

	shared_ptr<vector<Detection>> DetectionInitializer::getDetections() const{
		return dects_;
	}

	shared_ptr<vector<Detection>> DetectionInitializer::getCandidates() const{
		return can_;
	}

	shared_ptr<AutoMovement> DetectionInitializer::getAutoMovementInfo() const{
		return auto_movement_;
	}

	RunMode::execute_mode DetectionInitializer::getExecutorMode() const {
		return mode_;
	}

}