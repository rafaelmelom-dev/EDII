def Fib(x):
    if (x <= 1):
        return 0
    elif (x == 2):
        return 1 
    
    return Fib(x-1) + Fib(x-2)

while True:
    x = int(input("Digite um número para a sequência de Fibonnacci: "))
    print(f"Fib({x}) = {Fib(x)}")
