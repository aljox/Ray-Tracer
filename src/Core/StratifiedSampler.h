#pragma once
#include "./Sampler.h"

class StratifiedSampler : public Sampler
{	
	private:
		int m_sampleDim;
		bool m_jitter;

	public:
		StratifiedSampler();
		~StratifiedSampler();
		StratifiedSampler(int sampleDim, bool jitter);

		Vec2f* sample(int& currX, int& currY);

		void setJitter(bool jitter);
		bool getJitter();
};