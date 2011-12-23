\name{glmmGS.Control}
\alias{glmmGS.Control}
\title{
Construct control list for \code{glmmGS} function
}
\description{
	%%  ~~ A concise (1-5 lines) description of what the function does. ~~
	Construct a list of control parameters used internally by the 
	\code{\link{glmmGS}} function.
}
\usage{
	glmmGS.Control(reltol = 1e-06, abstol = 1e-06, maxit = 200)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
 	\item{reltol}{
		minimum relative tolerance for the parameters update.
	}
	\item{abstol}{
		minimum absolute tolerance for the parameters update.
	}
  	\item{maxit}{
		maximum number of iterations for the parameters update.
	}
}
\details{
	%%  ~~ If necessary, more details than the description above ~~
	The Gauss-Seidel iterative algorithm stops if the magnitude of every 
	parameter update is less than \code{abstol} or less than \code{reltol} 
	times the magnitude of the current parameter.
	If the algorithm reaches \emph{maxit} number of iterations without converging, 
	then the algorithm stops and returns an error.
}

\value{
	%%  ~Describe the value returned
	%%  If it is a LIST, use
	%%  \item{comp1 }{Description of 'comp1'}
	%%  \item{comp2 }{Description of 'comp2'}
	%% ...
	A list of control parameters for the \code{\link{glmmGS}} function.
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
	\code{\link{glmmGS}}
}

\examples{
	control <- glmmGS.Control(reltol = 1.e-8, abstol = 1.e-25, maxit = 500);
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
