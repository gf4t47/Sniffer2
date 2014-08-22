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
#include <boost/property_tree/ptree.hpp>
#include "../model/WindVector.h"

namespace Model {
	struct Candidate;
	class Map3D;
}

namespace Initializer {
    struct Detection {
        int time_;
		boost::optional<Model::WindVector> wv_;
        std::vector<Model::Candidate> detected_;
    };
    
    struct AutoMovement {
        int time_;
        double threshold_;
        Model::unit_t distance_;
    };
    
    class DetectionInitializer {
    public:
        DetectionInitializer(std::string cfg_file, const Model::Map3D & map);
        
        std::shared_ptr<std::vector<Detection>> getDetections() const;
        std::shared_ptr<std::vector<Detection>> getCandidates() const;
        std::shared_ptr<AutoMovement> getAutoMovementInfo() const;
        bool beMultiplethread() const;

		static Model::WindVector transDirectionSpeed2Vector(int wind_direct, double wind_speed);
		static Model::WindVector transLonLat2Coordinate(double lat, double lon);

	protected:
		bool parseJson(std::string json_file);
		bool parseText(std::string text_file);
        
    private:
        std::shared_ptr<std::vector<Detection>> parseJsonNode(const std::string & nodeName, const boost::property_tree::ptree & pt) const;
		std::shared_ptr<std::vector<Detection>> transStringTable2Struct(const std::vector<std::vector<std::string>> & strTable) const;
        
    private:
        std::shared_ptr<std::vector<Detection>> dects_;
        std::shared_ptr<std::vector<Detection>> can_;
        std::shared_ptr<AutoMovement> auto_movement_;
        bool multiplethread_flag_;
		const Model::Map3D & map_;
    };
}

#endif /* defined(__SnifferCxx__DetectionInitializer__) */
