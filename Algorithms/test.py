// write a function to sort a list of numbers in maopao sort
def maopao_sort(numbers):
    for i in range(len(numbers)):
        for j in range(len(numbers) - 1):
            if numbers[j] > numbers[j + 1]:
                numbers[j], numbers[j + 1] = numbers[j + 1], numbers[i]
    return numbers


// test the function
numbers = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
print(maopao_sort(numbers))
 