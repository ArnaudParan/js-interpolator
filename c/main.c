//#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <emscripten/emscripten.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
void printarr(float *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; ++i) {
        printf(" %.2f", arr[i]);
    }
    printf(" ]\n");
}
*/

void interpolate(float *res, float *arr, int L, float *indices, float freq, float start, float stop) {
    int i = -1, j =-1;

    for (int l = 0; l < (stop - start + 1) / freq; ++l) {
        res[l] = NAN;
    }

    for (int l = 0; l < L; ++l) {
        if (i == -1 && !isnan(arr[l])) {
            i = l;
        }
        else if (!isnan(arr[l])) {
            j = l;

            for (int k = (int)((indices[i] - start) / freq) ; k <= (stop - start) / freq && start + k * freq <= indices[j]; ++k) {
                res[k] = ((arr[j] - arr[i]) / (indices[j] - indices[i])) * ((start + k * freq) - indices[i]) + arr[i];
            }
            i = l;
        }
    }
}

#ifdef __cplusplus
}
#endif

/*
int main() {
    float arr[] = { NAN, NAN, NAN, 0., NAN, NAN, NAN, 1., NAN, 0., NAN, 3. };
    float indices[] = { 0., 1., 3., 7., 8., 10., 13., 16., 20., 24., 28., 30. };
    float res[31];

    for (int i = 0; i < 31; ++i) {
        res[i] = NAN;
    }

    interpolate(arr, 12, indices, res, 1., 0., 30.);

    printarr(arr, 12);
    printarr(indices, 12);
    printarr(res, 31);

    return 0;
}
*/
