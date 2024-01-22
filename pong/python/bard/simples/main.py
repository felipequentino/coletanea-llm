import pygame

# Configurações do jogo
largura = 640
altura = 480
velocidade = 5

# Inicializa o PyGame
pygame.init()

# Cria a janela do jogo
janela = pygame.display.set_mode((largura, altura))

# Cria as paletas
paleta1 = pygame.Rect(50, altura / 2, 100, 20)
paleta2 = pygame.Rect(largura - 150, altura / 2, 100, 20)

# Cria a bola
bola = pygame.Rect(largura / 2, altura / 2, 20, 20)

# Inicializa a bola em movimento
bola.xvel = 5
bola.yvel = 5

# Variável para controlar o jogo
rodando = True

# Loop principal do jogo
while rodando:
    # Processa os eventos do teclado
    for event in pygame.event.get():
        # Verifica se o usuário clicou no botão de fechar
        if event.type == pygame.QUIT:
            rodando = False

        # Verifica se o usuário pressionou as teclas de controle das paletas
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_w:
                paleta1.y -= velocidade
            elif event.key == pygame.K_s:
                paleta1.y += velocidade

    # Atualiza a posição da bola
    bola.x += bola.xvel
    bola.y += bola.yvel

    # Verifica se a bola tocou as bordas da tela
    if bola.x <= 0 or bola.x >= largura:
        bola.xvel = -bola.xvel

    # Verifica se a bola tocou as paletas
    if bola.colliderect(paleta1) or bola.colliderect(paleta2):
        bola.yvel = -bola.yvel

    # Atualiza a posição das paletas
    paleta1.y = pygame.mouse.get_pos()[1] - paleta1.height / 2

    # Desenha o jogo na tela
    janela.fill((0, 0, 0))
    pygame.draw.rect(janela, (255, 255, 255), paleta1)
    pygame.draw.rect(janela, (255, 255, 255), paleta2)
    pygame.draw.rect(janela, (255, 0, 0), bola)

    # Atualiza a tela
    pygame.display.flip()

# Finaliza o PyGame
pygame.quit()

""" erro: Traceback (most recent call last):
  File "/home/liputer/Documentos/pibiti/IA/pong/python/bard/simples/main.py", line 22, in <module>
    bola.xvel = 5
    ^^^^^^^^^
AttributeError: 'pygame.rect.Rect' object has no attribute 'xvel' """