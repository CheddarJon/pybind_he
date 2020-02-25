class ParamWrap {
public:
    long m;
    std::vector<long> mvec;
    std::vector<long> gvec;
    std::vector<long> ovec;
};

void generateParameters(std::vector<ParamWrap>& retv, int argc, char *argv[]);
