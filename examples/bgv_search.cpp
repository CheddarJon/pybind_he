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

//#define TIME
#define SUCCESS

#ifndef TIME
    #define DEBUG
    #define ENTRIES 80
#endif

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
  // Factorisation of m required for bootstrapping. m = 4095
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

  // This is needed to get rid of unwanted ciphertext slots in the end.
  addSome1DMatrices(secret_key);

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

  const long bitSize = 16; // Number of bits that the comparison cares for.

#ifdef ENTRIES
  long entries = std::abs(ENTRIES) > ea.size() ? ea.size() : std::abs(ENTRIES);
#else
  long entries = ea.size();
#endif

  std::vector<long> search_pool(entries);

  for (auto& e : search_pool)
      e = NTL::RandomBits_long(bitSize);

#ifdef SUCCESS
  long search_val = search_pool[entries / 2];
#else
  long search_val = 0b0000000111111110;
#endif

#ifdef DEBUG
  std::cout << "Pre-encryption data:" << std::endl;
  std::cout << "search_pool = " << helib::vecToStr(search_pool) << std::endl;
  std::cout << "search_val = " << search_val << std::endl;
#endif

  // Use a scratch ciphertext to populate vectors.
  helib::Ctxt scratch(public_key);
  std::vector<helib::Ctxt> encrypted_pool(bitSize, scratch);
  std::vector<helib::Ctxt> encrypted_search(bitSize, scratch);
  // Encrypt the data in binary representation.
  for (long i = 0; i < bitSize; ++i) {
      std::vector<long> pool_vec(ea.size());
      std::vector<long> search_vec(ea.size());
      for (long j = 0; j < entries; j++)
          pool_vec[j] = (search_pool[j] >> i) & 1;
      for (auto& slot : search_vec)
        slot = (search_val >> i) & 1;

      ea.encrypt(encrypted_pool[i], public_key, pool_vec);
      ea.encrypt(encrypted_search[i], public_key, search_vec);
  }

  /* OPERATIONS BEGIN*/
#ifdef TIME
  helib::setTimersOn();
#endif
  helib::Ctxt mu(public_key);
  helib::Ctxt ni(public_key);
  helib::compareTwoNumbers(
          mu, // a > b ? 1 : 0
          ni, // a > b ? 0 : 1
          helib::CtPtrs_vectorCt(encrypted_pool),
          helib::CtPtrs_vectorCt(encrypted_search),
          &unpackSlotEncoding);

  /* The numbers we compare are equal if mu = ni = 0.
   * Therefore inverting mu and ni will yield the answer 1 if both are 0,
   * and if one or both of them are 1 beforehand then the answer will be 0.
   */
  inv_module(mu, 1);
  inv_module(ni, 1);

  mu *= ni;

#ifdef DEBUG
  std::vector<long> dbg;
  ea.decrypt(mu, secret_key, dbg);
  std::cout << "[DEBUG] mu before masking: " << helib::vecToStr(dbg) << std::endl;
#endif

  /* Unwanted slots get shifted out,
   * then the ciphertext get rotated to the original position.
   */
  long unwanted_slots = ea.size() - entries;
  if (unwanted_slots != 0) {
    ea.shift(mu, unwanted_slots);

    if (unwanted_slots < entries) {
      ea.shift(mu, -unwanted_slots);
      std::cout << "DEBUG: shift -unwanted_slots" << std::endl;
    }
    else {
      ea.rotate(mu, entries);
      std::cout << "DEBUG: rotate entries" << std::endl;
    }
  }
#ifdef DEBUG
  dbg.clear();
  ea.decrypt(mu, secret_key, dbg);
  std::cout << "[DEBUG] mu after masking: " << helib::vecToStr(dbg) << std::endl;
#endif
#ifdef TIME
  helib::setTimersOff();
#endif

  /* OPERATIONS END*/
  /* Dump the result. */
  std::vector<long> decrypted_result;
  std::vector<long> decrypted_a;
  std::vector<long> decrypted_b;
  ea.decrypt(mu, secret_key, decrypted_result);
  helib::decryptBinaryNums(decrypted_a, helib::CtPtrs_vectorCt(encrypted_pool), secret_key, ea);
  helib::decryptBinaryNums(decrypted_b, helib::CtPtrs_vectorCt(encrypted_search), secret_key, ea);

  unsigned int matches = 0;
  for (long i = 0; i < entries; i++) {
#ifdef DEBUG
      if (decrypted_result[i])
        std::cout << "Comparison: " << decrypted_a[i] << " = " << decrypted_b[i] << std::endl;
      else
        std::cout << "Comparison: " << decrypted_a[i] << " != " << decrypted_b[i] << std::endl;
#endif
      if (decrypted_result[i])
          matches++;
  }

  std::cout << "Found " << matches << " matching entries for "
      << search_val << " in search_pool" << std::endl;

#ifdef TIME
  helib::printAllTimers();
#endif

  return 0;
}

void
inv_module(std::vector<helib::Ctxt>& v, const long bitSize)
{
    FHE_TIMER_START;
    long all1 = gen1s(bitSize);

    for (auto& slot : v)
        slot.xorConstant(NTL::ZZX(all1));
    FHE_TIMER_STOP;
}

void
inv_module(helib::Ctxt& c, const long bitSize)
{
    FHE_TIMER_START;
    long all1 = gen1s(bitSize);

    c.xorConstant(NTL::ZZX(all1));
    FHE_TIMER_STOP;
}

long
gen1s(const long bitSize)
{
    FHE_TIMER_START;
    long all1 = 0;
    for (int i = 0; i < bitSize; i++) {
        all1 <<= 1;
        all1 |= 1;
    }
    FHE_TIMER_STOP;
    return all1;
}
