typedef struct {
    long m;
    std::vector<long> mvec;
    std::vector<long> gvec;
    std::vector<long> ovec;
} ParamWrap;

void generateParameters(int argc, char *argv[]);
