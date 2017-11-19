Micro e Micro - 2.2017

# Ponto de Controle 01

## Projeto de Automação com MSP430

* **Módulos utilizados no sistema**
	* Abaixo segue uma lista dos módulos que serão utilizados no sistema até a data de redação deste relatório
	
	* **Level-shifter para redução de tensão**
		* Uma montagem utilizando dois resistores de 10k ohm e um transistor mosfet BS170.
		* O level-shifter reduz a tensão para que seja possível conectar componentes que utilizam diferentes tensões como nível lógico alto. Se um sinal chega com 3,3 V o level-shifter subirá esta tensão para 5 V em sua saída para que seja utilizado por outro componente.
		* A recíproca é verdadeira. Portanto, se um sinal tiver 5 V, a saída do level-shifter terá 3,3 V.
		* Imagem do esquemático do componente abaixo.
		* Testes foram realizados com este componente para verificar se ele funciona e quais os níveis de tensão em sua saída. Houve também uma preocupação quanto à frequência máxima de operação, uma vez que este componente será utilizado na saída de todos os sensores e nas saídas do MSP430. Foi confirmada o nível de ruído apresentado na saída do level-shifter à partir de Hz, de acordo com a informação do datasheet do componente transistor BS170. As imagens abaixo mostram os resultados obtidos nos testes com osciloscópio.

> **LINK PARA DATASHEET DO BS170: https://www.onsemi.com/pub/Collateral/BS170-D.PDF**

   * **Módulo relé 4 canais**
       * Será utilizado um módulo com 4 relés para controle dos dispositivos com tensão de 12V e corrente
    * **Módulo sensor de umidade do solo (umidostato)**

		* Possui formato de garfo (apenas duas pontas que deverão estar fincadas no solo). Ao identificar umidade ocorrerá uma diferença de potencial entre as pontas do garfo. A corrente que passará entre as duas pontas é muito pequena (resistência próxima dos M ohm).

		* Quanto maior a resistência, menor a umidade entre as ponteiras. A corrente, portanto, é muito baixa para que se insira o sensor diretamente na porta analógica do micro. É necesário o uso de um módulo comparador.

			* Nada mais é que um amplificador operacional em modo comparador. Quando comprado o sensor, o comparador LM393 (low offset voltage dual comparator) vem no conjunto.

			* A tensão de trabalho é de 3,3 V a 5 V. O comparador tem quatro pinos: Vcc, GND, D0 (digital) e A0 (analógico). Para usar a saída digital é necessário utilizar o potenciômetro para calibrar o sensor.

			* O potenciômetro irá ajustar em qual medida de umidade a saída digital terá nível lógico zero. OBS.: Podemos utilizar uma entrada digital do MSP430 ativa em alta para identificar quando a umidade está baixa. Ou seja, Quando D0 = 1 -> Umidade baixa. Quando D0 = 0 -> Umidade no solo suficiente, desliga o irrigador.

			* Utilizaremos apenas o pino digital para o projeto. A leitura dos dados de umidade do solo podem ser comutados com a leitura dos dados de umidade do ar (DHT11), liberando a porta digital para outra aplicação.

			* Utilizar uma porta analógica para leitura de dados seria mais preciso, mas exigira um processamento do sinal analógico antes deste ser inserido no microcontrolador (i.e. uma média móvel dos valores para evitar ruído/sinal aleatório).

**REFERÊNCIAS**
> **LINK PARA SENSOR: https://www.filipeflop.com/produto/sensor-de-umidade-do-solo-higrometro/
	LINK PARA O DATASHEET DO LM393: http://www.ti.com/lit/ds/symlink/lm293.pdf**

	* Para visualização dos dados (umidade do ar, umidade do solo e temperatura) será utilizado um display. Dependendo da temperatura será ativado um exaustor (resfriar a estufa) ou uma lâmpada (aquecer a estufa); Da umidade do ar/solo serão ligadas as válvulas de irrigação.

		* Possui uma biblioteca na IDE do arduino #include<LiquidCrystal.h>
		* Pode ser facilmente implementada no MSP430
		* Utilizado para referência do usuário e para verificação dos dados da estufa

	* O sensor DHT11 é responsável por realizar a medição de umidade relativa do ar (usando um sensor do tipo HR202 (entre 20% e 90%)) e da temperatura (usando um termistor NTC (entre 0 e 50 C)). Possui quatro pinos: Vcc, GND, Dados (comunicação UART) e N.C (não utilizada)

		* Possui uma biblioteca própria no Arduino #include<dht.h>

		* Utiliza dois pinos para enviar os dados para o Microcontrolador (ambos analógicos). Para escrever os dados no display, é necessário separar os digitos.

		* É necessário um delay entre uma leitura e a outra (o micro enviará um sinal avisando que está em modo de leitura e o DHT11 enviará outro sinal indicando que está enviando dados). Será utilizada uma interrupção com o timer A para realizar a leitura dos dados.

		* Possui uma biblioteca para msp430 disponível no link do github a seguir: https://github.com/bafeigum/DHT11-Library-for-MSP430

		* Para utilizar esta biblioteca é necessário o uso de um timer e uma interrupção, uma vez que a leitura e escrita exigem um delay entre a comunicação com a placa.
			* Precisa estar setado em UP mode e contando a cada 250 kHz (pode-se utilizar o SMCLOCK sendo /4);
			* ISR seta um volatile unsigned char TOUT no TA0. Esse ISR também deverá dar clear na interrupt flag, setando CCIFG no registrador TACCL0;
			* São enviados 5 elementos de um vetor (chamado packet) para o MSP430:
				* packet[0] = primeiro byte de umidade
				* packet[1] = segundo byte de umidade (deve ser ZERO)
				* packet[2] = primeiro byte de temperatura
				* packet[3] = segundo byte de temperatura (deve ser ZERO)
				* packet[4] = byte da soma dos 4 bytes anteriores (usado para checagem dos dados (em caso de falha na comunicação))

**REFERÊNCIAS**
> **LINK PARA SENSOR: https://www.filipeflop.com/produto/sensor-de-umidade-e-temperatura-dht11/
	LINK PARA O DATASHEET DO DHT11: http://img.filipeflop.com/files/download/Datasheet_DHT11.pdf**
