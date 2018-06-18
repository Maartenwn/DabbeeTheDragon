#include <math.h>

typedef struct {
	double r;       // ∈ [0, 1]
	double g;       // ∈ [0, 1]
	double b;       // ∈ [0, 1]
} rgb;

typedef struct {
	double h;       // ∈ [0, 360]
	double s;       // ∈ [0, 1]
	double v;       // ∈ [0, 1]
} hsv;

rgb hsv2rgb(hsv HSV)
{
	rgb RGB;
	double H = HSV.h, S = HSV.s, V = HSV.v,
		P, Q, T,
		fract;

	(H == 360.) ? (H = 0.) : (H /= 60.);
	fract = H - floor(H);

	P = V * (1. - S);
	Q = V * (1. - S * fract);
	T = V * (1. - S * (1. - fract));

	if (0. <= H && H < 1.)
		RGB = {V,T,P };
	else if (1. <= H && H < 2.)
		RGB ={Q,V,P };
	else if (2. <= H && H < 3.)
		RGB = {P,V,T };
	else if (3. <= H && H < 4.)
		RGB =  {P, Q, V };
	else if (4. <= H && H < 5.)
		RGB = {T,P, V };
	else if (5. <= H && H < 6.)
		RGB = {V,P,Q };
	else
		RGB = {0.,0.,0. };

	return RGB;
}