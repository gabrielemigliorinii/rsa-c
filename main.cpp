
#include <ctime>
#include "rsa.h"

using namespace std;

int main (void) {
	
	srand(time(NULL));
	
	RSA rsa(1);
	rsa.show_pars();
	string plain;

	cout << "\n\n >> INPUT PLAINTEXT: ";
	getline(cin, plain);
	
	string cipher = rsa.encrypt(plain);
	
	cout << "\n >> CIPHERTEXT: " << cipher;
	
	cout << "\n\n >> PLAINTEXT: " << rsa.decrypt(cipher);
	
	cout << "\n\n";
	
	return 0;
}


