//
//  DetectionInitializer.h
//  SnifferCxx
//
//  Created by Ke Ding  on 8/11/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__DetectionInitializer__
#define __SnifferCxx__DetectionInitializer__

#include <memory>
#include <vector>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include "../model/TypeDef.h"
#include "../runmode/ExecutorFactory.h"

namespace Model {
	struct Candidate;
	struct Detection;
	struct AutoMovement;
	class Map3D;
	class WindVector;
}

namespace RunMode {
	class Executor;
}

namespace Initializer {  
    class DetectionInitializer {
    public:
        DetectionInitializer(std::string cfg_file, const Model::Map3D & map);
        
        std::shared_ptr<std::vector<Model::Detection>> getDetections() const;
		std::shared_ptr<std::vector<Model::Detection>> getCandidates() const;
        std::shared_ptr<Model::AutoMovement> getAutoMovementInfo() const;
		RunMode::execute_mode getExecutorMode() const;
        bool beMultiplethread() const;

		static Model::WindVector transDirectionSpeed2Vector(int wind_direct, double wind_speed);
		static Model::WindVector transLonLat2Coordinate(double lat, double lon);

	protected:
		bool parseJson(std::string json_file);
		bool parseText(std::string text_file);
        
    private:
		std::shared_ptr<std::vector<Model::Detection>> parseJsonNode(const std::string & nodeName, const boost::property_tree::ptree & pt) const;
		std::shared_ptr<std::vector<Model::Detection>> transStringTable2Struct(const std::vector<std::vector<std::string>> & strTable) const;

	public:
		static std::unordered_map<std::string, RunMode::execute_mode> String2Mode;
        
    private:
        std::shared_ptr<std::vector<Model::Detection>> dects_;
        std::shared_ptr<std::vector<Model::Detection>> can_;
        std::shared_ptr<Model::AutoMovement> auto_movement_;
		RunMode::execute_mode mode_;
		const Model::Map3D & map_;
    };
}

#endif /* defined(__SnifferCxx__DetectionInitializer__) */
