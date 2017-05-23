
#ifndef __simt__Random__
#define __simt__Random__

class Random
{
public:
    Random();
    ~Random();
    double nextGaussian() const;
    double nextDouble() const;
    int    nextInt(int max) const;
    bool   nextBool() const;
	void   srand(unsigned seed);
private:
	mutable double nextNextGaussian;
	mutable bool haveNextNextGaussian;
};

#endif /* defined(__simt__Random__) */
