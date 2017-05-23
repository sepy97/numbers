
#include "Random.h"

#define STDRAND 1

#if STDRAND
#include <stdlib.h>
#else

#include "emmintrin.h"
void srand_sse( unsigned int seed );
void rand_sse( unsigned int* );
__declspec( align(16) ) static __m128i cur_seed;

void srand_sse( unsigned int seed )
{
    cur_seed = _mm_set_epi32( seed, seed+1, seed, seed+1 );
}

inline void rand_sse( unsigned int* result )
{
	__declspec( align(16) ) __m128i cur_seed_split;
	__declspec( align(16) ) __m128i multiplier;
	__declspec( align(16) ) __m128i adder;
	__declspec( align(16) ) __m128i mod_mask;
	__declspec( align(16) ) __m128i sra_mask;
	// __declspec( align(16) ) __m128i sseresult;
	__declspec( align(16) ) static const unsigned int mult[4] =
	{ 214013, 17405, 214013, 69069 };
	__declspec( align(16) ) static const unsigned int gadd[4] =
	{ 2531011, 10395331, 13737667, 1 };
	__declspec( align(16) ) static const unsigned int mask[4] =
	{ 0xFFFFFFFF, 0, 0xFFFFFFFF, 0 };
	__declspec( align(16) ) static const unsigned int masklo[4] =
	{ 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF };
    
	adder = _mm_load_si128( (__m128i*) gadd);
	multiplier = _mm_load_si128( (__m128i*) mult);
	mod_mask = _mm_load_si128( (__m128i*) mask);
	sra_mask = _mm_load_si128( (__m128i*) masklo);
	cur_seed_split = _mm_shuffle_epi32( cur_seed, _MM_SHUFFLE( 2, 3, 0, 1 ) );
    
	cur_seed = _mm_mul_epu32( cur_seed, multiplier );
	multiplier = _mm_shuffle_epi32( multiplier, _MM_SHUFFLE( 2, 3, 0, 1 ) );
	cur_seed_split = _mm_mul_epu32( cur_seed_split, multiplier );
    
	cur_seed = _mm_and_si128( cur_seed, mod_mask);
	cur_seed_split = _mm_and_si128( cur_seed_split, mod_mask );
	cur_seed_split = _mm_shuffle_epi32( cur_seed_split, _MM_SHUFFLE( 2, 3, 0, 1 ) );
	cur_seed = _mm_or_si128( cur_seed, cur_seed_split );
    
	cur_seed = _mm_add_epi32( cur_seed, adder);
	_mm_storeu_si128( (__m128i*) result, cur_seed);
	return;
}

const unsigned RANDOM_SSE_MAX = 0xFFFFFFFFu;
static unsigned random_sse()
{
	unsigned r[4] = {0,0,0,0};
	rand_sse(r);
	return r[0];
}

#endif

void Random::srand(unsigned seed)
{
#if STDRAND
	::srand(seed);
#else
	srand_sse(seed);
#endif
}



#include <math.h>


Random::Random(void)
{
	haveNextNextGaussian = false;
}

Random::~Random(void)
{
}


bool Random::nextBool() const
{
#if STDRAND
	if (rand() % (RAND_MAX) < (RAND_MAX / 2))
	{
		return true;
	}
	return false;
#else
    if (random_sse() % 32768 < 16384) return true;
    return false;
#endif
}

int Random::nextInt(int max) const
{
#if STDRAND
	return rand() % max;
#else
    return random_sse() % max;
#endif
}

double Random::nextDouble() const
{
#if STDRAND
	return (double)rand() / RAND_MAX;
#else
    return (double)random_sse() / RANDOM_SSE_MAX;
#endif
}

double Random::nextGaussian() const
{
    if (haveNextNextGaussian) {
        haveNextNextGaussian = false;
        return nextNextGaussian;
    } else {
        double v1, v2, s;
        do {
            v1 = 2 * nextDouble() - 1;   // between -1.0 and 1.0
            v2 = 2 * nextDouble() - 1;   // between -1.0 and 1.0
            s = v1 * v1 + v2 * v2;
        } while (s >= 1 || s == 0);
        double multiplier = sqrt(-2 * log(s)/s);
        nextNextGaussian = v2 * multiplier;
        haveNextNextGaussian = true;
        return v1 * multiplier;
    }
}

