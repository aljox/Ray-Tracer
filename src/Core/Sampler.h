#pragma once

#include "../Math/Vec2f.h"
#include <stdlib.h>

class Sampler
{
	protected:
		int m_numOfSamples;
		Vec2f* m_samples;

	public:
		Sampler();
		~Sampler();
		Sampler(int num);

		virtual Vec2f* sample(int& currX, int& currY);

		void setNumOfSamples(int num);
		int getNumOfSamples();
};