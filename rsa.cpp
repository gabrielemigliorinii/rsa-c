#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef long long Long;

class Rsa {
	
	// Chiave pubblica (n,e)
	// Chiave privata (p,q,d)
	
	private:
		
		int p, q, e;    
		Long b, n, d;
	
		Long generate_d(Long max=999999999);  				// genera d avendo e, ed b = (p-1)*(q-1)
		int generate_e(int max=99999);						// genera e avendo b = (p-1)*(q-1)
	
	public:
		
		Rsa();
		void crypt(string, int[]);
		int decrypt(int crypted);
		void show_pars();
};

class MATH {
	
	public:
		
		static bool is_prime(int x);
		static int generate_prime(int min, int max);
		static Long MCD(Long, Long);
		static int modularExp(int, int, int);
};


int main(void) {

	srand(time(NULL));
	
	int e; 
	Long d, n;
	
	Rsa rsa;	
	rsa.show_pars();
	
	string message;
	
	cout << " Inserire un messaggio da criptare (numero): ";
	cin >> message;
		
	cout << "\n\n";
	cout << " -> MESSAGGIO ORIGINALE  : "<<message << "\n";
	
	int crypted_message[message.length()];
	rsa.crypt(message, crypted_message); 
	
	for (int i=0; i<sizeof(crypted_message)/sizeof(*crypted_message); i++)
		cout << crypted_message[i] << "\n";
	
	exit(0);
	
//	cout << " -> MESSAGGIO CRIPTATO   : "<<crypted_message << "\n";
	
//	int decrypted_message = rsa.decrypt(crypted_message);
	
//	cout << " -> MESSAGGIO DECRIPTATO : "<<decrypted_message << "\n\n\n";
	
	return 0;
}

Rsa::Rsa(){
	
	this->p = MATH::generate_prime(5,100);
	
	int temp_q = 0;
	
	do {
		
		temp_q = MATH::generate_prime(5,100);
		
		if (temp_q == p) continue; else break;
		
	} while (true);
	
	this->q = temp_q;
	
	this->b = (p-1) * (q-1);
	this->n = p * q;
	
	this->e = generate_e();
	this->d = generate_d();
}

void Rsa::crypt(string msg, int* encr){
		
	int a[msg.length()];
	
	for (int i=0; i<msg.length(); i++)
		a[i] = (int)msg[i];
		
	for (int i=0; i<msg.length(); i++)
		cout << a[i] << "\n";
	
	int enc[msg.length()];
	
	cout << "\n";
	
	for (int i=0; i<msg.length(); i++)
		enc[i] = MATH::modularExp(a[i], e, n);
		
	for (int i=0; i<msg.length(); i++)
		encr[i] = enc[i];
}

int Rsa::decrypt(int crypted){
	
	const int decrypted_message = MATH::modularExp(crypted, d, n);
	return decrypted_message;
}

void Rsa::show_pars(){
	
	cout << "\n\n";
	cout << " -- PARAMETRI PER RSA --\n\n --------------------------------------------------- \n\n";
	cout << "  p: "<<this->p<<endl;
	cout << "  q: "<<this->q<<endl; 
	cout << "  b: "<<this->b<<"    (p-1) * (q-1)\n"; 
	cout << "  n: "<<this->n<<"    (p)   * (q)  \n"; 
	cout << "  e: "<<this->e<<endl; 
	cout << "  d: "<<this->d<<endl;
	cout << "\n --------------------------------------------------- ";  
	cout << "\n\n";
}

Long Rsa::generate_d(Long max) {
	
	for (int d=0; d<max; d++) if ((d * e) % b == 1) return d;
	return -1;
}

int Rsa::generate_e(int max) {
	
	int e = 2;
	
	while (e < max) if (MATH::MCD(e, b) == 1) return e; else e++;
	
	return -1;
}




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


