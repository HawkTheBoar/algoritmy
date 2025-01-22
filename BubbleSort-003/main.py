import time

class Timer:
    def __init__(self):
        self.startTime = 0
        self.lastTimeRecorded = 0
    
    def start(self):
        self.startTime = time.time()
    def end(self):
        self.lastTimeRecorded = time.time - self.start
    def getLastTimeRecorded(self):
        return self.lastTimeRecorded

def swap(arr, x, y):
    arr[x], arr[y] = arr[y], arr[x]
def BubbleSort(arr):
    LENGTH = len(arr)
    N = LENGTH - 1
    for i in range(N):
        if(i % 100 == 0):
            print(f'{i}/{N}')
        swapped = False
        for j in range(N - i):
            if(arr[j] > arr[j+1]):
                swap(arr, j, j+1)
                swapped = True
        if(not swapped):
            break
    return arr

timer = Timer()
timer.start()
input = open("input.txt", "r")
arr = list(map(int, input.readlines()))
input.close()
BubbleSort(arr)
timer.end()

output = open('output.txt', 'w')
output.write(timer.getLastTimeRecorded())
output.writelines(list(map(str, arr)))
output.close()