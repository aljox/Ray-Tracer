#include "./Sampler.h"

Sampler::Sampler() { m_numOfSamples = 0; }
Sampler::~Sampler() { delete[] m_samples; }
Sampler::Sampler(int num) 
{  
	m_numOfSamples = num;
	m_samples = new Vec2f[m_numOfSamples];
}

Vec2f* Sampler::sample(int& currX, int& currY)
{	
	for (int i = 0; i < m_numOfSamples; i++) {
		Vec2f sample(currX + ((double)rand() / (RAND_MAX)), currY + ((double)rand() / (RAND_MAX)));
		m_samples[i] = sample;
	}

	return m_samples;
}

void Sampler::setNumOfSamples(int num) { m_numOfSamples = num; }
int Sampler::getNumOfSamples() { return m_numOfSamples; }