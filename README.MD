# Sketch Arduino para controle de temperatura de fechamento de impressora 3D

## Sobre:
Este projeto foi desenvolvido para controlar a temperatura de fechamento de uma impressora 3D, utilizando um Arduino Uno com os seguintes componentes:
- 1x Sensor de temperatura e humidade DHT22
- 1x Display OLED 128x64
- 1x Teclado matricial 3x4
- 1x Modulo de Reles 5V 4 Canais
- 3x Fan Cooler 12V
- 1x Fonte 12V 5A
- 1x Conversor Step Down 12V para 5V (lm2596)

## Motivação:
A motivação para o desenvolvimento deste projeto foi a necessidade de controlar a temperatura interna de uma estrutura fechada, onde uma impressora 3D foi colocada para evitar alterações de temperatura, o que pode dificultar o uso de determinados filamentos, por exemplo o ABS.

## Funcionalidades:
- **Controle de temperatura**: O sketch realiza a leitura da temperatura e humidade do ambiente e controla o acionamento dos coolers de acordo com a temperatura de referência definida pelo usuário.
- **Display OLED**: O sketch exibe no display OLED a temperatura e humidade do ambiente, além de mensagens de erro e configurações.
- **Teclado matricial**: O sketch utiliza o teclado matricial para que o usuário possa navegar entre os menus e realizar as configurações desejadas.
- **Controle manual**: O sketch permite que o usuário controle de forma manual o acionamento dos coolers.
- **Controle automático**: O sketch permite que o usuário defina uma temperatura de referência para que o sketch controle o acionamento dos coolers de forma automática.

## Funcionamento:
O sketch trabalha de duas forma:
- Modo manual: Onde o usuário pode controlar de forma manual o acionamento dos coolers.
- Modo automático: Onde o usuário pode definir uma temperatura de referência para que o sketch controle o acionamento dos coolers de forma automática.

Para que essas configurações possam ser feitas, o sketch utiliza o teclado matricial para que o usuário possa navegar entre os menus e realizar as configurações desejadas.

Em modo de operação o sketch realiza a leitura da temperatura e humidade do ambiente e exibe no display OLED, além de controlar o acionamento dos coolers de acordo com a temperatura de referência definida pelo usuário.

## Estrutura de pastas:
```
.
├── README.md  // Este arquivo
├── LICENSE    // Licença de uso
├── src        // Código fonte
│   ├── temp_control // Pasta do sketch
│   │   ├── temp_control.ino // Arquivo principal
|   ├── img // Imagens utilizadas no sketch
│   │   ├── 3d_printer61x64.png // imagem da impressora 3D usada como logo
│   │   ├── alert20x20.png // imagem de alerta usada em mensagens de erro

```
## Contribuindo

Contribuições para este projeto são bem-vindas. Se você tiver alguma ideia, sugestão ou relatório de bug, abra um issue ou envie um pull request no repositório GitHub.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).

## Utilidades/Referências:
- [Usando um oled display com Arduino](https://www.makerhero.com/blog/como-conectar-display-oled-arduino/)
- [Usando um oled display com Arduino2](https://www.youtube.com/watch?v=8iJdbe6OP14&t=695s)
- [Como desenhar imagens bitmap em um Display OLED SSD1306 com Arduino - biblioteca Adafruit](https://www.squids.com.br/arduino/index.php/projetos-arduino/projetos-squids/basico/301-projeto-91-como-exibir-imagens-bitmap-um-display-oled-ssd1306-com-arduino-biblioteca-adafruit)
- [Como usar um teclado matricial com Arduino](https://www.robocore.net/tutoriais/usando-teclado-matricial-com-arduino)
- [Como usar um teclado matricial com Arduino2](https://www.youtube.com/watch?v=7ZFmx5j2sls)
- [Como usar um modulo de reles com Arduino](https://blogmasterwalkershop.com.br/arduino/como-usar-com-arduino-modulo-rele-5v-de-4-canais)
- [Guarndando os dados digitados no teclado matricial](https://forum.arduino.cc/t/keypad-h-por-favor-help/195107/14)
- [Como usar um sensor de temperatura e humidade DHT22 com Arduino](https://blogmasterwalkershop.com.br/arduino/como-usar-com-arduino-sensor-de-umidade-e-temperatura-dht22-am2302)
- [Como usar um sensor de temperatura e humidade DHT22 com Arduino2](https://www.youtube.com/watch?v=m71B6Qvhi9M&t=12s)
- [Transformar uma imagem em bitmap](https://javl.github.io/image2cpp/)
- [Redimensionar uma imagem](https://www.resizepixel.com/download)
