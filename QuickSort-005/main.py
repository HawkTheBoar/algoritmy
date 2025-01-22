def swap(arr, x, y):
    arr[x], arr[y] = arr[y], arr[x]

def partition(arr, low, high):
    pivot = arr[high]  # Select the last element as the pivot
    i = low - 1  # Pointer for the smaller element
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            swap(arr, i, j)
    # Swap the pivot element to its correct position
    swap(arr, i + 1, high)
    return i + 1  # Return the partition index

def quick_sort(arr, low, high):
    if low >= high:  # Base case
        return
    pi = partition(arr, low, high)  # Partition the array

    # Recursively sort elements before and after partition
    quick_sort(arr, low, pi - 1)
    quick_sort(arr, pi + 1, high)

# Example usage
arr = [10, 80, 40, 50, 20, 90, 70]
quick_sort(arr, 0, len(arr) - 1)
print(arr)
