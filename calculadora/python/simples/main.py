def adicao(x, y):
    return x + y

def subtracao(x, y):
    return x - y

def multiplicacao(x, y):
    return x * y

def divisao(x, y):
    if y != 0:
        return x / y
    else:
        return "Erro: Divisão por zero"

# Função principal para interação com o usuário
def calculadora():
    while True:
        print("Escolha a operação:")
        print("1. Adição")
        print("2. Subtração")
        print("3. Multiplicação")
        print("4. Divisão")
        print("5. Sair")

        escolha = input("Digite a opção (1/2/3/4/5): ")

        if escolha == '5':
            print("Saindo da calculadora. Até logo!")
            break

        if escolha in ('1', '2', '3', '4'):
            try:
                num1 = float(input("Digite o primeiro número: "))
                num2 = float(input("Digite o segundo número: "))
            except ValueError:
                print("Por favor, insira números válidos.")
                continue

            if escolha == '1':
                print(f"{num1} + {num2} = {adicao(num1, num2)}")
            elif escolha == '2':
                print(f"{num1} - {num2} = {subtracao(num1, num2)}")
            elif escolha == '3':
                print(f"{num1} * {num2} = {multiplicacao(num1, num2)}")
            elif escolha == '4':
                resultado = divisao(num1, num2)
                if isinstance(resultado, float):
                    print(f"{num1} / {num2} = {resultado}")
                else:
                    print(resultado)
        else:
            print("Opção inválida. Por favor, escolha novamente.")

# Chama a função principal
calculadora()
