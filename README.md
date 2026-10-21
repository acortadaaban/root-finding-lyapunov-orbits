# Root Finding and Lyapunov Orbits in the Earth–Moon System

Course project for *Numerical Methods* (UAB, 2024–2025), written in C and developed as a pair project.

## What it does

1. **Root-finding library (`zeros.c` / `zeros.h`)** with two methods:
   - `biseccio`: bisection method, stopping when the interval half-width is below a tolerance.
   - `newton`: Newton's method, with tolerances on `|f(x)|` and on the step size, a maximum number of iterations and a return code.
2. **Application to the Restricted Three-Body Problem (RTBP):** finds a planar Lyapunov orbit around the L1 equilibrium point of the Earth–Moon system by solving `u_f(x) = 0`, where `u_f` is the x-component of the velocity at the first crossing of the x-axis.

## Programs

- `rtbp_lyap_csig c isgn x0 xf n`: generates pairs `(x, u_f(x))` on `[x0, xf]` to locate a sign change.
- `rtbp_lyap_ref c isgn xa xb tolbis tolfnwt maxitnwt ixrr`: combines bisection and Newton to find a zero of `u_f`.

Example used to locate the sign change:

```bash
./rtbp_lyap_csig 3.196255396314419 -1 -0.830 -0.829 100 > u.txt
```

## Requirements

The RTBP propagator (`rtbp.h` / `rtbp.c`, function `proptraj`) was provided by the course and is **not included** in this repository. To build the two programs, place those files next to the sources and compile, for example:

```bash
gcc -O2 -o rtbp_lyap_csig rtbp_lyap_csig.c rtbp.c -lm
gcc -O2 -o rtbp_lyap_ref  rtbp_lyap_ref.c zeros.c rtbp.c -lm
```

`zeros.c` has no external dependencies and can be used on its own.

## Main results

- **Bisection:** halving the tolerance adds exactly one iteration, matching the theoretical linear convergence.
- **Newton:** with a close initial guess it converges quadratically (6 iterations on `f(x) = eˣ − 2`); with a distant one (`x0 = 10`) it first advances slowly and needs more iterations (15 with `maxit = 20`).
- The initial condition found was propagated to the second crossing of the x-axis to plot the planar Lyapunov orbit.

## Acknowledgements

The algorithms follow the course handout by Josep Maria Mondelo.


## Report
The full write-up of the project, with the software manual, tests and results (in Catalan), is in `docs/Memoria_Zeros_i_Orbites_Lyapunov.pdf`.


## Authors

Albert Cortada, together with Oriol Antoja.


