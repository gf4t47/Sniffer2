#pragma once

#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace Support {

	enum severity_level
	{
		trace,
		debug,
		info,
		error,
		critical
	};

	class MyLog : public boost::log::sources::severity_logger < severity_level >
	{
	public:
		MyLog();
		~MyLog();

		static void init_log(std::string filename);
	};

}
