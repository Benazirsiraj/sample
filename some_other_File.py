def multiply_numbers(a, b, c):
    """
    Multiply three numbers.

    Args:
        a (int or float): First number
        b (int or float): Second number
        c (int or float): Third number

    Returns:
        int or float: Product of a, b, and c
    """
    return a * b * c


# Example usage
if __name__ == "__main__":
    num1 = 4
    num2 = 5
    num3 = 2
    result = multiply_numbers(num1, num2, num3)
    print(f"The product of {num1}, {num2}, and {num3} is {result}")