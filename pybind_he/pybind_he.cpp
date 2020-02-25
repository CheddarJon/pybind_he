#include <iostream>
#include <pybind11/pybind11.h>
#include <helib/helib.h>

/*
	The pybind_he will be THE module that enables already identified HElib
	cXX-functions for optimization into your everyday python. 
	
	For installing the below functionality, run the setup and in python
	import <WRITE-MODULE-NAME>
*/

using namespace helib;

int john_helib() {
    
    /*  Example of BGV scheme  */
    
    // Plaintext prime modulus
    unsigned long p = 4999;
    // Cyclotomic polynomial - defines phi(m) m = 321090 => 96 slots, m = 32109 => 24 slots.
    unsigned long m = 321090;
    // Hensel lifting (default = 1)
    unsigned long r = 1;
    // Number of bits of the modulus chain
    unsigned long bits = 300;
    // Number of columns of Key-Switching matix (default = 2 or 3)
    unsigned long c = 2;

    std::cout << "Initialising context object..." << std::endl;
    // Intialise context
    Context context(m, p, r);
    // Modify the context, adding primes to the modulus chain
    std::cout  << "Building modulus chain..." << std::endl;
    buildModChain(context, bits, c);

    // Print the context
    context.zMStar.printout();
    std::cout << std::endl;

    // Print the security level
    std::cout << "Security: " << context.securityLevel() << std::endl;

    // Secret key management
    std::cout << "Creating secret key..." << std::endl;
    // Create a secret key associated with the context
    SecKey secret_key(context);
    // Generate the secret key
    secret_key.GenSecKey();
    std::cout << "Generating key-switching matrices..." << std::endl;
    // Compute key-switching matrices that we need
    addSome1DMatrices(secret_key);

    // Public key management
    // Set the secret key (upcast: SecKey is a subclass of PubKey)
    const PubKey& public_key = secret_key;

    // Get the EncryptedArray of the context
    const EncryptedArray& ea = *(context.ea);

    // Get the number of slot (phi(m))
    long nslots = ea.size();
    std::cout << "Number of slots: " << nslots << std::endl;

    /*---------------------------- END OF GENERIC BGV CODE ------------------------- */

    // Matrix dimensions rows x cols
    const long rows = 96;
    const long cols = 96;
    // Chooses the columns in the matrix to acc.
    std::vector<long> selector(nslots);
    // Matrix repr, an array of vectors. Vectors has to have nslots elements.
    std::array<std::vector<long>, rows> db;
    // Used to populate vectors in encrypted matrix.
    Ctxt scratch(public_key);
    // Encrypted matrix consists of a vector with as many Ctxt's as there are rows.
    std::vector<Ctxt> edb(rows, scratch);

    // Initialize plaintext matrix.
    for (long i = 0; i < rows; i++) {
        db[i] = std::vector<long>(nslots);
        for (long j = 0; j < cols; j++) {
            db[i][j] = j + 1;
        }

        // Choose columns
        if (i % 13 == 0)
        {
            selector[i] = 1;
        }
    }

    Ctxt cselect(public_key);
    Ctxt res(public_key);

    // Print the plaintext
    std::cout << std::endl;
    std::cout << "Ptxt db as a matrix: (zeros are padding)" << std::endl;
    for (long i = 0; i < rows; i++)
    {
        std::cout << vecToStr(db[i]) << std::endl;
    }
    
    std::cout << std::endl;
    
    std::cout << "Ptxt selector: (zeros are padding)" << std::endl;
    std::cout << vecToStr(selector) << std::endl;

    // Encrypt the plaintext selector, using the public_key
    ea.encrypt(cselect, public_key, selector);

    // encrypt each row of db.
    for (long i = 0; i < rows; i++)
    {
        ea.encrypt(edb[i], public_key, db[i]);
    }
    
    // OPERATE
    setTimersOn();
    for (long i = 0; i < rows; i++) 
    {
      edb[i] *= cselect;
    }

    for (long i = 0; i < rows; i++) 
    {
        res += edb[i];
    }
  
    setTimersOff();
    // Decrypt the modified ciphertext and print.
    std::cout << std::endl;
    std::cout << "Ptxt db as a matrix: (after operations)" << std::endl;
    for (long i = 0; i < rows; i++) 
    {
      ea.decrypt(edb[i], secret_key, db[i]);
      std::cout << vecToStr(db[i]) << std::endl;
    }
  
    ea.decrypt(res, secret_key, selector);
    std::cout << std::endl;
    std::cout << "Result of select and accumulate: " << vecToStr(selector) << std::endl;
    printAllTimers();

    return 0;
}

#ifndef BARE_BONE
PYBIND11_MODULE(pybind_he, m) 
{
    m.doc() = "IM ALIVE"; 

    m.def("john", &john_helib, "Example of BGV scheme");
}
#endif

#ifdef BARE_BONE
int main(int argc, char *argv[]) 
{
    john_helib();
}
#endif