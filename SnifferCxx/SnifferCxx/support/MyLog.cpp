#include "MyLog.h"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace Support
{
	namespace logging = boost::log;
	namespace src = boost::log::sources;
	namespace sinks = boost::log::sinks;
	namespace keywords = boost::log::keywords;

	BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level);

	MyLog::MyLog()
	{
	}


	MyLog::~MyLog()
	{
	}

	void MyLog::init_log(std::string filename)
	{
		std::ostringstream ostr;
		ostr << filename << "_%N.log";

		logging::add_file_log
			(
				keywords::file_name = ostr.str(),
				keywords::rotation_size = 10 * 1024 * 1024,
				keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
				keywords::format = "[%TimeStamp%]: %Message%"
			);

		logging::add_console_log(std::cout, keywords::format = "[%TimeStamp%]: %Message%");

		logging::core::get()->set_filter
			(
				severity >= severity_level::trace
			);

		boost::log::add_common_attributes();
		//logging::register_simple_formatter_factory<severity_level>(severity);
	}
}