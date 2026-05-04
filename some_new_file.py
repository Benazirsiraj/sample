def add_three_numbers(a, b, c, d):
    """
    Function to add three numbers.
    
    Args:
        a (int or float): First number
        b (int or float): Second number
        c (int or float): Third number
        d (int or float): Fourth number
    
    Returns:
        int or float: Sum of a, b, c, and d
    """
    return a + b + c + d

# Example usage
if __name__ == "__main__":
    num1 = 5
    num2 = 3
    num3 = 2
    num4 = 1

    result = add_three_numbers(num1, num2, num3,num4)
    print(f"The sum of {num1}, {num2}, {num3}, and {num4} is {result}")
    
