def add_three_numbers(a, b, c):
    """
    Function to add three numbers.
    
    Args:
        a (int or float): First number
        b (int or float): Second number
        c (int or float): Third number
    
    Returns:
        int or float: Sum of a, b, and c
    """
    return a + b + c

# Example usage
if __name__ == "__main__":
    num1 = 5
    num2 = 3
    num3 = 2
    result = add_three_numbers(num1, num2, num3)
    print(f"The sum of {num1}, {num2}, and {num3} is {result}")
