# Este repositório se trata de uma coletânea de codificações feitas por IA, principalmente pelo ChatGPT 3.5, Github Copilot e CodeGeex.

### Até então foi feito 4 projetos (pong, CRUD, To-do List e calculadora), nas linguagens Javascript/HTML/CSS (Desenvolvimento Web); Lua; Python; WebASsembly (apenas PONG), cada um com 3 níveis: Simples, Médio e Avançado. A diferença entre os níveis se trata sobre a profundidade dos prompts (ver prompts.txt), quanto mais elaborado, maior o nível.

## Considerações sobre  Desenvolvimento Web:

- Quanto mais elaborado o prompt for, mais bem sucedido é o resultado. Isso é facilmente perceptível, mas quando trata-se de desenvolvimento web, a porcentagem de acertos aumenta muito consideravelmente. O prompt avançado de Pong foi o único em que o ChatGPT entregou tudo que foi requisitado, sem bugs nenhum. 

## Considerações sobre Python:

- O prompt simples foi o pior de todos, com a velocidade da bola altíssima e com física apenas nas paredes, a física com as raquetes não funcionam.
- O prompt médio resultou em menos bugs, mas ainda sim não é injogável, a bola se movimenta corretamente mas as físicas com as raquetes e com as paredes são inexistentes, de modo que a bola "some" da tela.
- O prompt avançado foi o melhor: Física com as paredes e com as raquetes funcionando, a IA vai exatamente na posição da bola, prevendo o resultado muito antes da colisão ocorrer, e alterações visuais também foram feitas com sucesso. 

## Considerações sobre Lua:

- O prompt simples foi muito bom, o melhor dos 4 casos, o jogo contém física com as raquetes bem elaboradas, tento até diferença entre o rebate com base na posição da raquete, além de você controlar as duas raquetes com W/S e ArrowUP/ArrowDown.

- O prompt médio, novamente, foi o melhor dos 4 casos. A velocidade da bola aumenta gradativamente, e agora há uma IA controlando a outra raquete, além de ter um Score do Usuário x IA.

- O prompt avançado peca apenas na IA, sendo muito inferior em comparação com o prompt médio, mas as raquetes estão estilizadas, além do visual do jogo estar mais bem feito e a movimentação da raquete mais fluída. Fica atrás apenas do avançado do JS/HTML/CSS.

## Considerações sobre WebAssembly:

- Um completo desastre, nenhum dos 3 níveis funciona, mesmo com diversos prompts apresentando os diversos erros gerados pelos códigos defeituosos às LLM. O avançado, depois de muitos prompts de insistência para a correção de erros, apresenta uma tela bem-feita, mas apenas isso, as raquetes não se movem e a bola é inexistente. O médio não funcionou, e o simples aparece a bola com uma velocidade muito rápida, e some rapidamente da tela (as raquetes também não funcionam). 
- Acredito que ocorreu essa deficiência devido à falta de documentação sobre WASM, por ser um framework "novo". Uma prova disso foi a minha persistência nos prompts nível avançado ao ChatGPT 3.5, pois ele apresentou um caminho para se fazer o projeto, mas se negou a fazer 4 vezes. 
