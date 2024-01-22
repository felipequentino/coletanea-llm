# verificaro big o da função a seguir:

def verify_number(array, number):
    for i in array: # size = len(array), logo O(n)
        if i == number: # O(1)
            return True  # O(1)
    return False # O(1)

# complexidade O(n) --> O(n), complexidade linear

def verify_number_2(array, number):
    size = len(array) # O(1)
    for i in range(size): # O(n)
        for j in range(size): # O(n)
            if i != j and array[i] == array[j]:
                return True
    return False

# complexidade O(n) --> O(n^2), complexidade quadrática

def verify_number_3(array, number): # complexidade quadrática com constantes
    size = len(array) # O(1)
    for i in range(size): # O(n)
        for j in range(size): # O(n)
            if i != j and array[i] == array[j]:
                # do something
                print('oi')
    
    for i in range(size): # O(n)
        # do something
        print('oi')
    
    for i in range(size): # O(n)
        if i == number:
            return True

# O(n) * O(n) + O(n) + O(n) --> 
# O(n^2) + 2*O(n) --> IGNORA A CONSTANTE E O MENOR GRAU
# O(n^2), complexidade quadrática.

def verify_array(vetor_v, vetor_w):
    v_size = len(vetor_v) # O(1)
    w_size = len(vetor_w) # O(1)
    for i in range(v_size): # O(n)
        for i in range(w_size): # O(m)
            if vetor_v[i] == vetor_w[i]:
                return True
    return False

# complexidade O(n) * O(m) --> O(n) O*(m)

def maior_idade(vetor):
    size = len(vetor)
    menor_idade = 200
    for i in range(size): # O(n)
        if vetor[i] < menor_idade:
            menor_idade = vetor[i]

    cont = 0
    for i in range(size): # O(n)
        if vetor[i] == menor_idade:
            cont += 1

    return cont > 1
# complexidade O(n) + O(n) --> O(n)

def maior_idade2(vetor):
    sorted_vetor = sorted(vetor)
    return vetor[0] == vetor[1]

# complexidade O(n log n) + O(1) --> O(n log n)

# as duas funções fazem a mesma coisa, mas a segunda é mais complexa, por mais que só tenha 2 linhas de código


