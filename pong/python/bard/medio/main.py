import pygame
import sys
# Constantes
LARGURA = 640
ALTURA = 480

# Inicializa o Pygame
pygame.init()

# Cria a tela
tela = pygame.display.set_mode((LARGURA, ALTURA))

# Cria as raquetes
raquete1 = pygame.Rect(10, 200, 100, 20)
raquete2 = pygame.Rect(LARGURA - 110, 200, 100, 20)

# Cria a bola
bola = pygame.Rect(320, 240, 20, 20)
bola_velocidade_x = 10
bola_velocidade_y = 10

# Variáveis de controle
jogador1_direita = False
jogador2_direita = False

# Loop principal do jogo
while True:

    # Processa os eventos
    for evento in pygame.event.get():
        if evento.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        # Controles do jogador 1
        if evento.type == pygame.KEYDOWN:
            if evento.key == pygame.K_RIGHT:
                jogador1_direita = True
            elif evento.key == pygame.K_LEFT:
                jogador1_direita = False

        # Controles do jogador 2
        if evento.type == pygame.KEYDOWN:
            if evento.key == pygame.K_d:
                jogador2_direita = True
            elif evento.key == pygame.K_a:
                jogador2_direita = False

    # Atualiza a posição das raquetes
    if jogador1_direita:
        raquete1.x += 5
    else:
        raquete1.x -= 5

    # Atualiza a posição da bola
    bola.x += bola_velocidade_x
    bola.y += bola_velocidade_y

    # Colisão com a parte superior da tela
    if bola.top < 0:
        bola_velocidade_y = -bola_velocidade_y

    # Colisão com a parte inferior da tela
    if bola.bottom > ALTURA:
        bola_velocidade_y = -bola_velocidade_y

    # Colisão com a raquete do jogador 1
    if bola.colliderect(raquete1):
        bola_velocidade_x = -bola_velocidade_x

    # Colisão com a raquete do jogador 2
    if bola.colliderect(raquete2):
        bola_velocidade_x = -bola_velocidade_x

    # Colisão com a borda esquerda da tela
    if bola.x < 0:
        # Ponto para o jogador 2
        print("Jogador 2 ganhou!")

    # Colisão com a borda direita da tela
    if bola.x > LARGURA:
        # Ponto para o jogador 1
        print("Jogador 1 ganhou!")

    # Ajusta a velocidade da bola
    bola_velocidade_x += 0.01
    bola_velocidade_y += 0.01

    # Atualiza a tela
    tela.fill((0, 0, 0))
    pygame.draw.rect(tela, (255, 0, 0), raquete1)
    pygame.draw.rect(tela, (0, 255, 0), raquete2)
    pygame.draw.rect(tela, (255, 255, 255), bola)
    pygame.display.update()

