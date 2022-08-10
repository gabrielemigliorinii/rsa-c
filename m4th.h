
#include <math.h>
#include <cstdlib>

typedef long long int Integer;

class MATH {
	
	public:
		
		static bool is_prime(Integer x);
		static Integer generate_prime(Integer min, Integer max);
		static Integer MCD(Integer, Integer);
		static Integer modularExp(Integer, Integer, Integer);
};

bool MATH::is_prime(Integer x){
			
	x = abs(x);

	if (x < 2) return 0;
	
	else {
		
		const Integer X = x;
		
		while (x-- > 2) 
			if (X % x == 0) return 0;
			
		return 1;	
	}
}
		
Integer MATH::generate_prime(Integer min, Integer max){
			
	if (min < 0 || max < 0 || min > max || (min == max && !is_prime(max))) return -1;
	if (min < 2) min = 2;
	
	unsigned const long long int rd = rand() % (max-min) + (min);
	
	if (is_prime(rd)) return rd;
	
	unsigned long long int t = rd+1;
	
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

Integer MATH::MCD(Integer a, Integer b) {
 
    a = abs(a);
    b = abs(b);

    if (a==0 && b==0) return -1; // MCD(0,0) => non definito;

    if (a == 0) return b;
    if (b == 0) return a;

    if (a < b) { Integer t = a; a = b; b = t; } // se a < b scambia a con b

    Integer temp_a, temp_b;

    while (b != 0) {

        temp_a = b;
        temp_b = a % b;

        a = temp_a;
        b = temp_b;
    }

    return a;
}

Integer MATH::modularExp(Integer a, Integer b, Integer c){
	
	Integer r = 1;
	
	for (Integer iter = 0; iter < b; iter++)
		r = (r*a) % c;	
	
	return r;
}
