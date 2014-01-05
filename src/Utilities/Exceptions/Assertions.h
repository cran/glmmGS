#ifndef UTILITIES_EXCEPTIONS_ASSERTIONS_H
#define UTILITIES_EXCEPTIONS_ASSERTIONS_H

#include "InvalidArgumentException.h"
#include "InvalidOperationException.h"
#include <assert.h>
#include <stdlib.h>

// Basic assertion
#define _VALIDATE(expression, exception) {if (!(expression)) throw(exception);}
#ifdef _DEBUG
#define _ASSERT(expression, exception) _VALIDATE(expression, exception)
#else
#define _ASSERT(expression, exception) (void(0));
#endif

// Assertion macros
#define _ASSERT_ARGUMENT(expression) _ASSERT(expression, Utilities::Exceptions::InvalidArgumentException())
#define _VALIDATE_ARGUMENT(expression) _VALIDATE(expression, Utilities::Exceptions::InvalidArgumentException())
#define _ASSERT_OPERATION(expression) _ASSERT(expression, Utilities::Exceptions::InvalidOperationException())
#define _VALIDATE_OPERATION(expression) _VALIDATE(expression, Utilities::Exceptions::InvalidOperationException())

#endif
