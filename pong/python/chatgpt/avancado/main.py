import pygame
import random

# Inicialização do Pygame
pygame.init()

# Cores
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

# Tamanho da tela
WIDTH, HEIGHT = 800, 600
FPS = 60

# Configurações da tela
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Pong")

# Variáveis do jogo
player_width, player_height = 10, 100
ball_size = 20
player_speed = 5
ball_speed_x = 4
ball_speed_y = 4

# Raquetes e bola
player1 = pygame.Rect(50, HEIGHT // 2 - player_height // 2, player_width, player_height)
player2 = pygame.Rect(WIDTH - 50 - player_width, HEIGHT // 2 - player_height // 2, player_width, player_height)
ball = pygame.Rect(WIDTH // 2 - ball_size // 2, HEIGHT // 2 - ball_size // 2, ball_size, ball_size)

# Velocidade da IA
ai_speed = 4

# Direção da bola
ball_dx = ball_speed_x
ball_dy = ball_speed_y

clock = pygame.time.Clock()

# Personalização - Cores
player1_color = (66, 135, 245)  # Azul
player2_color = (245, 135, 66)  # Laranja
ball_color = (255, 255, 0)      # Amarelo
background_color = (30, 30, 30)  # Cinza escuro

def predict_ball(ball_rect, ball_dx, ball_dy):
    future_ball = ball_rect.copy()
    future_ball_dx = ball_dx
    future_ball_dy = ball_dy

    while True:
        future_ball.x += future_ball_dx
        future_ball.y += future_ball_dy

        if future_ball.top <= 0 or future_ball.bottom >= HEIGHT:
            future_ball_dy *= -1

        if future_ball.colliderect(player1) or future_ball.colliderect(player2):
            future_ball_dx *= -1

        if future_ball.left <= 0 or future_ball.right >= WIDTH:
            return future_ball.y, future_ball_dy

# Loop do jogo
running = True
while running:
    screen.fill(background_color)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys = pygame.key.get_pressed()

    # Controles do jogador
    if keys[pygame.K_w] and player1.top > 0:
        player1.y -= player_speed
    if keys[pygame.K_s] and player1.bottom < HEIGHT:
        player1.y += player_speed

    # Lógica da IA
    if ball_dx > 0:
        predicted_y, _ = predict_ball(ball, ball_dx, ball_dy)
        if player2.centery < predicted_y:
            player2.y += ai_speed
        elif player2.centery > predicted_y:
            player2.y -= ai_speed

    # Movimento da bola
    ball.x += ball_dx
    ball.y += ball_dy

    # Colisão da bola com as paredes
    if ball.top <= 0 or ball.bottom >= HEIGHT:
        ball_dy *= -1

    # Colisão da bola com os jogadores
    if ball.colliderect(player1) or ball.colliderect(player2):
        ball_dx *= -1

    # Verificar vitória
    if ball.left <= 0 or ball.right >= WIDTH:
        # Implemente o que deseja fazer quando alguém vencer
        pass

    # Desenhar elementos na tela com cores personalizadas
    pygame.draw.rect(screen, player1_color, player1)
    pygame.draw.rect(screen, player2_color, player2)
    pygame.draw.ellipse(screen, ball_color, ball)

    # Atualizar a tela
    pygame.display.flip()
    clock.tick(FPS)

pygame.quit()
