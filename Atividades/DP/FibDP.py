def FibDP (x):
    if (x <= 1):
        return 0
    elif (x == 2):
        return 1 
        
    dp = [0 for i in range (x+3)] 
    
    dp[1] = 0
    dp[2] = 1
    
    for i in range(3, x+3):
        dp[i]  = dp[i - 1] + dp[i - 2]
    
    return dp[x]
    
while True:
    x = int(input("Digite um número para a sequência de Fibonnacci: "))
    print(f"Fib({x}) = {FibDP(x)}")
