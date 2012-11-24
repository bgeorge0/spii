#ifndef SPII_SOLVER_H
#define SPII_SOLVER_H

#include <iostream>
#include <string>

#include <spii/function.h>

struct SolverResults
{
	SolverResults();

	enum {GRADIENT_TOLERANCE,
	      FUNCTION_TOLERANCE,
	      ARGUMENT_TOLERANCE,
	      NO_CONVERGENCE,
	      NAN,
	      INFINITY,
	      ERROR,
	      NA} exit_condition;

	double startup_time;
	double function_evaluation_time;
	double stopping_criteria_time;
	double matrix_factorization_time;
	double linear_solver_time;
	double backtracking_time;
	double log_time;
	double total_time;
};

std::ostream& operator<<(std::ostream& out, const SolverResults& results);

void cerr_log_function(const std::string& log_message);

class Solver
{
public:
	Solver();
	void Solve(const Function& function,
	           SolverResults* results) const;

	// Mode of operation. How the Hessian is stored.
	// Default: AUTO.
	enum {DENSE, SPARSE, AUTO} sparsity_mode;

	// Function called each iteration with a log message.
	void (*log_function)(const std::string& log_message);

	// Maximum number of iterations. Default: 100.
	int maximum_iterations;

	// Gradient tolerance. The solver terminates if
	// ||g|| / ||g0|| < tol, where ||.|| is the maximum
	// norm. Default: 1e-12.
	double gradient_tolerance;

	// Function improvement tolerance. The solver terminates
	// if |df| / (|f| + tol) < tol. Default: 1e-12.
	double function_improvement_tolerance;

	// Argument improvement tolerance. The solver terminates
	// if ||dx|| / (||x|| + tol) < tol. Default: 1e-12.
	double argument_improvement_tolerance;
};

#endif