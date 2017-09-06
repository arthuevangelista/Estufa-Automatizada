Micro e Micro - 2.2017

# Ponto de Controle 01

## Projeto de Automação com MSP430

* **Justificativa**
    * O controle hídrico em lavouras, jardins residenciais e estufas tem papel fundamental nas finanças de uma empresa ou residência. Estima-se que boa parte dos gastos com água potável são devido a estas atividades. Em uma situação de crise hídrica como a atual e o preço da água se elevando a cada dia, uma empresa ou residência com controle de seus gastos hídricos obtém vantagem econômica expressiva.

* **Objetivos**
    * Economia de água devido a automação do ambiente;
    * Controle de irrigação do jardim/lavoura/plantação;
    * Captação de dados de umidade e temperatura ambiente;
    * Calcular e fornecer dados estatísticos como temperatura média, umidade relativa, desvios padrões e etc.
      
* **Requisitos**
    * Uso do launchpad MSP430;
    * Uso de uma memória flash externa para armazenamento do banco de dados;
    * Controle do fluxo de água com Relés e válvulas solenóides;
    * Sensores de umidade e temperatura;
    * Módulo Wi-Fi e Bluetooth;
    
* **Benefícios**
    * Uso da opção de low-power mode do MSP430 pode oferecer vantagem nos momentos em que não estiver sendo utilizado;
    * Relés e válvulas todas normalmente fechadas provê economia substancial de energia;
    * Controle hídrico
    
* **Revisão Bibliográfica**
    * 
    
* **Anotações Temporárias**

> Dúvida: Entrada de dados no sistema;

> Banco de dados ficaria armazenado em um dispositivo flash externo ao microcontrolador. Listas encadeadas podem ser uma boa abordagem para guardar elementos, adicionar/remover elementos e etc do banco de dados. **CUIDADO!** Listas são realizadas com alocação dinâmica de memória (pode dar problema na memória RAM do MSP430 se não for especificado que a lista deve estar na memo flash);
