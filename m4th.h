
#include <math.h>
#include <cstdlib>

typedef long long Long;

class MATH {
	
	public:
		
		static bool is_prime(int x);
		static int generate_prime(int min, int max);
		static Long MCD(Long, Long);
		static int modularExp(int, int, int);
};

bool MATH::is_prime(int x){
			
	x = abs(x);

	if (x < 2) return 0;
	
	else {
		
		const int X = x;
		
		while (x-- > 2) 
			if (X % x == 0) return 0;
			
		return 1;	
	}
}
		
int MATH::generate_prime(int min, int max){
			
	if (min < 0 || max < 0 || min > max || (min == max && !is_prime(max))) return -1;
	if (min < 2) min = 2;
	
	unsigned const int rd = rand() % (max-min) + (min);
	
	if (is_prime(rd)) return rd;
	
	unsigned int t = rd+1;
	
	while (t <= max){
		
		if (is_prime(t)) return t;
		t++;
	}
	if (t > max) t = max;
	
	if (is_prime(t)) return t;
	
	t = rd-1;
		
	while (t >= min){
		
		if (is_prime(t)) return t;
		t--;
	}
	if (t < min) t = min;
	
	if (is_prime(t)) return t;
	return -1;
}

Long MATH::MCD(Long a, Long b) {
 
    a = abs(a);
    b = abs(b);

    if (a==0 && b==0) return -1; // MCD(0,0) => non definito;

    if (a == 0) return b;
    if (b == 0) return a;

    if (a < b) { Long t = a; a = b; b = t; } // se a < b scambia a con b

    Long temp_a, temp_b;

    while (b != 0) {

        temp_a = b;
        temp_b = a % b;

        a = temp_a;
        b = temp_b;
    }

    return a;
}

int MATH::modularExp(int a, int b, int c){
	
	int r = 1;
	int iter = 0;
	
	while (true) {
		
		r = (r*a) % c;
		
		iter++;
		if (iter < b) continue; else break;
	}
	
	return r;
}
