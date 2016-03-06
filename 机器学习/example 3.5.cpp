# include <bits/stdc++.h>
using namespace std;

const int N = 17;
const int DIM = 2;

float X[N][DIM];
int Y[N];

int read_data() {
	int id;
	for (int i = 0; i < N; i++){
		scanf("%d%f%f%d", &id, &X[i][0], &X[i][1], &Y[i]);
	}
	return N;
}


struct model {

	float Sw[DIM][2*DIM];
	float u0[DIM], u1[DIM];
	float w[DIM];
	float wT_u0, wT_u1;
	int fit () {
		_get_u0_u1();
		for (int i = 0; i < DIM; i ++) {
			for (int j = 0; j < DIM; j ++) {
				Sw[i][j] = 0.0;
			}
		}
		for (int i = 0; i < N; i ++) {
			float* _u;
			if (Y[i] == 0)_u = u0;
			else _u = u1;
			for (int x = 0; x < DIM; x ++) {
				for (int y = 0; y < DIM; y ++) {
					Sw[x][y] += (X[i][x]-_u[x]) * (X[i][y]-_u[y]);
				}
			}
		}

        for (int i = 0; i < DIM; i ++) {
			for (int j = 0; j < DIM; j ++) {
				printf("%f%c", Sw[i][j], " \n"[j == DIM-1]);
			}
		}

		_ni();

		for (int i = 0; i < DIM; i ++) {
			for (int j = 0; j < 2*DIM; j ++) {
				printf("%f%c", Sw[i][j], " \n"[j == 2*DIM-1]);
			}
		}

		for (int i = 0; i < DIM; i ++) {
			w[i] = 0.0;
			for (int j = 0; j < DIM; j ++) {
				w[i] += Sw[i][DIM+j]*(u0[j]-u1[j]);
			}

			printf("%.4f%c", w[i], " \n"[i == DIM-1]);
		}

		wT_u0 = wT_u1 = 0.0;
		for (int i = 0; i < DIM; i ++) {
			wT_u0 += w[i] * u0[i];
			wT_u1 += w[i] * u1[i];
		}
	}

	int predict(float* x) {
		int classes;
		float wT_x;
		wT_x = 0.0;
		for (int i = 0; i < DIM; i ++) {
			wT_x += w[i] * x[i];
		}
		if (wT_u0 > wT_u1) {
			if (wT_x > (wT_u0+wT_u1)/2) classes = 0;
			else classes = 1;
		}
		else {
			if (wT_x > (wT_u0+wT_u1)/2) classes = 1;
			else classes = 0;
		}
		printf("%.8f %d\n", wT_x, classes);
		return classes;
	}

	void _get_u0_u1() {
		int _cnt0, _cnt1;
		_cnt0 = _cnt1 = 0;
		for (int i = 0; i < DIM; i ++) {
			u0[i] = u1[i] = 0.0;
		}
		for (int i = 0; i < N; i ++) {
			if (Y[i] == 0) {
				_cnt0 ++;
				for (int j = 0; j < DIM; j++) {
					u0[j] += X[i][j];
				}
			}
			else if (Y[i] == 1) {
				_cnt1 ++;
				for (int j = 0; j < DIM; j++) {
					u1[j] += X[i][j];
				}
			}
		}
		for (int i = 0; i < DIM; i ++) {
			u0[i] /= _cnt0;
			u1[i] /= _cnt1;
		}
	}

	void _ni() {
		for (int i = 0; i < DIM; i ++) {
			for (int j = 0; j < DIM; j ++) {
				if (i == j)Sw[i][DIM+j] = 1.0;
				else Sw[i][DIM+j] = 0.0;
			}
		}
		const float eps = 1e-6;
		for (int i = 0; i < DIM; i ++) {
			//swap Sw[i] and Sw[j] in order to make Sw[i][i] > 0
			if (fabs(Sw[i][i]) < eps) {
				for (int j = i+1; j < DIM; j ++) {
					if (fabs(Sw[j][i]) > eps) {
						for (int x = 0; x < DIM*2; x ++){
							swap(Sw[i][x], Sw[j][x]);
						}
						break;
					}
				}
			}
			//change Sw[i][i] = 1.0
			float _t = Sw[i][i];
			for (int j = i; j < DIM*2; j ++) {
				Sw[i][j] /= _t;
			}

			//remove the next row 0.0
			for (int j = 0; j < DIM; j ++) {
			    if (j == i)continue;
				_t = (Sw[j][i]/Sw[i][i]);
				for (int x = i; x < DIM*2; x ++){
					Sw[j][x] -= Sw[i][x] * _t;
				}
			}
		}
	}
}LDA;
int main() {
 freopen("data3.0a.txt", "r", stdin);
	read_data();
	LDA.fit();
	for (int i = 0; i < N; i ++) {
		printf("", LDA.predict(X[i]));
	}
	return 0;
}
