\name{glmmGS.CovarianceModel}
\alias{glmmGS.CovarianceModel}
\title{
	Construct covariance models for the \code{glmmGS} function
}
\description{
	%%  ~~ A concise (1-5 lines) description of what the function does. ~~
	Construct a list defining a covariance model for the \code{\link{glmmGS}} function. 
}

%% Function prototype
\usage{
	glmmGS.CovarianceModel(type, \dots)
}

%% Arguments
\arguments{
  	\item{type}{
		a string specifying the type of the covariance model. Current valid types are:
		\code{identity}, \code{precision}. The covariance components of the identity
		and precision models represent the global precision parameters.
  	}
  	\item{\dots}{
    	optional arguments containing information about the precision or covariance structure.
    	If the type is \code{identity}, no optional arguments are required;
    	if the type is \code{precision}, the optional argument is a precision matrix 
    	of either R \code{matrix} type or \code{\link{glmmGS.SparseMatrix}} type.
  	}
}

\details{
	%%  ~~ If necessary, more details than the description above ~~
}
\value{
	%%  ~Describe the value returned
	%%  If it is a LIST, use
	%%  \item{comp1 }{Description of 'comp1'}
	%%  \item{comp2 }{Description of 'comp2'}
	%% ...
	A list of parameters specifying a covariance model for the 
	\code{\link{glmmGS}} function.
}
\references{
	%% ~put references to the literature/web site here ~
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
	\code{\link{glmmGS}}, \code{\link{glmmGS.SparseMatrix}}
}
\examples{
# Set number of columns
	ncols <- 100;

# Identity covariance model (no need to specify matrix dimensions)
 	# Define dense-precision model
 	I <- glmmGS.CovarianceModel("identity");

# Dense-precision model

	# Dense precision matrix
	R <- as.matrix(rnorm(ncols * ncols), nrow = ncols, ncol = ncols);
	R <- R \%*\% t(R);
	
 	# Define dense-precision model
 	T.dense <- glmmGS.CovarianceModel("precision", R);

# Sparse-precision model

	# Sparse precision matrix
	R <- diag(rep(1, ncols));
	for (i in 2:ncols)
	{
		R[i - 1, i] <- 0.5;
		R[i, i - 1] <- 0.5;
	}
	
	# Create sparse matrix from R
	R.sparse = glmmGS.SparseMatrix(R);
	
 	# Define sparse-precision model
 	T.sparse <- glmmGS.CovarianceModel("precision", R.sparse);
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
