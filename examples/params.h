/* Copyright (C) 2012-2017 IBM Corp.
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


// This version generates only m's that are products of distinct primes:
// no prime powers are allowed, and no "coalescing" of distinct prime
// factors is allowed.  This comports with the new analysis of
// bootstrapping.

namespace std {}
namespace NTL {}

using namespace std;
using namespace NTL;

#include <helib/NumbTh.h>
#include <helib/PAlgebra.h>
#include <helib/PtrVector.h>
#ifndef HELIB_HELIB_H
    #include <helib/helib.h>
#endif
#include <iomanip>
#include <cassert>


void generateParameters(
        long mret=500,
        long gens_flag=0,
        long info_flag=0,
        long p=2,
        long lo=1001,
        long hi=80000,
        long m_arg=0);

typedef struct {
    long m;
    long phim;
    std::vector<long> mvec;
    std::vector<long> gvec;
    std::vector<long> ovec;
} ParamWrap;

static std::vector<ParamWrap> params;

long getM(int index)
{
    if (index >= 0 && index < params.size()) {
        return params[index].m;
    }
    return -1;
}

void getMVEC(std::vector<long>& v, int index)
{
    std::vector<long> tmp = params[index].mvec;

    for (int i = 0; i < tmp.size(); i++) {
        v.push_back(tmp[i]);
    }
}

void getGVEC(std::vector<long>& v, int index)
{
    std::vector<long> tmp = params[index].gvec;

    for (int i = 0; i < tmp.size(); i++) {
        v.push_back(tmp[i]);
    }
}

void getOVEC(std::vector<long>& v, int index)
{
    std::vector<long> tmp = params[index].ovec;

    for (int i = 0; i < tmp.size(); i++) {
        v.push_back(tmp[i]);
    }
}

// A heuristic measure for how good a certain (depth,cost) is
long weighted_cost(long cost, long depth)
{
    return depth*(1L << 16) + cost;
}

// Reverse a vector
Vec<long> rev(const Vec<long>& v)
{
    long n = v.length();
    Vec<long> w;
    w.SetLength(n);
    for (long i = 0; i < n; i++)
        w[i] = v[n-1-i];
    return w;
}

// Truncate a vector
Vec<long> trunc(const Vec<long>& v)
{
    long n = v.length();
    Vec<long> w = v;
    if (n > 0 && w[n-1] == 1)
        w.SetLength(n-1);
    return w;
}

// Disregard values of m where the order of p mod m is grater than MaxOrd
const long MaxOrd = 100;

// Compute phi(p^e)=p^{e-1}*(p-1) (assuming that p is a prime)
long computePhi(const Pair<long,long>& x)
{
    return power_long(x.a, x.b-1) * (x.a-1);
}

bool comparePhi(const Pair<long,long>& x, const Pair<long,long>& y)
{
    return computePhi(x) < computePhi(y);
}

/* Usage: params_x.exe [ name=value ]...
 *  gens flag to output mvec, gens, and ords  [ default=0 ]
 *  info flag to output descriptive info about m  [ default=1 ]
 *  p    plaintext base  [ default=2 ]
 *  lo   low value for m range  [ default=1001 ]
 *  hi   high value for m range  [ default=80000 ]
 *  m    use only the specified m value
 *  mret maximum number of parametersets to be returned [ default=1 ]
 */
void generateParameters(
        long mret, long gens_flag, long info_flag, long p, long lo, long hi, long m_arg)
{
    if (lo % 2 == 0) lo++;

    if (m_arg) lo = hi = m_arg;


    for (long m = lo; m <= hi && mret > 0; m += 2) {

        if (GCD(p, m) != 1)
            continue;

        long d = helib::multOrd(p, m);

        if (d > MaxOrd)
            continue;

        long phim = helib::phi_N(m);

        Vec< Pair<long, long> > fac;
        helib::factorize(fac, m);

        long k = fac.length();

        if (k == 1)
            continue;

        bool sqrfree = true;
        for (long i = 0; i < k; i++) {
            if (fac[i].b > 1)
                sqrfree = false;
        }
        if (!sqrfree)
            continue;


        Vec<long> fac1;
        fac1.SetLength(k);

        for (long i = 0; i < k; i++)
            fac1[i] = power_long(fac[i].a, fac[i].b);

        Vec<long> phivec;
        phivec.SetLength(k);
        for (long i = 0; i < k; i++)
            phivec[i] = computePhi(fac[i]);

        long phisum = 0;
        for (long i = 0; i < k; i++)
            phisum += phivec[i];

        long gen_index = -1;
        bool good_gen = false;
        long first_gen = 0;

        long best_weighted_cost = NTL_MAX_LONG;
        long best_cost = NTL_MAX_LONG;
        long best_depth = NTL_MAX_LONG;

        for (long i = 0; i < k; i++) {
            long m1 = fac1[i];
            long phim1 = phivec[i];
            if (helib::multOrd(p, m1) != d)
                continue;

            helib::PAlgebra pal1(m1, p);
            if (pal1.numOfGens() > 1)
                continue;

            bool good = (pal1.numOfGens() == 0 ||
                        (pal1.numOfGens() == 1 && pal1.SameOrd(0)));

            long cost = phisum - phivec[i] + d-1;
            long depth = k-1;
            cost += (2-long(good))*(phim1/d-1);
            depth += (2-long(good));

            if (weighted_cost(cost, depth) < best_weighted_cost) {
                gen_index = i;
                good_gen = good;
                first_gen = pal1.ZmStarGen(0);
                best_weighted_cost = weighted_cost(cost, depth);
                best_cost = cost;
                best_depth = depth;
            }
        }

        long gen_index2 = -1;

        if (gen_index == -1)
            continue;

        Vec<long> fac2;

        fac2 = fac1;

        for (long i = gen_index-1; i >= 0; i--)
            swap(fac2[i], fac2[i+1]);

        if (gen_index2 != -1) {
            for (long i = gen_index2; i < k-1; i++)
                swap(fac2[i], fac2[i+1]);
            fac2[0] *= fac2[k-1];
            fac2.SetLength(k-1);
        }

        long k2 = fac2.length();

        Vec<long> genvec, ordvec;
        genvec.SetLength(k2);
        ordvec.SetLength(k2);

        if (first_gen == 0)
            first_gen = 1;
        genvec[0] = first_gen;
        ordvec[0] = helib::phi_N(fac2[0])/d;
        if (!good_gen)
            ordvec[0] = -ordvec[0];


        for (long i = 1; i < k2; i++) {
            vector<long> gens, ords;
            helib::findGenerators(gens, ords, fac2[i], 1);

            assert(gens.size() == 1);
            assert(ords.size() == 1);
            assert(ords[0] > 0);
            genvec[i] = gens[0];
            ordvec[i] = ords[0];
        }

        Vec<long> global_gen, crtvec;
        global_gen.SetLength(k2);
        crtvec.SetLength(k2);

        long all_1 = 0;

        for (long i = 0; i < k2; i++) {
            crtvec[i] = (m/fac2[i]) * InvMod((m/fac2[i]) % fac2[i], fac2[i]);
            all_1 += crtvec[i];
        }

        for (long i = 0; i < k2; i++) {
            global_gen[i] = (all_1 - crtvec[i] + crtvec[i]*genvec[i]) % m;
        }



        if (info_flag) {
            cout << setw(6) << phim << "  ";
            cout << setw(4) << d << "  ";
            cout << setw(6) << m << "  ";


            cout << "m=";
            for (long i = 0; i < k; i++) {
                if (i > 0)
                    cout << "*";
                if (i == gen_index)
                    cout << "(";
                if (i == gen_index2)
                    cout << "{";
                cout << fac[i].a;
                if (fac[i].b > 1)
                    cout << "^" << fac[i].b;
                if (i == gen_index)
                    cout << ")";
                if (i == gen_index2)
                    cout << "}";
            }
            cout << " ";

            if (!good_gen)
                cout << ":-( ";

            cout << "m/phim(m)="
                << double(long(100*double(m)/double(phim)))/100.0 << " ";

            cout << "C=" << best_cost << " ";
            cout << "D=" << best_depth << " ";
            cout << "E=" << NumTwos(conv<ZZ>(d)) << " ";
        }

        if (gens_flag) {
            cout << " mvec=" << "\"" << rev(fac2) << "\"" << " ";
            cout << "gens=" << "\"" << trunc(rev(global_gen)) << "\"" << " ";
            cout << "ords=" << "\"" << trunc(rev(ordvec)) << "\"" << " ";
        }


        if (gens_flag || info_flag) {
            cout << "\n";
            cout.flush();
        }

        // We do not want to save bad parameters.
        if (!good_gen)
            continue;

        if (mret-- > 0) {
            ParamWrap p;
            p.m = m;
            p.phim = phim;
            helib::vecCopy(p.mvec, rev(fac2));
            helib::vecCopy(p.gvec, trunc(rev(global_gen)));
            helib::vecCopy(p.ovec, trunc(rev(ordvec)));

            params.push_back(p);
        }
    }
}

/*
 * security = number of bits of security wanted.
 * L        = number of bits in the modulus chain.
 * c        = number of columns in the key-switching matrix.
 *
 * Returns index in the 'params' vector, that satisfies the security.
 */
int findParam(long security, long L, long c)
{
    /*
     * To get k-bit security we need N > log(Q0/sigma)(k + 110) / 7.2 i.e. roughly
     *      N > L(1 + 1/c)(k + 110) / 7.2
     *      k = 7.2N / L(1 + 1/c) - 110
     */
    generateParameters();
    cout << "DEBUG: size of params: " << params.size() << endl;

    for (int i = 0; i < params.size(); i++) {
        double cc = 1 + (1/c);
        double nom = 7.2 * params[i].phim;
        double denom = cc * L;
        long k = floor((nom / denom) - 110);

        if (k >= security)
            return i;
    }
    cout << "DEBUG: did not find any" << endl;
    return -1;
}
