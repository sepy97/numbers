#include "SparseVector.h"

SparseVector::SparseVector(void)
{
	_size = 0;
}

SparseVector::~SparseVector(void)
{
}

void SparseVector::adjustDimension(int size)
{
	if (size > _size)
	{
		map<vint, RationalNumber> newm;
		for (map<vint, RationalNumber>::const_iterator ci = _m.begin(); ci != _m.end(); ci++)
		{
			vint nv = ci->first;
			nv.resize(size);
			newm.insert(make_pair(nv, ci->second));
		}
		_m = newm;
		_size = size;
	}
}

RationalNumber 
SparseVector::add(vint const &cwh, RationalNumber const &num)
{
	vint wh = cwh;
	if ((int)cwh.size() < _size)
	{
		wh.resize(_size);
	}
	map<vint, RationalNumber>::iterator elem = _m.find(wh);
	if (elem == _m.end())
	{
		_m.insert(make_pair(wh, num));
		return num;
	}
	else
	{
		elem->second += num;
		return elem->second;
	}
}

vector<SparseVector::vint> SparseVector::getAll() const
{
	vector<vint> ret;
	for (map<vint, RationalNumber>::const_iterator ci = _m.begin(); ci != _m.end(); ci++)
	{
		ret.push_back(ci->first);
	}
	return ret;
}

RationalNumber 
SparseVector::get(vint const &cwh) const
{
	map<vint, RationalNumber>::const_iterator elem = _m.find(cwh);
	if (elem == _m.end())
	{
		return RationalNumber("0");
	}
	else
	{
		return elem->second;
	}
}

vector<int> SparseVector::getMaxDegrees() const
{
	vector<int> ret(_m.size());
	for (map<vint, RationalNumber>::const_iterator ci = _m.begin(); ci != _m.end(); ci++)
	{
		vint vf = ci->first;
		for (int j = 0; j < (int)vf.size(); j++)
		{
			if (vf[j] > ret[j]) 
			{
				ret[j] = vf[j];
			}
		}
	}
	return ret;
}
