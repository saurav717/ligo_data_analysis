#if !defined(PTAPSOHDR)
#define PTAPSOHDR

#include <gsl/gsl_vector.h>
#include <gsl/gsl_rng.h>

#if defined (__cplusplus)
extern "C" {
#endif

/*! Structure containing output results from \ref ptapso. */
typedef struct returnData {
	size_t totalIterations; /*!< total number of iterations */
    size_t totalFuncEvals; /*!< total number of fitness evaluations */
    gsl_vector *bestLocation; /*!< Final global best location */
    double bestFitVal; /*!< Best fitness values found */
    double computationTimeSecs;
} returnData_t;

typedef double (*fitness_function_ptr)(gsl_vector *, void *);

/* This called every N iterations with the current best results. */
typedef void (*current_result_function_ptr)(void* callback_params, returnData_t *);


/*!\file
\brief Header file for \ref ptapso.c
*/

/*! \brief PSO parameter structure 

Notes: 
   - The stopping criterion for PSO here is the number of iterations.
   - Particle inertia weight decays linearly over iterations as: max(A1 - (A2/A3)*k,A4)
where k is the iteration number.
*/
struct psoParamStruct {
	size_t popsize;      /*!< Number of particles */
	size_t maxSteps;     /*!< Number of iterations */
	double c1;           /*!< Acceleration const for pbest term */
	double c2;           /*!< Acceleration const for lbest term */
	double max_velocity; /*!< Maximum velocity along each dimension */
	double dcLaw_a;      /*!< Inertia decay law const A1 */
	double dcLaw_b;      /*!< Inertia decay law const A2 */
	double dcLaw_c;      /*!< Inertia decay law const A3 */
	double dcLaw_d;      /*!< Inertia decay law const A4 */
	/*!
	 Max number of iterations of 
	 local minimizer. Set to 0 to
	 switch off local minimization of
	 gbest.
	*/
	size_t locMinIter;
	/*! Initial step size of the GSL
	   local minimizer (in standardized
	   coordinates) along each coordinate.
	*/
	double locMinStpSz;
	gsl_rng *rngGen; /*!< Pointer to GSL random number generator */
	/*! Pointer to ascii file where to dump info. Set to NULL if not dumping. */
	FILE *debugDumpFile;
};



/*! Struct to contain particle information (instead of the plain matrix used in the Matlab code). */
struct particleInfo{
	gsl_vector *partCoord; /*!< Current coordinates */
	gsl_vector *partVel;  /*!<  Current velocity */
	gsl_vector *partPbest; /*!<  Coordinates of pbest */
	gsl_vector *partLocalBest; /*!<  Coordinates of neighborhood best */
	double partSnrPbest; /*!<  pbest fitness value */
	double partSnrCurr;  /*!<  Current fitness value */
	double partSnrLbest; /*!<  Best fitness in neighborhood */
	double partInertia;  /*!<  Current inertia weight */
	size_t partFitEvals; /*!<  Number of fitness function evaluations */
};

/*! Struct to allow fitness functions without a const gsl_vector * input
   argument to be passed to GSL local minimizer routines. Used internally
   by \ref ptapso.
*/
struct dummyFitFuncParam{
	//double (*trufuncPr)(gsl_vector *, void *);
	fitness_function_ptr trufuncPr;
	void *trufuncParam;
};

typedef struct current_result_callback_params_s {
	current_result_function_ptr callback;
	void* callback_params;
	int interval;
} current_result_callback_params_t;

double dummyfitfunc(const gsl_vector *, void *);

void lbestpso(size_t, /* Dimensionality of fitness function */
            fitness_function_ptr, /* Pointer to fitness function */
		    void *, /* Fitness function parameter structure */
			current_result_callback_params_t*, /* Pointer to callback function parameter structure */
			struct psoParamStruct *, /* PSO parameters */
			struct returnData * /* Structure containing PSO output */
		   );

void gbestpso(size_t nDim, /*!< Number of search dimensions */
            fitness_function_ptr fitfunc, /*!< Pointer to Fitness function */
			void *ffParams, /*!< Fitness function parameter structure */
			current_result_callback_params_t *, /* Pointer to callback function parameter structure */
            struct psoParamStruct *psoParams, /*!< PSO parameter structure */
			struct returnData *psoResults /*!< Output structure */);

void spso(size_t nDim, /*!< Number of search dimensions */
            fitness_function_ptr fitfunc, /*!< Pointer to Fitness function */
        	void *ffParams, /*!< Fitness function parameter structure */
            current_result_callback_params_t *, /* Pointer to callback function parameter structure */
            struct psoParamStruct *psoParams, /*!< PSO parameter structure */
            struct returnData *psoResults /*!< Output structure */);

void initPsoParticles(struct particleInfo *, size_t , gsl_rng *);

void particleinfo_alloc(struct particleInfo *, size_t);

void particleinfo_free(struct particleInfo *);

struct returnData * returnData_alloc(size_t );

void returnData_free(struct returnData *);

void particleinfo_fwrite(FILE *, struct particleInfo *);

void particleInfoDump(FILE *, struct particleInfo *, size_t );

#if defined (__cplusplus)
}
#endif

#endif
