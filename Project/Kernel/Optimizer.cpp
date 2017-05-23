#include "Optimizer.h"

Number minimize(Tree *tf, NVector const &start, NVector const &end, int points, double diam, Number &val)
{
	ProblemServer l(points);
	vector<Param> params;
	for (int i = 0; i < (int)start.v.size(); i++) {
		Param p;
		p.init(start.v[i], end.v[i], (start.v[i]+end.v[i])/2.0);
		params.push_back(p);
	}
	double result;
	NVector p;
	p = l.differentialEvolutionNew(params, 32, tf, diam, result);
	val = p.v[0];
	return Number(result);	
}

