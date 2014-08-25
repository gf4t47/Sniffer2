#pragma once
#include "Executor.h"
#include <boost/asio.hpp>

namespace RunMode {

	class AsynEvent :
		public Executor
	{
	public:
		AsynEvent(Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward);
		virtual ~AsynEvent();

		void run(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, const std::vector<Model::Detection> & dect_vec);
		void autoDrive(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, std::vector<Model::Detection> & dect_vec, const Model::AutoMovement & auto_info);

	private:
		void handle_Deduce(Model::Hypotheses & hyps);
		void handle_Detection(Model::Hypotheses & hyps, const Model::Detection & dect);

	private:
		boost::asio::io_service io_service_;
		boost::asio::deadline_timer dect_timer_;
	};

}

