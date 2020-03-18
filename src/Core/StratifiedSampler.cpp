#include "./StratifiedSampler.h"
#include <iostream>

StratifiedSampler::StratifiedSampler() { m_numOfSamples = 0; }
StratifiedSampler::~StratifiedSampler(){}
StratifiedSampler::StratifiedSampler(int sampleDim, bool jitter)
{
	m_sampleDim = sampleDim;
	m_numOfSamples = sampleDim * sampleDim;
	m_samples = new Vec2f[m_numOfSamples];
	m_jitter = jitter;
}

Vec2f* StratifiedSampler::sample(int& currX, int& currY)
{	
	float centerOffset = 1.0f / ((float)(m_sampleDim) * 2.0f);

	for (int y = 0; y < m_sampleDim; y++) {
		for (int x = 0; x < m_sampleDim; x++) {

			float jitterX = 0.0f;
			float jitterY = 0.0f;

			if (m_jitter) {
				jitterX = centerOffset * (((double)rand() / (RAND_MAX)) * 2.0f - 1.0f);
				jitterY = centerOffset * (((double)rand() / (RAND_MAX)) * 2.0f - 1.0f);
			}

			Vec2f sample(currX + centerOffset + jitterX, currY + centerOffset + jitterY);

			m_samples[y * m_sampleDim + x] = sample;
		}
	}

	return m_samples;
}

void StratifiedSampler::setJitter(bool jitter) { m_jitter = jitter; }
bool StratifiedSampler::getJitter() { return m_jitter; }