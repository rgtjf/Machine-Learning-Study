#include <bits/stdc++.h>

using namespace std;
const float e = 2.732;
const int N = 17;
const int DIM = 2;
float X[N][DIM+1];
int Y[N];


int read_data() {
	int id;
	for (int i = 0; i < N; i++){
		scanf("%d%f%f%d", &id, &X[i][0], &X[i][1], &Y[i]);
		X[i][2] = 1.0;
		printf("%f %f\n", X[i][0], X[i][1]);
	}
	return N;
}

struct model {
	float beta[DIM+1];

	int fit() {
		for (int i = 0; i < DIM + 1; i++) {
			beta[i] = 0.0;
		}
		int iter = 80;
		while (iter --) {
			float beta_1[DIM+1];
			float beta_2;

			//get beta_1
			for (int i = 0; i < DIM + 1; i ++) {
				beta_1[i] = 0.0;
			}
			for (int i = 0; i < N; i++){
				for (int j = 0; j < DIM + 1; j ++) {
					beta_1[j] -= X[i][j]*Y[i] - p1(X[i]);
				}
			}

			//get beta_2
			beta_2 = 0.0;
			for (int i = 0; i < N; i++) {
				float t = 0.0;
				for (int j = 0; j < DIM + 1; j ++) {
					t += X[i][j] * X[i][j];
				}
				t = t * p1(X[i]) * (1 - p1(X[i]));
				beta_2 += t;
			}
            printf("beta2 = %f\n", beta_2);
			//get next_beta
			for (int i = 0; i < DIM + 1; i++) {
				beta[i] -= 1.0/beta_2*beta_1[i];
                printf("%d ", beta[i]);
			}printf("\n");
		}
	}

	float p1(float* x) {
		float z = 0.0;
		for (int i = 0; i < DIM + 1; i++) {
            z += beta[i]*x[i];
		}
		//printf("z = %f\n", z);
		return pow(e, z) / (1 + pow(e, z));
	}

	float predict(float* x) {
		float y = 0.0;
		for (int i = 0; i < DIM + 1; i ++) {
			y += beta[i] * x[i];
		}
		y = 1.0 / (1.0 + pow(e, y));
		return y;
	}
}LR;

int main() {
    freopen("data3.0a.txt", "r", stdin);
	read_data();
	LR.fit();
	for (int i = 0; i < DIM + 1; i ++) {
		printf("%.2f ", LR.beta[i]);
	}printf("\n");
	for (int i = 0; i < N; i ++) {
		printf("%.4f\n", LR.predict(X[i]));
	}
	return 0;
}
