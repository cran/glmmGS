\name{glmmGS.SparseMatrix}
\alias{glmmGS.SparseMatrix}
\title{
	Construct sparse matrix for \code{glmmGS.CovarianceModel} function
}
\description{
	%%  ~~ A concise (1-5 lines) description of what the function does. ~~
	Construct list of variables defining a column-sparse matrix used 
	by the \code{\link{glmmGS.CovarianceModel}} function
}
\usage{
	glmmGS.SparseMatrix(\dots)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
	\item{\dots}{
		can be a dense matrix or the following arguments in order: 
		(1) a numeric (i.e., double) vector with the non-zero elements of the matrix;
		(2) an integer vector with the zero-based row indices of the non-zero elements of the matrix;
		(3) an integer vector \code{counts} of length \code{ncols + 1},
		where \code{ncols} indicates the number of columns of the matrix,
		such that \code{counts[1] = 0}, and \code{counts[j]} equal to the total number	
		of non-zero elements in columns 1, \ldots, j - 1.
	}
}

\details{
	%%  ~~ If necessary, more details than the description above ~~
	The list returned by this function defines a column-sparse matrix. The data structure
	is the same one used by the LDL algorithms written by Tim Davis at 
	the University of Florida (see reference).
}
\value{
	%%  ~Describe the value returned
	%%  If it is a LIST, use
	%%  \item{comp1 }{Description of 'comp1'}
	%%  \item{comp2 }{Description of 'comp2'}
	%% ...
	A list with variables named as the arguments, describing a column-sparse matrix. 
}
\references{
	%% ~put references to the literature/web site here ~
	\url{http://www.cise.ufl.edu/research/sparse/ldl/}
}
\author{
	%%  ~~who you are~~
	Michele Morara, Louise Ryan, Subharup Guha, Christopher Paciorek
}
\note{
	%%  ~~further notes~~
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
	%% ~~objects to See Also as \code{\link{help}}, ~~~
}
\examples{

# Create dense matrix R
	ncols <- 100;
	R <- diag(rep(1, ncols));
	for (i in 2:ncols)
		R[i - 1, i] <- R[i, i - 1] <- 0.5;
	
# Create sparse matrix from dense matrix R

	R.sparse <- glmmGS.SparseMatrix(R);
	
# Create sparse matrix from vectors of values, indices, and counts
# maximizing performance (requires O(ncols^2) workspace memory) 

	nz <- R != 0;
	values <- c(R[nz]);
	indices <- row(R)[nz] - 1L;
	counts <- as.integer(c(0, cumsum(colSums(nz))));
	R.sparse2 <- glmmGS.SparseMatrix(values, indices, counts);

# Create sparse matrix from vectors of values, indices, and counts
# allocating O(ncols) workspace memory
	
	# 1) Set counts
	counts <- integer(ncols + 1L);
	count.total <- 0L;
	counts[1] <- 0L;
	for (j in 1:ncols)
	{
		nz <- which(R[, j] != 0);
		count.total <- count.total + length(nz);
		counts[j + 1] <- count.total;
	}
	
	# 2) Set values and indices
	values <- double(count.total);
	indices <- integer(count.total);
	index <- 0L;
	for (j in 1:ncols)
	{
		nz <- which(R[, j] != 0);
		lnz <- length(nz);
		kk <- index + 1:lnz;
		values[kk] <- R[nz, j];
		indices[kk] <- nz - 1L; # must be zero-based
		index <- index + lnz;
	}
	
	# Build sparse matrix
	R.sparse3 <- glmmGS.SparseMatrix(values, indices, counts);
}

% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
