import pygame
import random

# Inicialização do Pygame
pygame.init()

# Definição das variáveis
largura_tela = 800
altura_tela = 600
tela = pygame.display.set_mode((largura_tela, altura_tela))
pygame.display.set_caption('Pong')

# Cores
cor_branca = (255, 255, 255)

# Variáveis da bola
ball = pygame.Rect(largura_tela/2 - 15, altura_tela/2 - 15, 30, 30)
ball_speed_x = 7 * random.choice((1, -1))
ball_speed_y = 7 * random.choice((1, -1))

# Variáveis dos jogadores
player1 = pygame.Rect(largura_tela - 20, altura_tela/2 - 60, 10, 120)
player2 = pygame.Rect(10, altura_tela/2 - 60, 10, 120)
player1_speed = 0
player2_speed = 0
player_speed = 7

# Função para atualizar a tela
def atualizar_tela(player1, player2, ball):
    tela.fill((0, 0, 0))
    pygame.draw.rect(tela, cor_branca, player1)
    pygame.draw.rect(tela, cor_branca, player2)
    pygame.draw.ellipse(tela, cor_branca, ball)
    pygame.draw.aaline(tela, cor_branca, (largura_tela/2, 0), (largura_tela/2, altura_tela))
    pygame.display.flip()

# Loop principal do jogo
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                player1_speed -= player_speed
            if event.key == pygame.K_DOWN:
                player1_speed += player_speed
            if event.key == pygame.K_w:
                player2_speed -= player_speed
            if event.key == pygame.K_s:
                player2_speed += player_speed
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                player1_speed = 0
            if event.key == pygame.K_w or event.key == pygame.K_s:
                player2_speed = 0

    # Movimento dos jogadores
    player1.y += player1_speed
    player2.y += player2_speed

    # Limites dos jogadores
    if player1.top <= 0:
        player1.top = 0
    if player1.bottom >= altura_tela:
        player1.bottom = altura_tela
    if player2.top <= 0:
        player2.top = 0
    if player2.bottom >= altura_tela:
        player2.bottom = altura_tela

    # Movimento da bola
    ball.x += ball_speed_x
    ball.y += ball_speed_y

    # Colisão da bola com os jogadores
    if ball.colliderect(player1) or ball.colliderect(player2):
        ball_speed_x *= -1

    # Limites da bola
    if ball.top <= 0 or ball.bottom >= altura_tela:
        ball_speed_y *= -1

    # Verificação de pontuação
    if ball.left <= 0 or ball.right >= largura_tela:
        ball_speed_x *= -1
        ball.center = (largura_tela / 2, altura_tela / 2)

    # Atualização da tela
    atualizar_tela(player1, player2, ball)
