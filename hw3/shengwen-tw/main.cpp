#include <iostream>
#include <sys/time.h>
#include <mkl.h>
#include <mkl_lapacke.h>
#include "matrix.h"

#define N 1024
#define BLOCK_SIZE 64

using namespace std;

double time(void)
{
        static int sec = -1;
        struct timeval tv;
        gettimeofday(&tv, NULL);

        if (sec < 0) sec = tv.tv_sec;
        return (tv.tv_sec - sec) + 1.0e-6 * tv.tv_usec;
}

void multiply_naive(Matrix &mat1, Matrix &mat2, Matrix &mat_result)
{
	for(int r = 0; r < mat1.row(); r++) {
		for(int c = 0; c < mat2.column(); c++) {
			for(int i = 0; i < mat1.column(); i++) {
				mat_result(r, c) += mat1(r, i) * mat2(i, c);
			}
		}
	}
}

void multiply_tile(Matrix &mat1, Matrix &mat2, Matrix &mat_result)
{
	for(int r = 0; r < mat1.row(); r+=BLOCK_SIZE) {
		for(int i = 0; i < mat1.column(); i++) {
			for(int c = 0; c < mat2.column(); c+=BLOCK_SIZE) {
				for(int br = r; br < r + BLOCK_SIZE; br++) {
					for(int bc = c; bc < c + BLOCK_SIZE; bc++) {
						mat_result(br, bc) += mat1(br, i) * mat2(i, bc);
					}
				}
			}
		}
	}
}

void multiply_mkl(Matrix &mat1, Matrix &mat2, Matrix &mat_result)
{
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat_result.row(),
                    mat_result.column(), mat2.row(), 1, mat1.raw_data(), mat2.row(),
                    mat2.raw_data(), mat_result.column(), 0, mat_result.raw_data(),
                    mat_result.column());	
}

float random_float(float max)
{
	return random() / ((float)RAND_MAX / 1000);
}

void random_matrix(Matrix &mat, float max_val)
{
	for(int r = 0; r < mat.row(); r++) {
		for(int c = 0; c < mat.column(); c++) {
			mat(r, c) = random_float(max_val);
		}
	}
}

void print_matrix(const char *prompt, Matrix &mat)
{
	cout << prompt << " (" << mat.row()  << "x" << mat.column() << "):\n";
	for(int r = 0; r < mat.row(); r++) {
		for(int c = 0; c < mat.column(); c++) {
			cout << mat.at(r, c) << "  ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int main(void)
{
	Matrix mat1(N, N);
	random_matrix(mat1, 1000);

	Matrix mat2(N, N);
	random_matrix(mat2, 1000);

	Matrix m_naive(N, N);
	Matrix m_tile(N, N);
	Matrix m_mkl(N, N);

	double start_time, end_time;

	start_time = time();
	multiply_naive(mat1, mat2, m_naive);
	end_time = time();
	cout << "naive " << end_time - start_time << " seconds\n";

	start_time = time();
	multiply_tile(mat1, mat2, m_tile);
	end_time = time();
	cout << "tiled " << end_time - start_time << " seconds\n";

	start_time = time();
	multiply_mkl(mat1, mat2, m_mkl);
	end_time = time();
	cout << "mkl " << end_time - start_time << " seconds\n";

#if 0
	print_matrix("mat1", mat1);
	print_matrix("mat2", mat2);

	print_matrix("m_naive", m_naive);
	print_matrix("m_tile", m_tile);
	print_matrix("m_mkl", m_mkl);
#endif

	return 0;
}
