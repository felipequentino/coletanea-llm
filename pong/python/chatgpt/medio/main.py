import pygame
import random

# Inicialização do Pygame
pygame.init()

# Definição das cores
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

# Definição das dimensões da janela
WIDTH, HEIGHT = 800, 600

# Configuração da janela do jogo
win = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Pong")

# Definição das variáveis do jogo
player_width, player_height = 10, 100
opponent_width, opponent_height = 10, 100
ball_width, ball_height = 10, 10
player_speed, opponent_speed, ball_speed = 7, 6, 5

# Inicialização das posições e velocidades
player_x, player_y = 50, HEIGHT // 2 - player_height // 2
opponent_x, opponent_y = WIDTH - 50 - opponent_width, HEIGHT // 2 - opponent_height // 2
ball_x, ball_y = WIDTH // 2 - ball_width // 2, HEIGHT // 2 - ball_height // 2
ball_dx = random.choice([-1, 1]) * ball_speed
ball_dy = random.choice([-1, 1]) * ball_speed

# Função para desenhar as raquetes e a bola
def draw_objects():
    win.fill(BLACK)
    pygame.draw.rect(win, WHITE, (player_x, player_y, player_width, player_height))
    pygame.draw.rect(win, WHITE, (opponent_x, opponent_y, opponent_width, opponent_height))
    pygame.draw.ellipse(win, WHITE, (ball_x, ball_y, ball_width, ball_height))

# Função principal do jogo
def main():
    global player_y, opponent_y, ball_x, ball_y, ball_dx, ball_dy, ball_speed

    clock = pygame.time.Clock()
    running = True

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        keys = pygame.key.get_pressed()

        # Controle do jogador
        if keys[pygame.K_w] and player_y > 0:
            player_y -= player_speed
        if keys[pygame.K_s] and player_y < HEIGHT - player_height:
            player_y += player_speed

        # Movimento do oponente (IA simples)
        if ball_dy < 0 and opponent_y > 0:
            opponent_y -= opponent_speed
        elif ball_dy > 0 and opponent_y < HEIGHT - opponent_height:
            opponent_y += opponent_speed

        # Atualização da posição da bola
        ball_x += ball_dx
        ball_y += ball_dy

        # Verificação de colisões
        if ball_y <= 0 or ball_y >= HEIGHT - ball_height:
            ball_dy = -ball_dy

        if ball_x <= 0:
            ball_x, ball_y = WIDTH // 2 - ball_width // 2, HEIGHT // 2 - ball_height // 2
            ball_dx = random.choice([-1, 1]) * ball_speed
            ball_dy = random.choice([-1, 1]) * ball_speed
            ball_speed = 5

        if ball_x >= WIDTH - ball_width:
            if player_y <= ball_y <= player_y + player_height or opponent_y <= ball_y <= opponent_y + opponent_height:
                ball_dx = -ball_dx
                ball_speed += 0.5

        # Desenhar os objetos na tela
        draw_objects()

        # Atualizar a tela
        pygame.display.update()
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()
