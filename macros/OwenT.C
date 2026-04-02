#if 0
#include <stdio.h>
#include <gsl/gsl_sf_owens_t.h>

int main() {
    double h = 1.0;
    double a = 0.5;

    // Compute Owen's T function using GSL
    double result = gsl_sf_owens_t(h, a);

    printf("Owen's T(%f, %f) = %.12f\n", h, a, result);

    return 0;
}
#endif
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

struct params {
    double h;
};

double integrand(double x, void *p) {
    struct params *params = (struct params *)p;
    double h = params->h;
    return exp(-0.5 * h * h * (1 + x * x)) / (1 + x * x);
}

double owens_t(double h, double a) {
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
    gsl_function F;
    struct params p = {h};
    F.function = &integrand;
    F.params = &p;

    double result, error;
    gsl_integration_qags(&F, 0, a, 0, 1e-7, 1000, w, &result, &error);
    gsl_integration_workspace_free(w);

    return result / (2 * M_PI);
}

int main() {
    double h = 1.0;
    double a = 0.5;
    double val = owens_t(h, a);
    printf("Owen's T(%f, %f) = %.12f\n", h, a, val);
    return 0;
}
