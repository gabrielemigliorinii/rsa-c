#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

typedef long long Long;

class RSA {
	
	// Chiave pubblica (n,e)
	// Chiave privata (p,q,d)
	
	private:
		
		int p, q, e;    
		Long b, n, d;
		
		Long gen_d(Long max=999999999);  				// genera d avendo e, ed b = (p-1)*(q-1)
		int gen_e(int max=99999);						// genera e avendo b = (p-1)*(q-1)
	
	public:
		
		RSA();
		string encrypt(string, int[]);
		string decrypt(int[], int);
		void show_pars();
		string get_pbc_key();
		string get_prv_key();
};

class MATH {
	
	public:
		
		static bool is_prime(int x);
		static int generate_prime(int min, int max);
		static Long MCD(Long, Long);
		static int modularExp(int, int, int);
};


static const char* B64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int B64index[256] =
{
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  62, 63, 62, 62, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0,  0,  0,  0,  63,
    0,  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
};

const std::string b64encode(const void* data, const size_t &len)
{
    std::string result((len + 2) / 3 * 4, '=');
    unsigned char *p = (unsigned  char*) data;
    char *str = &result[0];
    size_t j = 0, pad = len % 3;
    const size_t last = len - pad;

    for (size_t i = 0; i < last; i += 3)
    {
        int n = int(p[i]) << 16 | int(p[i + 1]) << 8 | p[i + 2];
        str[j++] = B64chars[n >> 18];
        str[j++] = B64chars[n >> 12 & 0x3F];
        str[j++] = B64chars[n >> 6 & 0x3F];
        str[j++] = B64chars[n & 0x3F];
    }
    if (pad)  /// Set padding
    {
        int n = --pad ? int(p[last]) << 8 | p[last + 1] : p[last];
        str[j++] = B64chars[pad ? n >> 10 & 0x3F : n >> 2];
        str[j++] = B64chars[pad ? n >> 4 & 0x03F : n << 4 & 0x3F];
        str[j++] = pad ? B64chars[n << 2 & 0x3F] : '=';
    }
    return result;
}

const std::string b64decode(const void* data, const size_t &len)
{
    if (len == 0) return "";

    unsigned char *p = (unsigned char*) data;
    size_t j = 0,
        pad1 = len % 4 || p[len - 1] == '=',
        pad2 = pad1 && (len % 4 > 2 || p[len - 2] != '=');
    const size_t last = (len - pad1) / 4 << 2;
    std::string result(last / 4 * 3 + pad1 + pad2, '\0');
    unsigned char *str = (unsigned char*) &result[0];

    for (size_t i = 0; i < last; i += 4)
    {
        int n = B64index[p[i]] << 18 | B64index[p[i + 1]] << 12 | B64index[p[i + 2]] << 6 | B64index[p[i + 3]];
        str[j++] = n >> 16;
        str[j++] = n >> 8 & 0xFF;
        str[j++] = n & 0xFF;
    }
    if (pad1)
    {
        int n = B64index[p[last]] << 18 | B64index[p[last + 1]] << 12;
        str[j++] = n >> 16;
        if (pad2)
        {
            n |= B64index[p[last + 2]] << 6;
            str[j++] = n >> 8 & 0xFF;
        }
    }
    return result;
}

std::string b64encode(const std::string& str)
{
    return b64encode(str.c_str(), str.size());
}

std::string b64decode(const std::string& str64)
{
    return b64decode(str64.c_str(), str64.size());
}







int main (void) {

	srand(time(NULL));
	
	RSA rsa;
	
	string plain;
	
	cout << "\n >> INPUT PLAINTEXT: ";
	getline(cin, plain);
		
	cout << "\n";
	
	int cipher_array[plain.length()];
	
	string cipher_string = rsa.encrypt(plain, cipher_array);
	
	cout << " >> CIPHERTEXT: " << cipher_string << "\n\n";
	
	cout << " >> PLAINTEXT: " << rsa.decrypt(cipher_array, *(&cipher_array+1)-cipher_array);
	
	cout << "\n\n";
	
	return 0;
}

RSA::RSA(){
	
	this->p = MATH::generate_prime(5,100);
	
	int temp_q = 0;
	
	do {
		
		temp_q = MATH::generate_prime(5,100);
		
		if (temp_q == p) continue; else break;
		
	} while (true);
	
	this->q = temp_q;
	
	this->b = (p-1) * (q-1);
	this->n = p * q;
	
	this->e = gen_e();
	this->d = gen_d();
}

string RSA::encrypt(string msg, int encrypted[]){
		
	int array_msg_plain[msg.length()];
	
	for (int i=0; i<msg.length(); i++)
		array_msg_plain[i] = (int)msg[i];
	
	int t_enc[msg.length()];
	
	for (int i=0; i<msg.length(); i++)
		t_enc[i] = MATH::modularExp(array_msg_plain[i], e, n);
		
	string str_enc = "";
		
	for (int i=0; i<msg.length(); i++)
	{
		encrypted[i] = t_enc[i];
		ostringstream temp;
    	temp << encrypted[i];
    	str_enc += temp.str();
    	if (i != msg.length() - 1) str_enc += "-";
    	
	}

	return str_enc;
}


string RSA::decrypt(int crypted[], int size){

	int decrypted_message[size];
	
	string decrypted = "";
	
	for (int i=0; i<size; i++)
	{
		decrypted_message[i] = MATH::modularExp(crypted[i], d, n);
		decrypted += (char)decrypted_message[i];
	}
	
	return decrypted;
}

void RSA::show_pars(){
	
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

Long RSA::gen_d(Long max) {
	
	for (int d=0; d<max; d++) if ((d * e) % b == 1) return d;
	return -1;
}

int RSA::gen_e(int max) {
	
	int e = 2;
	
	while (e < max) if (MATH::MCD(e, b) == 1) return e; else e++;
	
	return -1;
}

string RSA::get_pbc_key()
{
	ostringstream temp;
    temp << e;
    string es = temp.str();
	string b64 = b64encode(es);
	return b64;
}

string RSA::get_prv_key()
{	
	ostringstream temp;
    temp << d;
    string ds = temp.str();
	string b64 = b64encode(ds);
	return b64;
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


