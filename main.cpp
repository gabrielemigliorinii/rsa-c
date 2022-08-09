
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "rsa.h"

using namespace std;

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

