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
#include <helib/binaryArith.h>
#include <helib/binaryCompare.h>
#include <helib/intraSlot.h>

void inv_module(std::vector<helib::Ctxt>& v, const long bitSize);
void inv_module(helib::Ctxt& c, const long bitSize);
long gen1s(const long bitSize);

int main(int argc, char* argv[])
{
  /*  Example of binary arithmetic using the BGV scheme  */

  // First set up parameters.
  //
  // NOTE: The parameters used in this example code are for demonstration only.
  // They were chosen to provide the best performance of execution while
  // providing the context to demonstrate how to use the "Binary Arithmetic
  // APIs". The parameters do not provide the security level that might be
  // required by real use/application scenarios.

  // Plaintext prime modulus.
  long p = 2;
  // Cyclotomic polynomial - defines phi(m).
  long m = 4095;
  // Hensel lifting (default = 1).
  long r = 1;
  // Number of bits of the modulus chain.
  long bits = 500;
  // Number of columns of Key-Switching matrix (typically 2 or 3).
  long c = 2;
  // Factorisation of m required for bootstrapping.
  std::vector<long> mvec = {7, 5, 9, 13};
  // Generating set of Zm* group.
  std::vector<long> gens = {2341, 3277, 911};
  // Orders of the previous generators.
  std::vector<long> ords = {6, 4, 6};

  std::cout << "Initialising context object..." << std::endl;
  // Intialise the context.
  helib::Context context(m, p, r, gens, ords);

  // Modify the context, adding primes to the modulus chain.
  std::cout << "Building modulus chain..." << std::endl;
  buildModChain(context, bits, c);

  // Make bootstrappable.
  context.makeBootstrappable(
      helib::convert<NTL::Vec<long>, std::vector<long>>(mvec));

  // Print the context.
  context.zMStar.printout();
  std::cout << std::endl;

  // Print the security level.
  std::cout << "Security: " << context.securityLevel() << std::endl;

  // Secret key management.
  std::cout << "Creating secret key..." << std::endl;
  // Create a secret key associated with the context.
  helib::SecKey secret_key(context);
  // Generate the secret key.
  secret_key.GenSecKey();

  // Generate bootstrapping data.
  secret_key.genRecryptData();

  // Public key management.
  // Set the secret key (upcast: SecKey is a subclass of PubKey).
  const helib::PubKey& public_key = secret_key;

  // Get the EncryptedArray of the context.
  const helib::EncryptedArray& ea = *(context.ea);

  // Build the unpack slot encoding.
  std::vector<helib::zzX> unpackSlotEncoding;
  buildUnpackSlotEncoding(unpackSlotEncoding, ea);

  // Get the number of slot (phi(m)).
  long nslots = ea.size();
  std::cout << "Number of slots: " << nslots << std::endl;

  /*------------------------- MODIFICAITONS TO EXAMPLE STARTS HERE --------------------- */

  // Generate three random binary numbers a, b, c.
  // Encrypt them under BGV.
  // Calculate a * b + c with HElib's binary arithmetic functions, then decrypt
  // the result.
  // Next, calculate a + b + c with HElib's binary arithmetic functions, then
  // decrypt the result.
  // Finally, calculate popcnt(a) with HElib's binary arithmetic functions, then
  // decrypt the result.  Note that popcnt, also known as hamming weight or bit
  // summation, returns the count of non-zero bits.

  // Note: several numbers can be encoded across the slots of each ciphertext
  // which would result in several parallel slot-wise operations.
  // For simplicity we place the same data into each slot of each ciphertext,
  // printing out only the back of each vector.
  const long bitSize = 16;
  long outSize = 2 * bitSize;
  long a_data = 0b0000000111111111;
  long b_data = 0b0000000111111111;
  long c_data = 0b1111111111111111;
  long d_data = 0b0000000000000001;

  std::cout << "Pre-encryption data:" << std::endl;
  std::cout << "a = " << a_data << std::endl;
  std::cout << "b = " << b_data << std::endl;
  std::cout << "c = " << c_data << std::endl;
  std::cout << "d = " << d_data << std::endl;

  // Use a scratch ciphertext to populate vectors.
  helib::Ctxt scratch(public_key);
  std::vector<helib::Ctxt> encrypted_a(bitSize, scratch);
  std::vector<helib::Ctxt> encrypted_b(bitSize, scratch);
  std::vector<helib::Ctxt> encrypted_c(bitSize, scratch);
  std::vector<helib::Ctxt> encrypted_d(bitSize, scratch);
  // Encrypt the data in binary representation.
  for (long i = 0; i < bitSize; ++i) {
    std::vector<long> a_vec(ea.size());
    std::vector<long> b_vec(ea.size());
    std::vector<long> c_vec(ea.size());
    std::vector<long> d_vec(ea.size());
    // Extract the i'th bit of a,b,c.
    for (auto& slot : a_vec)
      slot = (a_data >> i) & 1;
    for (auto& slot : b_vec)
      slot = (b_data >> i) & 1;
    for (auto& slot : c_vec)
      slot = (c_data >> i) & 1;
    for (auto& slot : d_vec)
      slot = (d_data >> i) & 1;
    ea.encrypt(encrypted_a[i], public_key, a_vec);
    ea.encrypt(encrypted_b[i], public_key, b_vec);
    ea.encrypt(encrypted_c[i], public_key, c_vec);
    ea.encrypt(encrypted_d[i], public_key, d_vec);
  }

  // Although in general binary numbers are represented here as
  // std::vector<helib::Ctxt> the binaryArith APIs for HElib use the PtrVector
  // wrappers instead, e.g. helib::CtPtrs_vectorCt. These are nothing more than
  // thin wrapper classes to standardise access to different vector types, such
  // as NTL::Vec and std::vector. They do not take ownership of the underlying
  // object but merely provide access to it.
  //
  // helib::CtPtrMat_vectorCt is a wrapper for
  // std::vector<std::vector<helib::Ctxt>>, used for representing a list of
  // encrypted binary numbers.

  helib::Ctxt mu(public_key);
  helib::Ctxt ni(public_key);
  helib::compareTwoNumbers(
          mu, // a > b ? 1 : 0
          ni, // a > b ? 0 : 1
          helib::CtPtrs_vectorCt(encrypted_a),
          helib::CtPtrs_vectorCt(encrypted_b),
          &unpackSlotEncoding);

  /* The numbers we compare are equal if mu = ni = 0.
   * Therefore inverting mu and ni will yield the answer 1 if both are 0,
   * and if one or both of them are 1 beforehand then the answer will be 0. */
  inv_module(mu, 1);
  inv_module(ni, 1);
  mu *= ni;

  std::vector<long> decrypted_result;
  std::vector<long> decrypted_a;
  std::vector<long> decrypted_b;
  ea.decrypt(mu, secret_key, decrypted_result);
  helib::decryptBinaryNums(decrypted_a, helib::CtPtrs_vectorCt(encrypted_a), secret_key, ea);
  helib::decryptBinaryNums(decrypted_b, helib::CtPtrs_vectorCt(encrypted_b), secret_key, ea);

  if (decrypted_result.back())
      std::cout << "Comparison: " << decrypted_a.back() << " = " << decrypted_b.back() << std::endl;
  else
      std::cout << "Comparison: " << decrypted_a.back() << " != " << decrypted_b.back() << std::endl;

  return 0;
}

void
inv_module(std::vector<helib::Ctxt>& v, const long bitSize)
{
    long all1 = gen1s(bitSize);

    for (auto& slot : v)
        slot.xorConstant(NTL::ZZX(all1));
}

void
inv_module(helib::Ctxt& c, const long bitSize)
{
    long all1 = gen1s(bitSize);

    c.xorConstant(NTL::ZZX(all1));
}

long
gen1s(const long bitSize)
{
    long all1 = 0;
    for (int i = 0; i < bitSize; i++) {
        all1 <<= 1;
        all1 |= 1;
    }
    return all1;
}
