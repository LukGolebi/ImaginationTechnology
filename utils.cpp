
void random_matrix(float *mat, int N) {
	struct timeval time{};
	gettimeofday(&time, nullptr);
	srand(time.tv_usec);
	for(auto i = 0; i < N; i++) {
		float tmp = (float)(rand() % 5) + 0.01 * (rand() % 5);
		tmp = (rand() % 2 == 0) ? tmp : tmp * (-1.);
		mat[i] = tmp;
	}
}

bool verify_matrix(float *matRef, float *matOut, int N, double precision = 0.01) {
	double diff = 0.0;
	for(auto i = 0; i < N; ++i) {
		diff = std::fabs(matRef[i] - matOut[i]);
		if(diff > precision) {
			cout << "Divergence precision\n";
			return false;
		}
	}
	return true;
}


inline int div_ceil(int numerator, int denominator) {
	std::div_t res = std::div(numerator, denominator);
	return res.rem ? (res.quot + 1) : res.quot;
}
