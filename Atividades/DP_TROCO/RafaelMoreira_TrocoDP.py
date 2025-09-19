while True:
    try:
        n = int(input("Digite o número de notas: "))

        if (n < 1):
            print("Número de notas inválido")
        else:
            break
    except ValueError:
        print("Entrada inválida")

notas = []
i = n

while (i > 0):
    try:
        nota = int(input("Digite o valor da nota: "))

        if nota in notas:
            print("Nota duplicada")
            i += 1
        elif nota < 1:
            print("Nota inválida")
            i += 1
        else:
            notas.append(nota)

    except ValueError:
        print("Entrada inválida")
        i += 1
    i -= 1


notas.sort()

while True:
    try:
        valor_troco = int(input("Digite o valor do troco: "))

        if (valor_troco < 1):
            print("Valor para troco inválido")
        else:
            break
    except ValueError:
        print("Entrada inválida")

def troco (notas, valor_troco, resultados, notas_usadas):
    min = valor_troco
    if (valor_troco in notas):
        # se valor do troco está em notas, o troco é a própria nota que está no vetor
        resultados[valor_troco] = 1
        notas_usadas[valor_troco] = valor_troco
        return 1
    elif (resultados[valor_troco] > 0):
        # se entrar nesse if, o troco para valor_troco já está calculado
        return resultados[valor_troco]
    else:
        # senao, ainda nao foi calculado, entao calcula
        for i in [j for j in notas if j <= valor_troco]:
            n_notas = 1 + troco(notas, valor_troco - i, resultados, notas_usadas)
            if (n_notas < min):
                min = n_notas
                resultados[valor_troco] = min
                notas_usadas[valor_troco] = i
    return min

def print_notas(notas_usadas, valor, notas):
    troco = notas_usadas[valor]
    valor = valor - troco
    notas.append(troco)
    if valor > 0:
        print_notas(notas_usadas, valor, notas)
    else:
        return notas

notas_usadas = [0] * (valor_troco + 1)
troco_res = troco(notas, valor_troco, [0]*(valor_troco + 1), notas_usadas)
notas = []

print_notas(notas_usadas, valor_troco, notas)

print(f"Serão necessárias {troco_res} nota(s) para o troco.")
print(f"A(s) nota(s) usada(s) foram: {notas}")
