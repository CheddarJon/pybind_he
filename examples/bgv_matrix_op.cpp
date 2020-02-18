/* Copyright (C) 2019 IBM Corp.
 * This program is Licensed under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. See accompanying LICENSE file.
 */
#include <iostream>

#include <helib/helib.h>

using namespace helib;

int main(int argc, char *argv[]) {
  /*  Example of BGV scheme  */

  // Plaintext prime modulus
  unsigned long p = 4999;
  // Cyclotomic polynomial - defines phi(m)
  unsigned long m = 32109;
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
  const long rows = 48;
  const long cols = 24;
  // Chooses the columns in the matrix to acc.
  std::vector<long> selector(nslots);
  // Matrix repr, an array of vectors. Vectors has to have nslots elements.
  std::array<std::vector<long>, rows> db;
  // Used to populate vectors in encrypted matrix.
  Ctxt scratch(public_key);
  // Encrypted matrix consists of a vector with as many Ctxt's as there are rows.
  std::vector<Ctxt> edb(rows, scratch);

  // Choose columns.
  selector[0] = 1;
  selector[3] = 1;
  selector[9] = 1;

  // Initialize plaintext matrix.
  for (long i = 0; i < rows; i++) {
    db[i] = std::vector<long>(nslots);
    for (long j = 0; j < cols; j++) {
        db[i][j] = j + 1;
    }
  }

  Ctxt cselect(public_key);
  Ctxt res(public_key);

  // Print the plaintext
  std::cout << std::endl;
  std::cout << "Ptxt db as a matrix: (zeros are padding)" << std::endl;
  for (long i = 0; i < rows; i++)
    std::cout << vecToStr(db[i]) << std::endl;
  std::cout << std::endl;

  std::cout << "Ptxt selector: (zeros are padding)" << std::endl;
  std::cout << vecToStr(selector) << std::endl;

  // Encrypt the plaintext selector, using the public_key
  ea.encrypt(cselect, public_key, selector);

  // encrypt each row of db.
  for (long i = 0; i < rows; i++)
      ea.encrypt(edb[i], public_key, db[i]);

  // OPERATE
  setTimersOn();
  for (long i = 0; i < rows; i++) {
      edb[i] *= cselect;
  }

  for (long i = 0; i < rows; i++) {
      res += edb[i];
  }
  setTimersOff();
  // Decrypt the modified ciphertext and print.
  std::cout << std::endl;
  std::cout << "Ptxt db as a matrix: (after operations)" << std::endl;
  for (long i = 0; i < rows; i++) {
      ea.decrypt(edb[i], secret_key, db[i]);
      std::cout << vecToStr(db[i]) << std::endl;
  }
  ea.decrypt(res, secret_key, selector);
  std::cout << std::endl;
  std::cout << "Result of select and accumulate: " << vecToStr(selector) << std::endl;
  printAllTimers();

  return 0;
}
