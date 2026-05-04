def greet(name):
    """
    Greet a person by their name.

    Args:
        name (str): The name of the person to greet

    Returns:
        str: A greeting message
    """
    return f"Hello, {name}! Welcome! Home"


# Example usage
if __name__ == "__main__":
    person = "Alice"
    message = greet(person)
    print(message)