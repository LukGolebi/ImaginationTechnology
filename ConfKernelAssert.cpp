// Type your code here, or load an example.


typedef unsigned int uint;

template<const uint NUM_THREADS, const uint BN, const uint BM, const uint BK, 
        const uint SN, const uint SM, const uint SNITER, const uint TM, const uint TN>
void KernelConfigAssert() {


    //settings paraeters to matmul kernel
    //NUM_THREADS = 128;
    //BN = 128;
    //BM = 128;
    //BK = 16;
    //SN = 64;
    //SM = 64;
    //SNITER = 4;
    //TN = 4;
    //TM = 8;
    //vect4
    //subgroupSize = 32
    //
    //as we can see in matmul kernel the dimension N is dense so that due vectorization it should be dim N % Vect == 0 

#if VECT2 
    constexpr uint SIMD = 2;
#elif VECT4
    constexpr uint SIMD = 4;
#elif VECT8
    constexpr uint SIMD = 8;    
#endif

    constexpr uint SUBGROUP_SIZE = 32;
    constexpr uint NUM_SUBGROUPS = NUM_THREADS / SUBGROUP_SIZE;

    constexpr uint SMITER = (SN * SM) / (SUBGROUP_SIZE * TM * TN * SNITER);

    static_assert(BN % SN == 0);  
    static_assert(BM % SM == 0);
    static_assert((BN / SN) * (BM / SM) == NUM_SUBGROUPS);

    static_assert((SM * SN) % (SUBGROUP_SIZE * TM * TN * SNITER) == 0);

    static_assert(SM % SMITER == 0);
    static_assert(SN % SNITER == 0);

    static_assert((NUM_THREADS * SIMD) % BK == 0);
    static_assert((NUM_THREADS * SIMD) % BN == 0);
    //we want to divide suobgroup into two equals part
    //first one is from matrix A, second one from matrix B
    static_assert(BN % ((SUBGROUP_SIZE / 2) * TN) == 0);
    static_assert(BM % ((SUBGROUP_SIZE / 2) * TM) == 0);
    static_assert((BM * BK) % (SIMD * NUM_THREADS) == 0);
    static_assert((BN * BK) % (SIMD * NUM_THREADS) == 0);

    runMatmulKernel(BM, BN, BK, SM, SN, SNITER, TM, TN, NUM_THREADS); 

}
