notas = []
notasUsadas = []

entrada = None

while (entrada != 0):
    entrada = int(input("Digite o valor da nota (digite 0 para finalizar): "))

    if (entrada != 0):
        notas.append(entrada)

notas.sort()

valor = int(input("Digite o valor: "))
resto = valor

while (resto != 0):
    while (notas[-1] > resto):
        notas.pop()
    resto -= notas[-1]
    notasUsadas.append(notas[-1])

notasUsadas.sort()
print(f"Notas usadas: {notasUsadas}")
