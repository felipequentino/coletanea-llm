import pygame
from pygame.locals import *
import pygame.math
import random
import sys

# Constantes
WIDTH = 640
HEIGHT = 480
VEL_MOUSE = 50

# Classes
class Raquet(pygame.sprite.Sprite):
    def __init__(self, x, y, w, h, color):
        super().__init__()
        self.image = pygame.Surface((w, h))
        self.image.fill(color)
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y
        self.vel = 0

    def update(self):
        self.rect.y += self.vel

class Ball(pygame.sprite.Sprite):
    def __init__(self, x, y, w, h, vel_x, vel_y):
        super().__init__()
        self.image = pygame.Surface((w, h))
        self.image.fill((255, 255, 255))
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y
        self.vel_x = vel_x
        self.vel_y = vel_y

    def update(self):
        self.rect.x += self.vel_x
        self.rect.y += self.vel_y

        # Colisão com a borda superior
        if self.rect.top < 0:
            self.vel_y = -self.vel_y

        # Colisão com a borda inferior
        if self.rect.bottom > HEIGHT:
            self.vel_y = -self.vel_y

        # Colisão com a raquete do jogador
        if pygame.sprite.collide_rect(self, player1):
            self.vel_x = -self.vel_x

        # Colisão com a raquete da IA
        if pygame.sprite.collide_rect(self, player2):
            self.vel_x = -self.vel_x

# Inicialização
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Pong")

# Sprites
player1 = Raquet(10, HEIGHT // 2, 100, 20, (255, 0, 0))
player2 = Raquet(WIDTH - 110, HEIGHT // 2, 100, 20, (0, 0, 255))
ball = Ball(WIDTH // 2, HEIGHT // 2, 20, 20, 5, 5)

# Grupos
sprites = pygame.sprite.Group(player1, player2, ball)

# Loop principal
while True:
    # Eventos
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

        # Controle da raquete do jogador
        if event.type == MOUSEMOTION:
            player1.rect.centery = (event.pos[1] - player1.rect.centerx) / VEL_MOUSE

    # Atualização
    sprites.update()

    # Renderização
    screen.fill((0, 0, 0))
    sprites.draw(screen)

    pygame.display.flip()
