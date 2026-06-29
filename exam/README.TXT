The Hessenberg factorization in terms a sequence of Jacobi transformation has been described by Bini and Robol in the paper https://doi.org/10.1016/j.laa.2015.08.026

Why the Jacobi Transformation sequence J(2,3), J(2,4), ..., J(2,n); J(3,4), ..., J(3,n); ...; J(n-1,n) reduces a matrix to it's lower Hessenberg form:
For each row p={1,...,n-2} the rotations J(p+1,p+2),...,J(p+1,n) zero row p's excess entries one at a time, folding each into the pivot A(p,p+1).
The row-mixing half of these rotations only touches rows beyond p, so no earlier row is touched there.
The column-mixing half touches columns p+1,...,n in every row, including row p where it creates the new zeros, also in earlier finished rows where those columns are already zero - so 0 stays 0.
Going top to bottom this way the matrix becomes lower Hessenberg once all rows are done.

Implementation notes:
To get rotational angle, we know A_{p-1,p} sin theta + A_{p-1,q} cos theta = 0.
Assuming cos theta != 0, we can rewrite this to: tan theta = -\frac{A_{p-1,q}}{A_{p-1,p}}.
Which in turn let's us obtain the angle from: theta = atan2(-A_{p-1,q},A_{p-1,p}).

Notes on extra exercice implementations:
For modified_qr:
    Uses the fact that only one nonzero entry below diagonal in each column exists.
    Therefore a single rotation (J(p,p-1)) can elimate it
For modified_evd:
    Since the input matrix is assumed tridiagonal only the n-1 nearest neighbor entries can be nonzero. Only these pairs are rotated.
    Uses this fact to aggresively skip entries inside each rotation to reduce scaling.
    Don't construct the eigenvectors as this blows up scaling
    Assumed that O(n) is O(n) for each eigenvalue, so it is checked against O(n)/#eigenvalues.
    Sorting the eigenvalues at the end might impact the scaling complexity.

Extra implementation details:
Chose to make modified versions of the full homeworks, instead of overloading the classes.
This is because i want the homeworks to remain as is, without mixing them with the exam


Self assessment: 10/10
