#pragma once

//#define BOOST_LOG_DYN_LINK
#define BOOST_LOG_NO_THREADS

#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace Support {

	enum severity_level
	{
		detail,
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
