
#include <ctime>
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
	
	string cipher_string = rsa.encrypt(plain, cipher_array, false);
	
	cout << " >> CIPHERTEXT: " << cipher_string << "\n\n";
	
	cout << " >> PLAINTEXT: " << rsa.decrypt(cipher_array, *(&cipher_array+1)-cipher_array, false);
	
	cout << "\n\n";
	
	return 0;
}

