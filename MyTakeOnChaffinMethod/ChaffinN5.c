//This code has improved the speed of the original Chaffin code from 4m to 0.25s for N = 5
//The commented code is in NewChaffinN6.c with some various other improvement
//Because it works well already I didn't introduced the improvements here

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int curstr[1000], max_perm, mperm_res[1000], N, tot_bl;
unsigned long int cur_perms[1000];

int factorial(int k);
bool *checker;
int *factval;
long int * upper;
int * power;
int * connected1;
int * connected2;
int * connected3;
int * connected4;
bool * arr;
unsigned long int tperm;
int stopit;
int dong[3];
int minim;
int tempwaste;

int getHashValue2(int * string) {
	long int val = 0;
	for (int i = 0; i < N; i++) {
		val = val * N + string[i];
	}
	val = upper[val];

	return val;
}

void max(int a, short int b, int pos) {
	if (b > a) {
		max_perm = b;
	}

}

int getSmallHash3(int * conn) {
	if (conn[0] < conn[1]) {
		if (conn[0] < conn[2]) {
			if (conn[1] < conn[2]) {
				return 0;
			}
			else {
				return 1;
			}

		}
		else {
			return 4;
		}
	}
	else {
		if (conn[1] < conn[2]) {
			if (conn[0] < conn[2]) {
				return 2;
			}
			else {
				return 3;
			}
		}
		else {
			return 5;
		}
	}
}

void builddong(int * conn) {
	if (conn[0] < conn[1]) {
		if (conn[0] < conn[2]) {
			dong[0] = conn[0];
			if (conn[1] < conn[2]) {
				dong[1] = conn[1];
				dong[2] = conn[2];
			}
			else {
				dong[1] = conn[2];
				dong[2] = conn[1];
			}

		}
		else {
			dong[0] = conn[2];
			dong[1] = conn[0];
			dong[2] = conn[1];
		}
	}
	else {
		if (conn[1] < conn[2]) {
			dong[0] = conn[1];
			if (conn[0] < conn[2]) {
				dong[1] = conn[0];
				dong[2] = conn[2];
			}
			else {
				dong[1] = conn[2];
				dong[2] = conn[0];
			}
		}
		else {
			dong[0] = conn[2];
			dong[1] = conn[1];
			dong[2] = conn[0];
		}
	}
}



//this is the starting fillStr call
void fillStr0(short int pos, short int pfound, int hashValue, int waste) {
	max(max_perm, pfound, pos);
	if (mperm_res[tot_bl - 1] + N > max_perm && max_perm < stopit) {
		int minihash = hashValue;
		checker[minihash] = 1;
		int pfound2 = pfound + 1;
		int pos1 = pos + 1;
		int pos2 = pos + 2;
		int pos3 = pos + 3;
		int pos4 = pos + 4;

		curstr[pos] = curstr[pos - N];
		{
			hashValue = connected1[minihash];
			if (checker[hashValue] == 0) {
				fillStr0(pos1, pfound2, hashValue, waste);
			}
		}
		curstr[pos] = curstr[pos1 - N];
		{
			tempwaste = waste - 1;
			if (tempwaste >= 0 && (mperm_res[tempwaste] + pfound > max_perm && mperm_res[tempwaste] + pfound >= minim)) {
				curstr[pos1] = curstr[pos - N];
				hashValue = connected2[minihash];
				if (checker[hashValue] == 0) {
					fillStr0(pos2, pfound2, hashValue, tempwaste);
				}
			}
		}
		curstr[pos] = curstr[pos2 - N];
		{
			tempwaste = waste - 2;
			if (tempwaste >= 0 && (mperm_res[tempwaste] + pfound > max_perm && mperm_res[tempwaste] + pfound >= minim)) {
				hashValue = connected3[minihash];
				if (checker[hashValue] == 0) {
					if (curstr[pos - N] < curstr[pos1 - N]) {
						curstr[pos1] = curstr[pos - N];
						curstr[pos2] = curstr[pos1 - N];
						fillStr0(pos3, pfound2, hashValue, tempwaste);
					}
					else {
						curstr[pos1] = curstr[pos1 - N];
						curstr[pos2] = curstr[pos - N];
						cur_perms[pfound] = hashValue;
						fillStr0(pos3, pfound2, hashValue, tempwaste);
					}
				}
				hashValue++;
				if (checker[hashValue] == 0) {
					if (curstr[pos - N] > curstr[pos1 - N]) {
						curstr[pos1] = curstr[pos - N];
						curstr[pos2] = curstr[pos1 - N];
						fillStr0(pos3, pfound2, hashValue, tempwaste);
					}
					else {
						curstr[pos1] = curstr[pos1 - N];
						curstr[pos2] = curstr[pos - N];
						fillStr0(pos3, pfound2, hashValue, tempwaste);
					}
				}
			}
		}
		curstr[pos] = curstr[pos3 - N];
		{
			tempwaste = waste - 3;
			if (tempwaste >= 0 && (mperm_res[tempwaste] + pfound  > max_perm && mperm_res[tempwaste] + pfound >= minim)) {
				hashValue = connected4[minihash];
				builddong(&curstr[pos - N]);
				if (checker[hashValue] == 0) {
					curstr[pos1] = dong[0];
					curstr[pos2] = dong[1];
					curstr[pos3] = dong[2];
					if (checker[hashValue] == 0) {
						fillStr0(pos4, pfound2, hashValue, tempwaste);
					}
				}
				hashValue++;
				if (checker[hashValue] == 0) {
					curstr[pos1] = dong[0];
					curstr[pos2] = dong[2];
					curstr[pos3] = dong[1];
					if (checker[hashValue] == 0) {
						fillStr0(pos4, pfound2, hashValue, tempwaste);
					}
				}
				hashValue++;
				if (checker[hashValue] == 0) {
					curstr[pos1] = dong[1];
					curstr[pos2] = dong[0];
					curstr[pos3] = dong[2];
					if (checker[hashValue] == 0) {
						fillStr0(pos4, pfound2, hashValue, tempwaste);
					}
				}
				hashValue++;
				if (checker[hashValue] == 0) {
					curstr[pos1] = dong[1];
					curstr[pos2] = dong[2];
					curstr[pos3] = dong[0];
					if (checker[hashValue] == 0) {
						fillStr0(pos4, pfound2, hashValue, tempwaste);
					}
				}
				hashValue++;
				if (checker[hashValue] == 0) {
					curstr[pos1] = dong[2];
					curstr[pos2] = dong[0];
					curstr[pos3] = dong[1];
					if (checker[hashValue] == 0) {
						fillStr0(pos4, pfound2, hashValue, tempwaste);
					}
				}
				hashValue++;
				if (checker[hashValue] == 0) {
					curstr[pos1] = dong[2];
					curstr[pos2] = dong[1];
					curstr[pos3] = dong[0];
					if (checker[hashValue] == 0) {
						fillStr0(pos4, pfound2, hashValue, tempwaste);
					}
				}

			}
		}

		checker[minihash] = 0;
	}

}

int main()
{
	unsigned short int j0;

	printf("This tool will try to find the length of the shortest superpermutation on n symbols. Please enter n: ");
	scanf("%d", &N);

	mperm_res[0] = N;

	///MY PART OF THE CODE
	//contains factorial values from 0! to N!
	factval = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 0; i <= N; i++) {
		factval[i] = factorial(i);
	}

	stopit = factval[N];

	upper = (long int*)calloc(pow(N, N + 2), sizeof(long int)); //a bit excessive, to improve
	power = (int*)malloc(sizeof(int) * (N * 2 + 1));
	connected1 = (int*)malloc(sizeof(int) * factorial(N) +1);
	connected2 = (int*)malloc(sizeof(int) * factorial(N) +1);
	connected3 = (int*)malloc(sizeof(int) * factorial(N)+ 1);
	connected4 = (int*)malloc(sizeof(int) * factorial(N) +1);

	for (int i = 0; i < factorial(N); i++) {
		connected1[i] = 0;
		connected2[i] = 0;
		connected3[i] = 0;
		connected4[i] = 0;
	}

	//contains power values of 6 from 0 to N*2
	for (int i = 0; i <= N * 2; i++) {
		power[i] = pow(N, i);
	}

	arr = (bool*)malloc(N * sizeof(bool));
	for (int s = 0; s < N; s++)
		arr[s] = 0;

	int a;
	int step;
	int k;

	//connecting first order connections to hash values
	for (int i = 0; i < factorial(N); i++) {
		long int upperValue = 0;
		for (int s = 0; s < N; s++)
			arr[s] = 0;

		a = i / factorial(N - 1);
		arr[a] = 1;
		upperValue = a;

		for (int j = 1; j < N; j++) {
			a = i % factorial(N - j);
			step = a / factorial(N - (j + 1));

			k = 0;
			while (arr[k] == 1)
				k++;
			while (step != 0) {
				if (arr[k] != 1)
					step--;
				k++;
				while (arr[k] == 1)
					k++;
			}
			arr[k] = 1;
			upperValue = upperValue * N + k;

		}
		upper[upperValue] = i;

	}

	//generationg connected1 and connected2
	int * conn = (int*)malloc(sizeof(int) * (N + N));
	for (int i = 0; i < factorial(N); i++) {
		for (int s = 0; s < N; s++)
			arr[s] = 0;

		a = i / factorial(N - 1);
		arr[a] = 1;
		conn[0] = a;
		conn[N] = a;
		for (int j = 1; j < N; j++) {
			a = i % factorial(N - j);
			step = a / factorial(N - (j + 1));

			k = 0;
			while (arr[k] == 1)
				k++;
			while (step != 0) {
				if (arr[k] != 1)
					step--;
				k++;
				while (arr[k] == 1)
					k++;
			}
			arr[k] = 1;
			conn[j] = k;
		}
		connected1[i] = getHashValue2(&conn[1]);
		conn[N] = conn[1];
		conn[N + 1] = conn[0];
		connected2[i] = getHashValue2(&conn[2]);
		conn[N] = conn[2];
		if (conn[0] < conn[1]) {
			conn[N + 1] = conn[0];
			conn[N + 2] = conn[1];
		}
		else {
			conn[N + 1] = conn[1];
			conn[N + 2] = conn[0];
		}
		connected3[i] = getHashValue2(&conn[3]);

		conn[N] = conn[3];
		if (conn[0] < conn[1]) {
			if (conn[0] < conn[2]) {
				conn[N + 1] = conn[0];
				if (conn[1] < conn[2]) {
					conn[N + 2] = conn[1];
					conn[N + 3] = conn[2];
				}
				else {
					conn[N + 2] = conn[2];
					conn[N + 3] = conn[1];
				}

			}
			else {
				conn[N + 1] = conn[2];
				conn[N + 2] = conn[0];
				conn[N + 3] = conn[1];
			}
		}
		else {
			if (conn[1] < conn[2]) {
				conn[N + 1] = conn[1];
				if (conn[0] < conn[2]) {
					conn[N + 2] = conn[0];
					conn[N + 3] = conn[2];
				}
				else {
					conn[N + 2] = conn[2];
					conn[N + 3] = conn[0];
				}
			}
			else {
				conn[N + 1] = conn[2];
				conn[N + 2] = conn[1];
				conn[N + 3] = conn[0];
			}
		}
		connected4[i] = getHashValue2(&conn[4]);
	}

	checker = (bool*)malloc(sizeof(bool) * factval[N]); 
	///END OF GENERATING CONNECTIONS ETC


	printf("Thanks for choosing N: %d, let's start!\n", N);

	for (tot_bl = 1; tot_bl <= 50; tot_bl++) {
		max_perm = 1;

		for (int i = 0; i < factval[N]; i++) ///THE NEW CLEARPERMS
			checker[i] = 0;

		for (j0 = 0; j0 < N; j0++) {
			curstr[j0] = j0;
		}
		checker[0] = 1;
		minim = mperm_res[tot_bl - 1] + 2;

		fillStr0(N, 1, 0, tot_bl);
		mperm_res[tot_bl] = max_perm;

		printf("%d wasted characters: at most %d permutations, N is at %d\n", tot_bl, max_perm, N);

		if (max_perm >= factval[N]) {
			printf("\n-----\nDONE!\n-----\n\nMinimal superpermutations on %d symbols have %d wasted characters and a length of %d.\n", N, tot_bl, max_perm);
			break;
		}
	}

	getchar();
	return 0;
}

// this function computes the factorial of a number
int factorial(int val) {
	int res = 1;
	for (int i = 1; i <= val; i++) {
		res = res * i;
	}
	return res;
}
