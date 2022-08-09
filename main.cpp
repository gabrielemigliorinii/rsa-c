
#include <ctime>
#include "rsa.h"

using namespace std;

int main (void) {
	
	srand(time(NULL));
	
	RSA rsa(1);
	string plain;
	
	cout << "\n\n >> INPUT PLAINTEXT: ";
	getline(cin, plain);
	
	string cipher_str = rsa.encrypt(plain, 0);
	
	cout << "\n >> CIPHERTEXT: " << cipher_str;
	
	cout << "\n\n >> PLAINTEXT: " << rsa.decrypt(cipher_str, 0);
	
	cout << "\n\n";
	
	return 0;
}

