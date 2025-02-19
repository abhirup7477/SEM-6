import math
def regula_falsi(f, a, b, tol=1e-6, max_iter=100):
    if f(a) * f(b) >= 0:
        raise ValueError("Root is not bracketed. Choose different a and b.")

    for i in range(max_iter):
        c = b - (f(b) * (b - a)) / (f(b) - f(a))  # Secant formula
        
        if abs(f(c)) < tol:  # Check convergence
            return c
        
        if f(a) * f(c) < 0:  # Root lies between a and c
            b = c
        else:  # Root lies between c and b
            a = c
    
    return c  # Return last approximation
# Define the function
def f(x):
    return math.log10(x) - math.cos(x);

# Initial guesses
a = 1
b = 2

# Find the root
root = regula_falsi(f, a, b)
print("Root:", root)

print(f(1.41840))
