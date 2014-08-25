#pragma once
#include "Executor.h"
#include <boost/asio.hpp>

namespace RunMode {

	class AsynEvent :
		public Executor
	{
	public:
		AsynEvent(const Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward);
		virtual ~AsynEvent();

		void run(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, const std::vector<Model::Detection> & dect_vec);

	private:
		void handle_Deduce(Model::Hypotheses & hyps);
		void handle_Detection(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, std::vector<Model::Detection>::const_iterator dect, const std::vector<Model::Detection> & dect_vec, const boost::system::error_code & error);

	private:
		boost::asio::io_service io_service_;
		boost::asio::deadline_timer dect_timer_;
	};

}

