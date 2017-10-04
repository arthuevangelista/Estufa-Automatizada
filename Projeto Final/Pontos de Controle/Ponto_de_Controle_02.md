* **Utilizar módulo sensor de umidade do solo (umidostato)**

	* Possui formato de garfo (apenas duas pontas que deverão estar fincadas no solo). Ao identificar umidade ocorrerá uma diferença de potencial entre as pontas do garfo. A corrente que passará entre as duas pontas é muito pequena (resistência próxima dos M ohm).

	* Quanto maior a resistência, menor a umidade entre as ponteiras. A corrente, portanto, é muito baixa para que se insira o sensor diretamente na porta analógica do micro. É necesário o uso de um módulo comparador.

		* Nada mais é que um amplificador operacional em modo comparador. Quando comprado o sensor, o comparador LM393 (low offset voltage dual comparator) vem no conjunto.

		* A tensão de trabalho é de 3,3 V a 5 V. O comparador tem quatro pinos: Vcc, GND, D0 (digital) e A0 (analógico). Para usar a saída digital é necessário utilizar o potenciômetro para calibrar o sensor.

		* O potenciômetro irá ajustar em qual medida de umidade a saída digital terá nível lógico zero. OBS.: Podemos utilizar uma entrada digital do MSP430 ativa em alta para identificar quando a umidade está baixa. Ou seja, Quando D0 = 1 -> Umidade baixa. Quando D0 = 0 -> Umidade no solo suficiente, desliga o irrigador.

		* Utilizaremos apenas o pino digital para o projeto. A leitura dos dados de umidade do solo podem ser comutados com a leitura dos dados de umidade do ar (DHT11), liberando a porta digital para outra aplicação.

		* Utilizar uma porta analógica para leitura de dados seria mais preciso, mas exigira um processamento do sinal analógico antes deste ser inserido no microcontrolador (i.e. uma média móvel dos valores para evitar ruído/sinal aleatório).

LINK PARA SENSOR: https://www.filipeflop.com/produto/sensor-de-umidade-do-solo-higrometro/

	* Para visualização dos dados (umidade do ar, umidade do solo e temperatura) será utilizado um display. Dependendo da temperatura será ativado um exaustor (resfriar a estufa) ou uma lâmpada (aquecer a estufa); Da umidade do ar/solo serão ligadas as válvulas de irrigação.

		* Possui uma biblioteca na IDE do arduino #include<LiquidCrystal.h>

	* O sensor DHT11 é responsável por realizar a medição de umidade relativa do ar (usando um sensor do tipo HR202 (entre 20% e 90%)) e da temperatura (usando um termistor NTC (entre 0 e 50 C)). Possui quatro pinos: Vcc, GND, Dados () e N.C ()

		* Possui uma biblioteca própria #include<dht.h>

		* Utiliza dois pinos para enviar os dados para o Microcontrolador (ambos analógicos). Para escrever os dados no display, é necessário separar os digitos.

		* É necessário um delay entre uma leitura e a outra (o micro enviará um sinal avisando que está em modo de leitura e o DHT11 enviará outro sinal indicando que está enviando dados).

LINK PARA SENSOR: https://www.filipeflop.com/produto/sensor-de-umidade-e-temperatura-dht11/
