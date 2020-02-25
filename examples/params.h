typedef struct {
    long m;
    long phim;
    std::vector<long> mvec;
    std::vector<long> gvec;
    std::vector<long> ovec;
} ParamWrap;

void generateParameters(
        long mret=500,
        long gens_flag=0,
        long info_flag=0,
        long p=2,
        long lo=1001,
        long hi=80000,
        long m_arg=0);

/*
 * security = number of bits of security wanted.
 * L        = number of bits in the modulus chain.
 * c        = number of columns in the key-switching matrix.
 *
 * Returns index in the 'params' vector, that satisfies the security.
 */
int findParam(long security, long L, long c);
