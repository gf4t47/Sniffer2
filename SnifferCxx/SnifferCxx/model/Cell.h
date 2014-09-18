//
//  Cell.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Cell__
#define __Sniffer_Cxx__Cell__

#include <iostream>
#include <unordered_map>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "Wind.h"
#include "Methane.h"
#include "Coordinate.h"

namespace Model
{
	enum class CellTag
	{
		Air = 1,
		Ground = 2,
		Building = 3
	};

	struct enum_hash
	{
		template <typename T>
		inline
		typename std::enable_if<std::is_enum<T>::value, size_t>::type
		operator ()(T const value) const
		{
			return static_cast<size_t>(value);
		}
	};

	class Cell
	{
	public:
		Cell();
		Cell(Coordinate& coord, CellTag tag, Methane& mtn, Wind& wind);

		const Wind& getWind() const;
		const Methane& getMethane() const;
		const Coordinate& getCoordinate() const;
		CellTag getTag() const;

		bool setMethane(const Methane& mtn);
		bool setCellTag(const CellTag& tag);
		bool setWindVector(const WindVector* wind);
		bool setPotential(const WindVector& potential);
		bool setCoordinate(const Coordinate& coord);

		bool isAirCell() const;
		bool hasMethane() const;

		bool operator==(const Cell& oth) const;
		friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
		std::ofstream& toBinary(std::ofstream& fs, boost::tribool include_wind) const;

		friend class boost::serialization::access;

		template <class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & coord_;
			ar & tag_;
			ar & mtn_;
			ar & wind_;
		}

	public:
		static std::unordered_map<CellTag, std::string, enum_hash> TagString;

	private:
		Coordinate coord_;
		CellTag tag_;
		Methane mtn_;
		Wind wind_;
	};
}

#endif /* defined(__Sniffer_Cxx__Cell__) */