typedef struct {
    long m;
    std::vector<long> mvec;
    std::vector<long> gvec;
    std::vector<long> ovec;
} ParamWrap;

void generateParameters(
        long gens_flag=0,
        long info_flag=0,
        long p=2,
        long lo=1001,
        long hi=80000,
        long m_arg=0,
        long mret=1);
