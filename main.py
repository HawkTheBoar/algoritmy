import turtle, tkinter
from functools import cache

if __name__ == "__main__":
    print("Zadejte délku stěny spirály: ", end="")
    L = int(input()) * 10
    print("Zadejte sířku mezery mezi stěnami spirály: ", end="")
    W = int(input()) * 10

    screen = turtle.Screen()
    t = turtle.Turtle()
    @cache
    def step(L):
        for i in range(2):
            turtle.forward(L)
            turtle.right(90)
        if L > W:
            step(L-W)

    turtle.forward(L)
    turtle.right(90)
    step(L)

    screen.exitonclick()
