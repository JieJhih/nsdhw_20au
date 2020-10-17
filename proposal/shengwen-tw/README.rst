#################################################################
libqpsolver: a library for solving quadratic programming problems
#################################################################

Basic information
#################

* A numerical optimizer for solving quadratic cost functions with or without equality / inequality constraints

* The optimizer will be implemented in C. (Not C++ since author will like to integrate it into embedded devices later.)

* The future goal of this project is to integrate it in to embedded devices, which requires more improvments to
  speed up the code. I expect myself to finish the first version this semester and able to run it on normal PC.

GitHub: https://github.com/shengwen-tw/libqpsolver

Problem to solve
################

What is Quadratic Programming?
------------------------------

.. image:: qp_formula.PNG

We call the variable x **optimization variables** to be minimized,

the first term **objective function** or **cost function**,

the second term **equality constraints**,

and the third term **inequality constraints**.

Why do we need Quadratic Programming?
-------------------------------------

Quadratic Programming shows up frequently in robotics field like control or trajectory planning.

* For example, if we want to map force and torque (6 degrees total) into motors numbers greater than 6,
then we have infinite combinations for choosing motor thrust.

* One of the solution is to choose the combination which has the lowest energy (in the sense of quadratic form)

There are two fantasic examples to illustate this problem:

.. image:: dragon.PNG

link: https://www.youtube.com/watch?v=uje6iUBbkwM

.. image:: omnicopter.PNG

link: https://www.youtube.com/watch?v=sIi80LMLJSY&t=27s


Perspective users
#################

I will expect the user may have the following backgrounds:

1. Robotics

2. Control

Usually the problem set up will like: 

We want robots to do something, but there are multiple choices.
We then construct a quadratic cost function to analogize the energy cost and choose the least one strategy.

System architecture
###################

.. image:: architecture.PNG

API description
###############

we use **qp_t** datatype to store all informations that the solver need to solve the problem

To set up the optimization variables, we call:

``void qp_solve_set_optimization_variable(qp_t *qp, vector_t *x);``

To set up the objective function, we call:

``void qp_solve_set_cost_function(qp_t *qp, matrix_t *P, vector_t *q, vector_t *r);``

To set up the equality constraints, we call:

``void qp_solve_set_equality_constraints(qp_t *qp, matrix_t *A, matrix_t *b);``

To set up the upper bound of the inequality constraints, we call:

``void qp_solve_set_upper_bound_inequality_constraints(qp_t *qp, vector_t *ub);``

To set up the lower bound of the inequality constraints, we call:

``void qp_solve_set_lower_bound_inequality_constraints(qp_t *qp, vector_t *lb);``

To start solving the quadratic programming problem, we call:

``bool qp_solve_start(qp_t);``

Engineering infrastructure
##########################

Algorithms I need:

1. Linear algebra functions (Intel MKL): matrix arithmatics, linear system solver, matrix decompositions, etc.

2. Gradient descent algorithm (the easest way to do minimization)

3. Newton's method of optimization (an improved version of gradient descent algorithm)

4. Exact line search algorithm (for deciding the step length of gradient descent (slower but precise))

5. Backtrack line search algorithm (for deciding the step length of gradient descent (faster but less preciese))

6. Barrier method (limiting the searching space of optimization to obay the inequality constraints)

Schedule
########

W6 (10/19) test program for Intel MKL

W7 (10/26) implement qp solver with no constraints

W8 (11/2) implement qp solver with equality constraints only

W9 (11/9) continue of last week

W10 (11/16) implement gradient descent method

W11 (11/23) implement newton's of optimization

W12 (11/30) continue of last week

W13 (12/7) implement log barrier function

W14 (12/14) implement log barrier function

W15 (12/21) implement qp solver with inequilty constraints

W16 (12/28) final presentation
